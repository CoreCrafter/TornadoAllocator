

#ifndef MEM_METADATA
#define MEM_METADATA

#include "../../utils/common_libs.h"
#include "memory_obj_met.h"
#include "../../utils/errors/handle_err.h"
#include "../../api/alloc_api/libs.h"

#define TORNADO_MEM_F_LIVE_MEMBER(mem) mem->first_live_obj_ptr

typedef struct {
    uintptr_t __pool;
    uintptr_t __first_hole_addr;
    uintptr_t __next_addr;
    size_t __used_;  
    size_t __size;
    size_t __meta_used;
    MemObject* first_live_obj_ptr;
    MemObject* last_live_obj_ptr;
    MemObject* ___live_temp;
    bool _DEF_OP_;
    bool _GC_;
    bool __init__;
} TornadoMemory;

void reset_configs(TornadoMemory* mem);
TornadoMemory* create_memory_pool(size_t total_size);
void _set_mem_init(TornadoMemory* mem, bool boolean);
void _set_first_hole_addr(TornadoMemory* mem, uintptr_t addr);
void _set_next_addr(TornadoMemory* mem, uintptr_t addr);
void _set_first_live_obj_ptr(TornadoMemory* mem, MemObject* ptr);
void _set_last_live_obj_ptr(TornadoMemory* mem, MemObject* ptr);
void _set_live_temp(TornadoMemory* mem, MemObject* temp);
void _set_DEF_OP(TornadoMemory* mem, bool op);
void _set_mem_gc(TornadoMemory* mem, bool boolean);
void _set_mem_size(TornadoMemory* mem, size_t size);
void _set_mem_used(TornadoMemory* mem, size_t size);
void _set_mem_pool(TornadoMemory* mem, uintptr_t pool);
void _set_mem_meta_used(TornadoMemory* mem, size_t size);
uintptr_t _get_first_hole_addr(const TornadoMemory* mem);
uintptr_t _get_next_addr(const TornadoMemory* mem);
MemObject* _get_first_live_obj_ptr(const TornadoMemory* mem);
MemObject* _get_last_live_obj_ptr(const TornadoMemory* mem);
MemObject* _get_live_temp(const TornadoMemory* mem);
bool _get_DEF_OP(const TornadoMemory* mem);
bool _get_mem_init(const TornadoMemory* mem);
size_t _get_mem_size(const TornadoMemory* mem);
size_t _get_mem_used(const TornadoMemory* mem);
bool _get_mem_gc(TornadoMemory* mem);
size_t _get_mem_meta_used(const TornadoMemory* mem);
uintptr_t _get_mem_pool(const TornadoMemory* mem);
void _inc_meta_used(TornadoMemory* mem, size_t size);
void _dec_meta_used(TornadoMemory* mem, size_t size);
void _dec_used(TornadoMemory* mem, size_t size);
void _inc_used(TornadoMemory* mem, size_t size);

#endif
