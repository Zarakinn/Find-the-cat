#include "explorer.h"
#include "parameterStruct.h"
#include "util.h"
#include "parser.h"

int main(int argc, char *argv[])
{


    parameter* param = parse(argc,argv);

    char source[64];
    strcpy(source,argv[1]);

    printDirectory(source,param);
    return EXIT_SUCCESS;
}
