#include <dirent.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h>
#include <time.h>
#include "parameterStruct.h"
#include "MegaMimes.h"

bool matchCondition(struct dirent* file, const char* filename, struct stat statBuffer, parameter* param);
