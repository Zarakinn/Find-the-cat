#include "explorer.h"
#include "parameterStruct.h"

int main(int argc, char const *argv[])
{
    
    parameter* param = (parameter*)malloc(sizeof(parameter));
    param->name = "s";

    printDirectory(".",param);

    return 0;
}
