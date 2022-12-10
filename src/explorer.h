#include <dirent.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h>
#include "parameterStruct.h"

#define currentDir "."
#define parentDir ".."

DIR* loadDir(const char* filename);

void printDirectory(const char* path,parameter* param);
