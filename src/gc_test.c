
#include "tmalloc.h"

void allocate_some_memories_again(TornadoMemory* tm){
    char* c;
    char* d;
    tornado_allocate_memory(tm, (void**)&c, sizeof(char) * 20);
    c[0] = 'c';
    c[1] = 'o';
    c[2] = '\0';

    tornado_allocate_memory(tm, (void**)&d, sizeof(char) * 20);
    d[0] = 'd';
    d[1] = 'o';
    d[2] = '\0';
    printf("address : %p\nstring3: %s\n",(void*)c, c);
    printf("address : %p\nstring4: %s\n\n",(void*)d, d);
}

void allocate_some_memories(TornadoMemory* tm){
    char* a;
    char* b;
    char* s = "asdsa";
    tornado_allocate_memory(tm, (void**)&a, sizeof(char) * 20);
    a[0] = 'a';
    a[1] = 'o';
    a[2] = '\0';

    tornado_allocate_memory(tm, (void**)&b, sizeof(char) * 20);
    b[0] = 'b';
    b[1] = 'o';
    b[2] = '\0';
    
    
    printf("allocated 4 objects :\n");
    printf("address : %p\nstring1: %s\n",(void*)a, a);
    printf("address : %p\nstring2: %s\n",(void*)b, b);
    
    
}

int main(int argc, const char* argv[]){


    TORNADO_CONF_GC; // Configure the parameters for GC
    TornadoMemory* tm = tornado_initial_heap_memory(208); // Allocating 208 bytes for memory
    tornado_set_gc(tm); // Enabling GC for tm
    // by default Defragmentation optimization is enabled 

    tornado_set_defrag_op(tm); // Enabling Defragmentation optimization

    // by default GC optimization is enabled you can use "tornado_unset_gc_op(tm);" to disable it 


    allocate_some_memories(tm); 
    allocate_some_memories_again(tm);


    printf("after collecting garbages : \n\n");

    char* a;
    char* b;
    char* c;
    char* d;
    tornado_allocate_memory(tm, (void**)&a, sizeof(char) * 20);
    a[0] = 'a';
    a[1] = 'o';
    a[2] = '\0';

    tornado_allocate_memory(tm, (void**)&b, sizeof(char) * 20);
    b[0] = 'b';
    b[1] = 'o';
    b[2] = '\0';
    
    tornado_allocate_memory(tm, (void**)&c, sizeof(char) * 20);
    c[0] = 'c';
    c[1] = 'o';
    c[2] = '\0';

    tornado_allocate_memory(tm, (void**)&d, sizeof(char) * 20);
    d[0] = 'd';
    d[1] = 'o';
    d[2] = '\0';

    printf("* as you can see there are no memory leaks *\n\n");
    printf("address : %p\nstring1: %s\n",(void*)a, a);
    printf("address : %p\nstring2: %s\n",(void*)b, b);
    printf("address : %p\nstring3: %s\n",(void*)c, c);
    printf("address : %p\nstring4: %s\n\n",(void*)d, d);
    
    tornado_destroy(tm);
    return 0;
}

