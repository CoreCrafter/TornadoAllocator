
#include "tmalloc.h"


int main(int argc, const char* argv[]){


	TornadoMemory* tm = tornado_initial_heap_memory(208);
 
	tornado_set_defrag_op(tm);


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
	printf("Allocated 4 objects :\n");
	printf("address : %p\nstring1: %s\n",(void*)a, a);
	printf("address : %p\nstring2: %s\n",(void*)b, b);
	printf("address : %p\nstring3: %s\n",(void*)c, c);
	printf("address : %p\nstring4: %s\n\n",(void*)d, d);
	
	tornado_deallocate_memory(tm, (void**)&a);
	tornado_deallocate_memory(tm, (void**)&c);
	printf("after deleting a and c: \n");
	
	printf("address : %p\nstring2: %s\n",(void*)b, b);
	printf("address : %p\nstring4: %s\n\n",(void*)d, d);
	tornado_allocate_memory(tm, (void**)&a, sizeof(char) * 20);
	a[0] = 'a';
	a[1] = 'o';
	a[2] = '\0';
	printf("address : %p\nstring1: %s\n",(void*)a, a);
	printf("address : %p\nstring2: %s\n",(void*)b, b);
	printf("address : %p\nstring4: %s\n\n",(void*)d, d);
	tornado_allocate_memory(tm, (void**)&c, sizeof(char) * 20);
	c[0] = 'c';
	c[1] = 'o';
	c[2] = '\0';
	printf("address : %p\nstring1: %s\n",(void*)a, a);
	printf("address : %p\nstring2: %s\n",(void*)b, b);
	printf("address : %p\nstring2: %s\n",(void*)c, c);
	printf("address : %p\nstring4: %s\n",(void*)d, d);
	
	tornado_destroy(tm);
    return 0;
}


