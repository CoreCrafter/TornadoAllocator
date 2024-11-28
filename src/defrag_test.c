
#include "talloc.h"


void allocate_some_memory(TornadoMemory* tm){
	char* a;
	char* b;
	char* c;
	char* d;
	tornado_allocate(tm, a, sizeof(char) * 20);
	a[0] = 'a';
	a[1] = 'o';
	a[2] = '\0';

	tornado_allocate(tm, b, sizeof(char) * 20);
	b[0] = 'b';
	b[1] = 'o';
	b[2] = '\0';
	
	tornado_allocate(tm, c, sizeof(char) * 20);
	c[0] = 'c';
	c[1] = 'o';
	c[2] = '\0';

	tornado_allocate(tm, d, sizeof(char) * 20);
	d[0] = 'd';
	d[1] = 'o';
	d[2] = '\0';
	printf("Allocated 4 objects :\n");
	printf("address : %p\nstring1: %s\n",(void*)a, a);
	printf("address : %p\nstring2: %s\n",(void*)b, b);
	printf("address : %p\nstring3: %s\n",(void*)c, c);
	printf("address : %p\nstring4: %s\n\n",(void*)d, d);

	tornado_free(tm, a);
	tornado_free(tm, c);
	printf("after deleting a and c: \n");
	
	printf("address : %p\nstring2: %s\n",(void*)b, b);
	printf("address : %p\nstring4: %s\n\n",(void*)d, d);
	tornado_allocate(tm, a, sizeof(char) * 20);
	a[0] = 'a';
	a[1] = 'o';
	a[2] = '\0';
	printf("address : %p\nstring1: %s\n",(void*)a, a);
	printf("address : %p\nstring2: %s\n",(void*)b, b);
	printf("address : %p\nstring4: %s\n\n",(void*)d, d);
	tornado_allocate(tm, c, sizeof(char) * 20);
	c[0] = 'c';
	c[1] = 'o';
	c[2] = '\0';
	printf("address : %p\nstring1: %s\n",(void*)a, a);
	printf("address : %p\nstring2: %s\n",(void*)b, b);
	printf("address : %p\nstring3: %s\n",(void*)c, c);
	printf("address : %p\nstring4: %s\n",(void*)d, d);
	
}

int main(int argc, const char* argv[]){

	TORNADO_CONF; // Configure the tornado

	TornadoMemory* tm = tornado_initial_heap_memory(208);
 
 	// by default partial defragmentation is enabled you can use "tornado_unset_defrag_op(tm);" to disable it 
	// tornado_unset_defrag_op(tm);

	// * DO NOT ALLOCATE MEMORY DIRECTLY HERE IN THE MAIN FUNCTION

	allocate_some_memory(tm);

	
	tornado_destroy_memory(tm);
    return 0;
}


