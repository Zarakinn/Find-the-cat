#include <dirent.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h>
#include <time.h>
#include <regex.h>
#include "parameterStruct.h"
#include "../lib/MegaMimes.h"

bool matchCondition(struct dirent* file, const char* filename, struct stat statBuffer, parameter* param);
