#include <string.h>
#include <stdbool.h>

#ifndef parameterStruct
#define parameterStruct
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
#endif
