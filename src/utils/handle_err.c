
#include "../../include/utils/errors/handle_err.h"


void throwErr(const char *msg) {
    printf("\n[!] Runtime Error:\n\n");
    printf("-> %s", msg);
    printf("\n\n");
    exit(EXIT_FAILURE);
}

void throwErr_dealloc(void *object, const char *msg) {
    printf("\n[!] Runtime Error:\n\n");
    printf("-> Memory at <%p> : %s", object, msg);
    printf("\n\n");
    exit(EXIT_FAILURE);
}
