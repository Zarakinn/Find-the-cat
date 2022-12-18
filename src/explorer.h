#include <dirent.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h>
#include "parameterStruct.h"

#define currentDir "."
#define parentDir ".."

void printFirst(const char* path,parameter* param);
void printDirectory(const char* path,parameter* param);
