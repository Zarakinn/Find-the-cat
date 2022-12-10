#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>

#ifndef new_parser
#define new_parser

// Coefficient de temps
#define m 3600;
#define H 60;
#define J 24;

// Coefficient de taille
#define c 1;
#define k 1024;
#define M 1048576;
#define G 1073741824;

long sizeInByte(char* size);

double timeInSecond(char* size);

typedef enum { GREATER, SMALLER, EQUAL} modifier;

typedef struct {
    const char* name;
    long size;
    modifier sizeModifier;
    double timeSinceLastAcess;
    modifier timeModifier;
    const char* type;
    const char* regex;
    const char* patern;
    bool isDir;
} parameter;



#define currentDir "."
#define parentDir ".."

DIR* loadDir(const char* filename);

void printDirectory(const char* path,parameter* param);

bool matchCondition(struct dirent* file, struct stat statBuffer, parameter* param);

#endif









