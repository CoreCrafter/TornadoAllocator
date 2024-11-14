#ifndef ERR_HANDLING
#define ERR_HANDLING

#include "../common_libs.h"

#define INITIAL_MEM_MAP_ERR "initializing memory mapping failed | allocation failed"
#define MEMORY_ERR_MSG "memory metadata cannot be created | allocation failed"
#define MEMORY_ARR_ERR_MSG "memory cannot be created | allocation failed"
#define MEM_OBJ_DET_ERR "memory object detection failed"
#define LIMIT_MEM_INIT "memory mapping error | too many initialization | allocation failed"
#define MEM_LIMIT "not enough space | memory limitation"
#define NULL_VAR "is NULL"
#define MEM_GC_DIS "GC is not enabled for that memory pool"
#define GC_LVL_LOW "GC level must be at least 1"
#define ERR_GC_CONF "use \"TORNADO_CONF_GC\" at the top of your main function."
#define ERR_GC_DUP "Duplicate use of \"TORNADO_CONF_GC\""
#define DEALLOC_FAILURE_ERR_FREED "deallocation failed | might be freed before"
#define MEM_SIZE_ERR "memory size should be at least 1 byte"
#define OBJ_MEM_SIZE_ERR "memory allocated for obj size should be at least 1 byte"
#define MEM_INIT_ERR "initial memory is not set yet"

void throwErr(const char *msg);
void throwErr_dealloc(void *object, const char *msg);

#endif

