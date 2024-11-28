#ifndef MEM_ALLOC_PROC
#define MEM_ALLOC_PROC

#include "meta/memory_met.h"
#include "meta/memory_obj_met.h"
#include "../utils/errors/handle_err.h"
#include "../utils/common_libs.h"
#include "../api/alloc_api/libs.h"

extern uintptr_t tornado_nullptr_addr;
TornadoMemory* __Initial_memory(size_t total_size);
void set_def_op(TornadoMemory* mem);
void unset_def_op(TornadoMemory* mem);
void __Dealloc_obj(TornadoMemory* mem, void* var_ptr);
void __alloc_mem(TornadoMemory* mem, void** var_ptr, size_t size);
void __Dealloc_ALL(TornadoMemory* mem);
void __Destroy_mem(TornadoMemory* mem);
void _get_t_GRBR();
void _get_b_SEG();
void unset_gc_(TornadoMemory* mem);
void set_gc_(TornadoMemory* mem);
void __init_internal_mem_arr();
void _destroy_internal();

#endif
