

#ifndef MEM_METADATA
#define MEM_METADATA

#include "../../utils/common_libs.h"
#include "memory_obj_met.h"
#include "../../utils/errors/handle_err.h"
#include "../../api/alloc_api/libs.h"

typedef struct {
    uintptr_t __pool;
    uintptr_t __first_hole_addr;
    uintptr_t __next_addr;
    size_t __used;  
    size_t __size;
    size_t __meta_used;
    MemObject* first_live_obj_ptr;
    MemObject* last_live_obj_ptr;
    MemObject* ___live_temp;
    unsigned short _gc_level_;
    bool _GC_OP_;
    bool __GC__;
    bool _DEF_OP_;
    bool __init__;
} TornadoMemory;

void reset_configs(TornadoMemory* mem);
TornadoMemory* create_memory_pool(size_t total_size);

inline void _set_mem_init(TornadoMemory* mem, bool boolean){ mem->__init__ = boolean; };
inline void _set_first_hole_addr(TornadoMemory* mem, uintptr_t addr) { mem->__first_hole_addr = addr; }
inline void _set_next_addr(TornadoMemory* mem, uintptr_t addr) { mem->__next_addr = addr; }
inline void _set_first_live_obj_ptr(TornadoMemory* mem, MemObject* ptr) { mem->first_live_obj_ptr = ptr; }
inline void _set_last_live_obj_ptr(TornadoMemory* mem, MemObject* ptr) { mem->last_live_obj_ptr = ptr; }
inline void _set_live_temp(TornadoMemory* mem, MemObject* temp) { mem->___live_temp = temp; }
inline void _set_DEF_OP(TornadoMemory* mem, bool op) { mem->_DEF_OP_ = op; }
inline void _set_mem_size(TornadoMemory* mem, size_t size){ mem->__size = size; }
inline void _set_mem_used(TornadoMemory* mem, size_t size){ mem->__used = size; }
inline void _set_mem_pool(TornadoMemory* mem, uintptr_t pool){ mem->__pool = pool; }
inline void _set_mem_meta_used(TornadoMemory* mem, size_t size){ mem->__meta_used = size; }
inline void _set_mem_gc(TornadoMemory* mem, bool gc){ mem->__GC__ = gc; }
inline void _set_mem_gc_op(TornadoMemory* mem, bool gc_op){ mem->_GC_OP_ = gc_op; }
inline void _set_mem_gc_level(TornadoMemory* mem, unsigned short _level){ mem->_gc_level_ = _level; }
inline uintptr_t _get_first_hole_addr(const TornadoMemory* mem) { return mem->__first_hole_addr; }
inline uintptr_t _get_next_addr(const TornadoMemory* mem) { return mem->__next_addr; }
inline MemObject* _get_first_live_obj_ptr(const TornadoMemory* mem) { return mem->first_live_obj_ptr; }
inline MemObject* _get_last_live_obj_ptr(const TornadoMemory* mem) { return mem->last_live_obj_ptr; }
inline MemObject* _get_live_temp(const TornadoMemory* mem) { return mem->___live_temp; }
inline bool _get_DEF_OP(const TornadoMemory* mem) { return mem->_DEF_OP_; }
inline bool _get_mem_init(const TornadoMemory* mem){ return mem->__init__;}
inline bool _get_mem_gc(TornadoMemory* mem){return mem->__GC__; }
inline bool _get_mem_gc_op(TornadoMemory* mem){ return mem->_GC_OP_ ; }
inline size_t _get_mem_size(const TornadoMemory* mem){ return mem->__size; }
inline size_t _get_mem_used(const TornadoMemory* mem){ return mem->__used; }
inline size_t _get_mem_meta_used(const TornadoMemory* mem){ return mem->__meta_used; }
inline uintptr_t _get_mem_pool(const TornadoMemory* mem){ return mem->__pool; }
inline unsigned short _get_mem_gc_level(TornadoMemory* mem){return mem->_gc_level_ ; }




inline void _inc_meta_used(TornadoMemory* mem, size_t size){ _set_mem_meta_used(mem, _get_mem_meta_used(mem) + size);}
inline void _dec_meta_used(TornadoMemory* mem, size_t size){ _set_mem_meta_used(mem, _get_mem_meta_used(mem) - size);}
inline void _dec_used(TornadoMemory* mem, size_t size){ _set_mem_used(mem, _get_mem_used(mem) - size);}
inline void _inc_used(TornadoMemory* mem, size_t size){ _set_mem_used(mem, _get_mem_used(mem) + size);}

#endif
