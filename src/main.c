#include "explorer.h"
#include "parameterStruct.h"
#include "util.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    parameter* param = parse(argc,argv);
    if (!param->carrySearch)
    {
        free(param);
        //printf("Exit\n");
        return EXIT_FAILURE;
    }
    char source[64];
    strcpy(source,argv[1]);

    if (source[strlen(source)-1] == '/')
    {
        source[strlen(source)-1] = '\0';
    }

    printDirectory(source,param);
    return EXIT_SUCCESS;
}
