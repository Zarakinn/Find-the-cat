#include "explorer.h"
#include "checker.h"


void printFirst(const char* path, parameter* param)
{

    DIR* dir = opendir(path);
    if (dir == NULL)
    {
        return;
    }

    struct dirent* file;
    struct stat statBuffer;

    while ((file = readdir(dir)) != NULL)
    {
        if (strcmp(file->d_name,currentDir))
        {
            continue;
        }
        
        stat(path,&statBuffer);

        if (matchCondition(file,path,statBuffer,param))
            printf("%s\n",path);
    }
    closedir(dir);
    printDirectory(path,param);
}



void printDirectory(const char* path,parameter* param)
{
    DIR* dir = opendir(path);
    if (dir == NULL)
    {
        //fprintf(stderr,"Failure, could not open Dir : %s\n", path);
        return;
    }

    struct dirent* file;
    struct stat statBuffer;

    while ((file = readdir(dir)) != NULL)
    {
        if (!strcmp(file->d_name,currentDir) || !strcmp(file->d_name, parentDir))
            continue;
        
        //Filename format
        char filename[strlen(path) + strlen(file->d_name)+ 10];
        strcpy(filename,path);
        strcat(filename,"/");
        strcat(filename, file->d_name);

        stat(filename,&statBuffer);

        if (S_ISDIR(statBuffer.st_mode)) 
        {   
            printDirectory(filename, param);
        }

        if (!matchCondition(file,filename, statBuffer,param))
            continue;
        
        printf("%s\n", filename);
    }
    closedir(dir);
}

