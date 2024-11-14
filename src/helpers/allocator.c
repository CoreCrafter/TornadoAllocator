#include "../../include/helpers/allocator.h"


#if defined(_WIN64) || defined(_WIN32) || defined(_WIN16)
#include <windows.h>
#elif defined(__linux__)
#include <sys/resource.h>
#include <unistd.h>
#endif

uintptr_t tornado_nullptr_addr = (uintptr_t)NULL;
size_t _mem_obj_meta_size = 0;
void (*_get_b_gc_ptr)();
void* _t_gc = NULL;
void* _b_gc = NULL;

static inline uintptr_t _get_data_addr(uintptr_t __start_addr__){
    return (uintptr_t)(__start_addr__ + _mem_obj_meta_size);
}
static inline uintptr_t _get_next_block_addr(uintptr_t __start_addr__, size_t object_size){
    return (uintptr_t)(_get_data_addr(__start_addr__) + object_size);
}
static inline bool _fits_in(uintptr_t _s, uintptr_t _e, size_t size){
return _get_next_block_addr(_s, size) <= _e;}

static inline MemObject* _get_meta(uintptr_t _data_addr){
    return (MemObject*)(_data_addr - _mem_obj_meta_size);
}

static void _append_to_list(TornadoMemory* mem, MemObject* _obj){
    MemObject* first_live_obj_ptr = _get_first_live_obj_ptr(mem);
    MemObject* last_live_obj_ptr = _get_last_live_obj_ptr(mem);
    if (first_live_obj_ptr == NULL){
        _set_first_live_obj_ptr(mem, _obj);
    }
    if (last_live_obj_ptr){
        _set_mem_obj_next(last_live_obj_ptr, _obj); 
    }
    _set_mem_obj_prev(_obj, last_live_obj_ptr);  
    _set_last_live_obj_ptr(mem,_obj);
}
static void allocate_at_end(TornadoMemory* mem, void** var_ptr, size_t object_size){
    MemObject* _obj = _fill_block(mem, var_ptr, object_size, _get_next_addr(mem));
    _append_to_list(mem, _obj);
    _set_next_addr(mem, _get_next_block_addr(_get_next_addr(mem), object_size));
}


static void _get_b_gc(){
    #if defined(_WIN64) || defined(_WIN32) || defined(_WIN16)
        #ifdef _MSC_VER || defined(__MINGW32__) || defined(__MINGW64__)
            _b_gc = (void*)(NtCurrentTeb()->NtTib.StackLimit); 
        #else
            _b_gc = (void*)_AddressOfReturnAddress();
        #endif 
    #elif defined(__linux__)
        struct rlimit sl;
        getrlimit(RLIMIT_STACK, &sl);
        _b_gc = (void*)((char*)&sl - sl.rlim_cur);
    #endif
}

static void _get_b_gc_op(){
    int32_t __temp_gc = 0xd22255;
    _b_gc = (void*)&__temp_gc;
}

void _get_t_gc(){
    #if defined(_WIN64) || defined(_WIN32) || defined(_WIN16)
        #ifdef _MSC_VER || defined(__MINGW32__) || defined(__MINGW64__)
            _t_gc = (void*)(NtCurrentTeb()->NtTib.StackBase);
        #elif defined(__GNUC__)
            _t_gc = (void*)__builtin_frame_address(0);
        #else
            _t_gc = (void*)_AddressOfReturnAddress();
        #endif
    #elif defined(__linux__)
        #if defined(__GNUC__) || defined(__clang__)
            _t_gc = (void*)__builtin_frame_address(0);
        #elif defined(__arm__) || defined(__aarch64__)
            __asm__("mov %0, sp" : "=r" (_t_gc)); 
        #elif defined(__x86_64__)
            __asm__("movq %%rsp, %0" : "=r" (_t_gc)); 
        #else
            __asm__("movl %%esp, %0" : "=r" (_t_gc)); 
        #endif  
    #endif
}


static MemObject* _fill_block(TornadoMemory* mem, void** var_ptr, size_t object_size, uintptr_t block_addr) {
    MemObject* _new_obj = (MemObject*)block_addr;
    _inc_meta_used(mem, _mem_obj_meta_size);
    _set_mem_obj_size(_new_obj, (uintptr_t)object_size);
    _set_mem_obj_free_status(_new_obj, false);
    _set_mem_obj_assoc_var_ptr(_new_obj, var_ptr);
    *var_ptr = (void*)_get_data_addr(block_addr);
    _inc_used(mem, object_size);
    return _new_obj;
}


static bool _gc_scan_(TornadoMemory* mem) {
    MemObject* __temp = _get_first_live_obj_ptr(mem);
    MemObject* next;
    while(__temp){
        next = _get_mem_obj_next(__temp);
        void* _data_addr = (void*)_get_data_addr((uintptr_t)__temp);
        void** var_ptr = _get_mem_obj_assoc_var_ptr(__temp);
        if ((uintptr_t)var_ptr >= (uintptr_t)_b_gc && (uintptr_t)var_ptr <= (uintptr_t)_t_gc){
            bool _found = false;
            unsigned char **current = (unsigned char **)_t_gc;
            void *php = (void*)current ;
            while (php && (php >= _b_gc)) {
                if (php == var_ptr){
                    _found = true;
                    if (*current != _data_addr){ __Dealloc_BLOCK(mem, __temp); }
                    break; }
                current--;
                php = (void*)current; }
            if (!_found) {__Dealloc_BLOCK(mem, __temp);}}
        else { __Dealloc_BLOCK(mem, __temp);}
        __temp = next;
    }
}

static void _find_next_hole(TornadoMemory* mem){
    MemObject* __temp = _get_live_temp(mem);
    MemObject* ___temp_next = _get_mem_obj_next(__temp);
    while (__temp && ___temp_next && \
     (_get_next_block_addr((uintptr_t)__temp, _get_mem_obj_size(__temp)) == (uintptr_t)___temp_next)){
        __temp = ___temp_next;
        ___temp_next = _get_mem_obj_next(___temp_next);
    }
    if (__temp && ___temp_next){
        _set_first_hole_addr(mem, _get_next_block_addr((uintptr_t)__temp, _get_mem_obj_size(__temp)));
        _set_live_temp(mem, ___temp_next);
        return;
    }
    _set_first_hole_addr(mem, tornado_nullptr_addr);
    _set_live_temp(mem,NULL);
}

static bool start_def(TornadoMemory* mem, void** var_ptr_temp, size_t size){
    MemObject* ___live_temp = _get_live_temp(mem);
    uintptr_t __f_hole_addr = _get_first_hole_addr(mem);
    while (___live_temp){ 
        MemObject* ___live_temp_next = _get_mem_obj_next(___live_temp);
        MemObject* ___live_temp_prev = _get_mem_obj_prev(___live_temp);
        if (_get_DEF_OP(mem) && (__f_hole_addr != tornado_nullptr_addr) && \
            _fits_in(__f_hole_addr, (uintptr_t)___live_temp, size)){
            MemObject* block = _fill_block(mem, var_ptr_temp, size, __f_hole_addr);
            _set_mem_obj_next(block, ___live_temp);
            _set_mem_obj_prev(block, ___live_temp_prev);
            _set_mem_obj_prev(___live_temp, block);
            if (___live_temp_prev){ _set_mem_obj_next(___live_temp_prev, block);}
            uintptr_t _next_block = _get_next_block_addr(__f_hole_addr, size);
            (_next_block == (uintptr_t)___live_temp) ? _find_next_hole(mem) : _set_first_hole_addr(mem, _next_block);
            return true;}
        void** var_ptr = _get_mem_obj_assoc_var_ptr(___live_temp); 
        void* _meta_dest = _write_data((void*)___live_temp, (void*)__f_hole_addr, _mem_obj_meta_size);
        MemObject* _current = (MemObject*)_meta_dest;
        _set_mem_obj_prev(_current, ___live_temp_prev);
        _set_mem_obj_next(_current, ___live_temp_next);
        _set_mem_obj_assoc_var_ptr(_current, var_ptr); 
        if (___live_temp_prev){ _set_mem_obj_next(___live_temp_prev, _current); }
        if (___live_temp_next){ _set_mem_obj_prev(___live_temp_next, _current); }
        size_t obj_s = (size_t)_get_mem_obj_size(_current);
        void* _data_dest = (_fits_in((uintptr_t)_current, (uintptr_t)_get_meta((uintptr_t)*var_ptr), obj_s)) ? \
        _write_data((void*)*var_ptr, (void*)_get_data_addr((uintptr_t)_current), obj_s) : \
        _write_safe((void*)*var_ptr, (void*)_get_data_addr((uintptr_t)_current), obj_s);
        *var_ptr = _data_dest;
        uintptr_t _current_next_block = _get_next_block_addr((uintptr_t)_current, obj_s);
        _set_first_hole_addr(mem, _current_next_block);
        __f_hole_addr = _current_next_block;
        if (___live_temp == _get_first_live_obj_ptr(mem)){ _set_first_live_obj_ptr(mem, _current); }
        if (___live_temp == _get_last_live_obj_ptr(mem)){ _set_last_live_obj_ptr(mem, _current);}
        _set_live_temp(mem, ___live_temp_next);
        ___live_temp = ___live_temp_next; 
    } 
    if (__f_hole_addr){ _set_next_addr(mem, __f_hole_addr); }
    _set_first_hole_addr(mem, tornado_nullptr_addr);
    _set_live_temp(mem, NULL);
    return false;
}

static void _init_gc(TornadoMemory* mem){
    _get_b_gc_ptr = _get_mem_gc_op(mem) ? _get_b_gc_op : _get_b_gc;
    _get_b_gc_ptr();
    if ((uintptr_t)_b_gc > (uintptr_t)_t_gc){
        void* t = _b_gc;
        _b_gc = _t_gc;
        _t_gc = t;}
    unsigned short _c_ = _get_mem_gc_op(mem) ? 1 : _get_mem_gc_level(mem);
    while (_c_){_gc_scan_(mem); _c_--;}
}

void __Destroy_ALL(TornadoMemory* mem) {
    void* ___pool = (void*)_get_mem_pool(mem);
    if (___pool){
        gen_free(___pool);
        _set_mem_pool(mem, tornado_nullptr_addr);
        gen_free((void*)mem);
    }      
}

static inline bool _is_available(TornadoMemory* mem, size_t size){
    return _get_next_block_addr(_get_next_addr(mem), size) <= (uintptr_t)(_get_mem_pool(mem) \
        + _get_mem_size(mem));
}


void __alloc_mem(TornadoMemory* mem, void** var_ptr, size_t size){
    if (_is_available(mem, size)){ allocate_at_end(mem, var_ptr, size); }
    else {
        if (_get_mem_gc(mem)){ _init_gc(mem); }
        if (!start_def(mem, var_ptr, size)){
            _is_available(mem, size) ? allocate_at_end(mem, var_ptr, size) : \
            (__Destroy_ALL(mem), throwErr(MEM_LIMIT));
        }
    }
}

TornadoMemory* __Initial_memory(size_t total_size) {
    TornadoMemory* memory_obj = create_memory_pool(total_size);
    _mem_obj_meta_size = _get_mem_obj_meta_size();
    return memory_obj;
}

void __Dealloc_ALL(TornadoMemory* mem){
    MemObject* __temp = _get_first_live_obj_ptr(mem);
    MemObject* next;
    while(__temp){
        next = _get_mem_obj_next(__temp);
        __Dealloc_BLOCK(mem, __temp);
        __temp = next;
    }
    reset_configs(mem);
}

void __Dealloc_BLOCK(TornadoMemory* mem, MemObject* mem_obj){
    size_t _obj_size = (size_t)_get_mem_obj_size(mem_obj);
    _set_mem_obj_free_status(mem_obj, true);
    _set_mem_obj_size(mem_obj, (uintptr_t)0);
    _set_mem_obj_assoc_var_ptr(mem_obj, NULL);
    _dec_used(mem, _obj_size);
    _dec_meta_used(mem, _mem_obj_meta_size);
    uintptr_t __f_hole_addr = _get_first_hole_addr(mem);
    if (__f_hole_addr == tornado_nullptr_addr || (uintptr_t)mem_obj < __f_hole_addr){ 
        _set_first_hole_addr(mem,(uintptr_t)mem_obj);
        _set_live_temp(mem,_get_mem_obj_next(mem_obj));
    } 
    MemObject* ___live_temp = _get_live_temp(mem);
    if (mem_obj == ___live_temp){ _set_live_temp(mem,_get_mem_obj_next(___live_temp)); }
    MemObject* last_live_obj_ptr = _get_last_live_obj_ptr(mem);
    MemObject* first_live_obj_ptr = _get_first_live_obj_ptr(mem);
    if (first_live_obj_ptr == last_live_obj_ptr){ reset_configs(mem);}
    else if (mem_obj == first_live_obj_ptr){ 
        _set_first_live_obj_ptr(mem, _get_mem_obj_next(first_live_obj_ptr));
        _set_mem_obj_prev(_get_first_live_obj_ptr(mem), NULL);
        _set_mem_obj_next(mem_obj, NULL);
    }
    else if(mem_obj == last_live_obj_ptr){
        _set_last_live_obj_ptr(mem,_get_mem_obj_prev(last_live_obj_ptr));
        _set_mem_obj_next(_get_last_live_obj_ptr(mem), NULL);
        _set_mem_obj_prev(mem_obj, NULL);
        _set_next_addr(mem, (uintptr_t)last_live_obj_ptr);
        __f_hole_addr = _get_first_hole_addr(mem);
        if ((uintptr_t)_get_last_live_obj_ptr(mem) < __f_hole_addr){
            _set_live_temp(mem, NULL) ;
            _set_first_hole_addr(mem, tornado_nullptr_addr);
            _set_next_addr(mem, __f_hole_addr);
        }
    }
    else {
        MemObject* __prev = _get_mem_obj_prev(mem_obj);
        MemObject* __next = _get_mem_obj_next(mem_obj);
        _set_mem_obj_next(__prev, __next);
        _set_mem_obj_prev(__next, __prev);
    }
}

void __Dealloc_obj(TornadoMemory* mem, void** var_ptr){
    if (var_ptr == NULL || *var_ptr == NULL ){
        __Destroy_ALL(mem);
        throwErr(NULL_VAR);
    }
    MemObject* obj = _get_meta((uintptr_t)*var_ptr);;
    if (_get_mem_obj_free_status(obj) == true){
        __Destroy_ALL(mem);
        throwErr_dealloc(obj, DEALLOC_FAILURE_ERR_FREED);
    }
    __Dealloc_BLOCK(mem, obj);
}

