
#ifndef MEM_INIT
#define MEM_INIT
#include "helpers/allocator.h"
#include "utils/common_libs.h"
#include "utils/errors/handle_err.h"
#include "helpers/meta/memory_met.h"
extern bool _conf_set;
#define TORNADO_CONF \
do {if (_conf_set){throwErr(ERR__DUP);}__init_internal_mem_arr();_get_b_SEG();_get_t_GRBR();_conf_set = true;} while (0);
#define tornado_allocate(tm, var, size) tornado_allocate_memory(tm, (void**)&var, size);
#define tornado_free(tm, var) tornado_deallocate_memory(tm, (void*)var);
TornadoMemory* tornado_initial_heap_memory(size_t total_size);
void tornado_allocate_memory(TornadoMemory* mem, void** var_ptr, size_t size);
void tornado_set_gc(TornadoMemory* mem);
void tornado_unset_gc(TornadoMemory* mem);
void tornado_set_defrag_op(TornadoMemory* mem);
void tornado_unset_defrag_op(TornadoMemory* mem);
void tornado_deallocate_all(TornadoMemory* mem);
void tornado_destroy_memory(TornadoMemory* mem);
void tornado_destroy_all();
void tornado_deallocate_memory(TornadoMemory* mem, void* var_ptr);

#endif
