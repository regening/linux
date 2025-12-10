#include <dirent.h>     
#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     

void list_a(const char *path, int show){  //-a
    struct dirent *entry;
    DIR *dp = opendir(path);  
    if(dp == NULL){
        perror("opendir");
        return;
    }
    while((entry = readdir(dp)) != NULL){
        if(show || strcmp(entry->d_name, ".") != 0){
            printf("%s\n",entry -> d_name);
        }
    }
    closedir(dp); 
}

void list_i
