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
#define ERR_SCN_ "Internal Error | handling segmentations has failed"
#define FTL_ERR "Fatal Error"
#define UNKNOWN_ARCH "Unknown Platform"
#define FTL_ERR_DEL "Fatal Error | Internal pool deletion failed"
#define IND_MEM_ARR_OB "Fatal Error | Tornado memory structure indexing error"
#define DEALLOC_OUT_OF_RANGE "deallocation failed | doesn't belong to the specified memory pool"
#define DEALLOC_ERR_OBJ "deallocation failed | wrong object"
#define ERR__CONF "use \"TORNADO_CONF\" at the top of your main function."
#define ERR__DUP "Duplicate use of \"TORNADO_CONF\""
#define DEALLOC_FAILURE_ERR_FREED "deallocation failed | might be freed before"
#define MEM_SIZE_ERR "memory size should be at least 1 byte"
#define OBJ_MEM_SIZE_ERR "memory allocated for obj size should be at least 1 byte"
#define MEM_INIT_ERR "initial memory is not set yet"


void throwErr(const char *msg);
void throwErr_dealloc(void *object, const char *msg);

#endif

