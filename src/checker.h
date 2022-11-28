#include <dirent.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>

bool matchCondition(struct dirent* file, struct stat statBuffer, int cond);
