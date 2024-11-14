
#ifndef MEM_OBJ_META
#define MEM_OBJ_META

#include "../../utils/common_libs.h"



#define FLAG_MASK 1
#define SIZE_MASK (~FLAG_MASK)

typedef struct memory_obj {
    struct memory_obj* __next_obj;
    struct memory_obj* __prev_obj;
    void** __var_ptr;
    uintptr_t __memObj_obj_size;
} MemObject;

inline void _set_mem_obj_assoc_var_ptr(MemObject* mem_obj, void** var_ptr){ mem_obj->__var_ptr = var_ptr;}
inline void _set_mem_obj_next(MemObject* mem_obj, MemObject* live_mem_obj){ mem_obj->__next_obj = live_mem_obj;}
inline void _set_mem_obj_prev(MemObject* mem_obj, MemObject* live_mem_obj){ mem_obj->__prev_obj = live_mem_obj; }
inline void _set_mem_obj_size(MemObject* mem_obj, uintptr_t size){mem_obj->__memObj_obj_size = (mem_obj->__memObj_obj_size & FLAG_MASK) | (size & SIZE_MASK);}

inline size_t _get_mem_obj_meta_size() {return sizeof(MemObject);}
inline uintptr_t _get_mem_obj_size(const MemObject* mem_obj){return mem_obj->__memObj_obj_size & SIZE_MASK;}
inline bool _get_mem_obj_free_status(const MemObject* mem_obj){return mem_obj->__memObj_obj_size & FLAG_MASK;}
inline void** _get_mem_obj_assoc_var_ptr(const MemObject* mem_obj){return mem_obj->__var_ptr;}
inline MemObject* _get_mem_obj_next(const MemObject* mem_obj){return mem_obj->__next_obj;}
inline MemObject* _get_mem_obj_prev(const MemObject* mem_obj){return mem_obj->__prev_obj;}

inline void _set_mem_obj_free_status(MemObject* mem_obj, bool flag){
    if (flag){
        mem_obj->__memObj_obj_size |= FLAG_MASK;
    }
    else {
        mem_obj->__memObj_obj_size &= SIZE_MASK;
    } 
}


#endif
