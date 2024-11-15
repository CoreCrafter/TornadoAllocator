
#ifndef API_ALLOC
#define API_ALLOC

#include "../../utils/common_libs.h"

inline void gen_free(void* sys_ptr){free(sys_ptr);}
inline void* _write_safe(void* source, void* destination, size_t size){return memmove(destination, source, size);}
inline void* _write_data(void* source, void* destination, size_t size){return memcpy(destination, source, size);}
inline void *gen_allocate(size_t size){return malloc(size);}
#endif
