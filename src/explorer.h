#include <dirent.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>

#define currentDir "."
#define parentDir ".."

DIR* loadDir(const char* filename);

void printDirectory(const char* filename);
