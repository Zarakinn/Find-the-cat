#include "explorer.h"
#include "parameterStruct.h"
#include "util.h"

int main(int argc, char const *argv[])
{
    printf("Size : %ld\n",sizeInByte("1"));
    printf("Size : %ld\n",sizeInByte("67"));
    printf("Size : %ld\n",sizeInByte("10k"));
    printf("Size : %ld\n",sizeInByte("10G"));

    printf("Temps en sec : %f\n", timeInSecond("5"));
    printf("Temps en sec : %f\n", timeInSecond("5m"));
    printf("Temps en sec : %f\n", timeInSecond("10h"));
    printf("Temps en sec : %f\n", timeInSecond("2j"));


    parameter* param = (parameter*)malloc(sizeof(parameter));
    param->name = "s";

    printDirectory(".",param);

    return 0;
}
