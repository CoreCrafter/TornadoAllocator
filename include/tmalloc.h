
#ifndef MEM_INIT
#define MEM_INIT
#include "helpers/allocator.h"
#include "utils/common_libs.h"
#include "utils/errors/handle_err.h"
#include "helpers/meta/memory_met.h"
extern bool _conf_set;
#define TORNADO_CONF_GC \
do {if (_conf_set){throwErr(ERR_GC_DUP);}_get_t_gc();_conf_set = true;} while (0);
TornadoMemory* tornado_initial_heap_memory(size_t total_size);
void tornado_allocate_memory(TornadoMemory* mem, void** var_ptr, size_t size);
void tornado_set_gc(TornadoMemory* mem);
void tornado_set_gc_level(TornadoMemory* mem, unsigned short _level);
void tornado_set_gc_op(TornadoMemory* mem);
void tornado_unset_gc_op(TornadoMemory* mem);
inline void tornado_unset_gc(TornadoMemory* mem){unset_gc(mem);}
inline void tornado_set_defrag_op(TornadoMemory* mem){set_def_op(mem);}
inline void tornado_unset_defrag_op(TornadoMemory* mem){unset_def_op(mem);}
inline void tornado_deallocate_all(TornadoMemory* mem) {__Dealloc_ALL(mem);}
inline void tornado_destroy(TornadoMemory* mem){__Destroy_ALL(mem);}
inline void tornado_deallocate_memory(TornadoMemory* mem, void** var_ptr) {__Dealloc_obj(mem, var_ptr);}

#endif
