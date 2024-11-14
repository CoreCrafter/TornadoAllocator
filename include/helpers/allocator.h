#ifndef MEM_ALLOC_PROC
#define MEM_ALLOC_PROC

#include "meta/memory_met.h"
#include "meta/memory_obj_met.h"
#include "../utils/errors/handle_err.h"
#include "../utils/common_libs.h"
#include "../api/alloc_api/libs.h"

extern uintptr_t tornado_nullptr_addr;
TornadoMemory* __Initial_memory(size_t total_size);
static MemObject* _fill_block(TornadoMemory* mem, void** var_ptr, size_t object_size, uintptr_t block_addr);
inline void set_gc_level_memory(TornadoMemory* mem, unsigned short _level){_set_mem_gc_level(mem, _level);}
inline void set_gc(TornadoMemory* mem){_set_mem_gc(mem, true);}
inline void unset_gc(TornadoMemory* mem){_set_mem_gc(mem,false);}
inline void set_gc_op(TornadoMemory* mem){_set_mem_gc_op(mem, true);}
inline void unset_gc_op(TornadoMemory* mem){_set_mem_gc_op(mem, false);}
inline void set_def_op(TornadoMemory* mem){_set_DEF_OP(mem, true);}
inline void unset_def_op(TornadoMemory* mem){_set_DEF_OP(mem, false);}
void __Dealloc_obj(TornadoMemory* mem, void** var_ptr);
void __alloc_mem(TornadoMemory* mem, void** var_ptr, size_t size);
void __Dealloc_ALL(TornadoMemory* mem);
void __Destroy_ALL(TornadoMemory* mem);
void __Dealloc_BLOCK(TornadoMemory* mem, MemObject* mem_obj);
void _get_t_gc();

#endif
