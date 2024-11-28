
#include "talloc.h"

char* allocate_some_memories_again(TornadoMemory* tm){
    
    
    char* c;
    tornado_allocate(tm, c ,sizeof(char) * 20);
    c[0] = 'c';
    c[1] = 'o';
    c[2] = '\0';

	char* d;
    tornado_allocate(tm, d ,sizeof(char) * 20);
    d[0] = 'd';
    d[1] = 'o';
    d[2] = '\0';

    printf("allocated 2 more objects :\n");
    printf("address : %p\nstring3: %s\n",(void*)c, c);
    printf("address : %p\nstring4: %s\n\n",(void*)d, d);
    return d;
    
    
    
}

void allocate_some_memories(TornadoMemory* tm){
    
    
    char* a;
    tornado_allocate_memory(tm,(void**)&a, sizeof(char) * 20);
    a[0] = 'a';
    a[1] = 'o';
    a[2] = '\0';
	
    char* b;
    tornado_allocate_memory(tm,(void**)&b, sizeof(char) * 20);
    b[0] = 'b';
    b[1] = 'o';
    b[2] = '\0';
    

    printf("allocated 2 objects :\n");
    printf("address : %p\nstring1: %s\n",(void*)a, a);
    printf("address : %p\nstring2: %s\n",(void*)b, b);
    
    
}

void test(){
    TornadoMemory* tm = tornado_initial_heap_memory(208); // Allocating 208 bytes for memory

    allocate_some_memories(tm); 
    char* res = allocate_some_memories_again(tm);


    printf("after collecting garbages\n\n");


    char* a;
    tornado_allocate_memory(tm,(void**)&a, sizeof(char) * 20);
    a[0] = 'a';
    a[1] = 'o';
    a[2] = '\0';

    char* b;
    tornado_allocate_memory(tm,(void**)&b, sizeof(char) * 20);
    b[0] = 'b';
    b[1] = 'o';
    b[2] = '\0';
    
    printf("address : %p\nstring1: %s\n",(void*)a, a);
    printf("address : %p\nstring2: %s\n",(void*)b, b);
    printf("address : %p\nstring res: %s\n\n",(void*)res, res);
    tornado_destroy_memory(tm);
}

int main(int argc, const char* argv[]){


    TORNADO_CONF; // Configure the tornado
    
    // by default partial defragmentation is enabled you can use "tornado_set_defrag_op(tm);" to disable it 
    
    // DO NOT ALLOCATE MEMORY WITHIN THE MAIN FUNCTION
    
    test();
    
    return 0;
}

