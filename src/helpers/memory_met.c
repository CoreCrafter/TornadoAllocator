#include "../../include/helpers/meta/memory_met.h"

extern uintptr_t tornado_nullptr_addr;

TornadoMemory* create_memory_pool(const size_t total_size){
    size_t _size_of_meta = sizeof(TornadoMemory); 
    TornadoMemory * memory_obj = (TornadoMemory *)gen_allocate(_size_of_meta);
    if (!memory_obj){
        throwErr(MEMORY_ERR_MSG);
    } 
    uintptr_t _pool = (uintptr_t)gen_allocate(total_size);
    if (!_pool){
        gen_free(memory_obj);
        throwErr(MEMORY_ARR_ERR_MSG);
    }
    _set_mem_pool(memory_obj, _pool); 
    _set_mem_size(memory_obj,total_size); 
    _set_mem_used(memory_obj, 0); 
    _set_mem_meta_used(memory_obj, _size_of_meta);
    _set_first_hole_addr(memory_obj, tornado_nullptr_addr);
    _set_next_addr(memory_obj, _pool);
    _set_first_live_obj_ptr(memory_obj, NULL) ;
    _set_last_live_obj_ptr(memory_obj, NULL) ;
    _set_live_temp(memory_obj, NULL) ;
    _set_DEF_OP(memory_obj, true) ;
    _set_mem_gc(memory_obj, false);
    _set_mem_gc_level(memory_obj, 1);
    _set_mem_gc_op(memory_obj, true);
    return memory_obj;
}
void reset_configs(TornadoMemory* memory_obj){
    _set_first_hole_addr(memory_obj, tornado_nullptr_addr);
    _set_next_addr(memory_obj, _get_mem_pool(memory_obj));
    _set_first_live_obj_ptr(memory_obj, NULL) ;
    _set_last_live_obj_ptr(memory_obj, NULL) ;
    _set_live_temp(memory_obj, NULL) ;
    _set_mem_used(memory_obj, 0); 
    _set_mem_meta_used(memory_obj, sizeof(TornadoMemory));
}
