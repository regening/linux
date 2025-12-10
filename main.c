#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>   
#include "ls.h"  

void list_a(const char *path, int show); 

int main(int argc, char *argv[]) {
    int show = 0;
    if(argc > 1 && strcmp(argv[1], "-a") == 0){
        show = 1;
    }
    list_a(".", show); 
    
    return 0;
}
