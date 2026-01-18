#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <linux/limits.h>
#include <dirent.h>

extern int a;  
extern int l;  
extern int R;  
extern int t;  
extern int r;  
extern int i;  
extern int s; 

int hidden(char *file);
void major(char *WAY);

#endif // TEST_H
