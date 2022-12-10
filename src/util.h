#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef util
#define util

// Coefficient de temps
#define m 3600;
#define h 60;
#define j 24;

// Coefficient de taille
#define c 1;
#define k 1024;
#define M 1048576;
#define G 1073741824;

long sizeInByte(char* size);

double timeInSecond(char* size);

#endif
