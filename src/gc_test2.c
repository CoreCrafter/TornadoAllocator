
#include "talloc.h"
#include <stdio.h>
#include <string.h>


TornadoMemory* tm;
char* tornado_strcat(const char* a, const char* b);
void run_program();

char* tornado_strcat(const char* a, const char* b){
    size_t a_size = strlen(a);  
    size_t b_size = strlen(b);  
    size_t total_size = a_size + b_size;

    char* result;
    tornado_allocate(tm, result, sizeof(char) * (total_size + 1));  
	
	
	printf("allocated in tornado_strcat function :      %p\n", (void*)result);

    for (size_t i = 0; i < a_size; i++){
        result[i] = a[i];
        
    }


    for (size_t i = 0; i < b_size; i++){
        result[a_size + i] = b[i];
       
    }


    result[total_size] = '\0';
	
    return result;
}


void run_program(){
	tm = tornado_initial_heap_memory(31); // 7 bytes + 24 bytes metadata
	

	printf("result is : %s\n",tornado_strcat("abc", "edf"));
	
	char* result;
    tornado_allocate(tm, result, sizeof(char) * 7); 
    printf("allocated out of tornado_strcat function :  %p\n", (void*)result); 

	tornado_destroy_memory(tm);
}

int main(int argc, const char* argv[]){


    TORNADO_CONF; // Configure the tornado
    
    // by default partial defragmentation is enabled you can use "tornado_set_defrag_op(tm);" to disable it 
    
    // DO NOT ALLOCATE MEMORY WITHIN THE MAIN FUNCTION
    
    run_program();
    
    return 0;
}

