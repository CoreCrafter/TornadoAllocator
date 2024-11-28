
#ifndef MEM_OBJ_META
#define MEM_OBJ_META

#include "../../utils/common_libs.h"

typedef struct memory_obj {
    struct memory_obj* __next_obj;
    struct memory_obj* __prev_obj;
    size_t __memObj_obj_size;
} MemObject;

void _set_mem_obj_reachable_status(MemObject* mem_obj, bool flag);
void _set_mem_obj_next(MemObject* mem_obj, MemObject* live_mem_obj);
void _set_mem_obj_prev(MemObject* mem_obj, MemObject* live_mem_obj);
void _set_mem_obj_size(MemObject* mem_obj, size_t size);
size_t _get_mem_obj_meta_size() ;
size_t _get_mem_obj_size(const MemObject* mem_obj);
bool _get_mem_obj_reachable_status(const MemObject* mem_obj);
bool _is_mem_obj_reachable(const MemObject* mem_obj);
MemObject* _get_mem_obj_next(const MemObject* mem_obj);
MemObject* _get_mem_obj_prev(const MemObject* mem_obj);

#endif
