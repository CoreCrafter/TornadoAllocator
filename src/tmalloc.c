

#include "../include/tmalloc.h"

bool _conf_set = false;
void tornado_allocate_memory(TornadoMemory* mem, void** var_ptr, size_t size){
    if (size < 1){
        tornado_destroy(mem);
        throwErr(OBJ_MEM_SIZE_ERR);
    }
    if (!_get_mem_init(mem)){
        tornado_destroy(mem);
    	throwErr(MEM_INIT_ERR);
    }
    __alloc_mem(mem, var_ptr, size);
}
void tornado_set_gc(TornadoMemory* mem){
    if (!_conf_set){
        tornado_destroy(mem);
        throwErr(ERR_GC_CONF);
    }
    set_gc(mem);
}
void tornado_set_gc_level(TornadoMemory* mem, unsigned short _level){
    if (!_get_mem_gc(mem)){
        tornado_destroy(mem);
        throwErr(MEM_GC_DIS);
    }
    if (_level < 1){
        tornado_destroy(mem);
        throwErr(GC_LVL_LOW);
    }
    set_gc_level_memory(mem, _level);}

void tornado_set_gc_op(TornadoMemory* mem){
    if (!_get_mem_gc(mem)){
        tornado_destroy(mem);
        throwErr(MEM_GC_DIS);
    }
    set_gc_op(mem);
}
void tornado_unset_gc_op(TornadoMemory* mem){
    if (!_get_mem_gc(mem)){
        tornado_destroy(mem);
        throwErr(MEM_GC_DIS);
    }
    unset_gc_op(mem);
}
TornadoMemory* tornado_initial_heap_memory(size_t total_size){
    if (total_size < 1){
        throwErr(MEM_SIZE_ERR);
    }
    TornadoMemory* mem = __Initial_memory(total_size);
    _set_mem_init(mem, true);
    return mem;
    
}



