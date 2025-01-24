
#include "talloc.h"
#include <stdio.h>
#include <string.h>


TornadoMemory* tm;
TornadoMemory* tm2;
void run_program();

typedef struct {
    void* data;
    int a;
} Item;



void allocate_in_(){
    char* r;
    tornado_allocate(tm, r, sizeof(char) * 3);
    r[0] = 'm';
    r[1] = 'o';
    r[2] = '\0';
    printf("allocated in tm  %p\n", (void*)r);
    Item* d;
    tornado_allocate(tm2, d, sizeof(Item));
   	printf("allocated in tm2 %p\n", (void*)d);

    d->a = 4;
    d->data = r;
    
    Item* d2;
    tornado_allocate(tm2, d2, sizeof(Item));
   	printf("allocated in tm2 %p\n", (void*)d2);

    d2->a = 4;
    d2->data = d;

   

}


void run_program(){
	tm = tornado_initial_heap_memory(27); // 3 bytes + 24 bytes metadata
	tm2 = tornado_initial_heap_memory(200); 

    allocate_in_();

    char* r;
    tornado_allocate(tm, r, sizeof(char) * 3);
    printf("allocated in run program %p\n", (void*)r);


	tornado_destroy_all();
}

int main(int argc, const char* argv[]){


    TORNADO_CONF; // Configure the tornado
    
    // by default partial defragmentation is enabled you can use "tornado_set_defrag_op(tm);" to disable it 
    
    // DO NOT ALLOCATE MEMORY WITHIN THE MAIN FUNCTION
    
    run_program();
    
    return 0;
}

