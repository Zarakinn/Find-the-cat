#include <dirent.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h>
#include <time.h>
#include "parameterStruct.h"

bool matchCondition(struct dirent* file, struct stat statBuffer, parameter* param);
