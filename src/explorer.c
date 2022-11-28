#include "explorer.h"
#include "checker.h"

DIR* loadDir(const char* filename){
    DIR* dir = opendir(filename);

    if (dir == NULL)
    {
        //handle Error    
    }

    return dir;
}

void printDirectory(const char* path,parameter* param)
{

    DIR* dir = loadDir(path);

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

        if (!matchCondition(file,statBuffer,param))
            continue;
        printf("%s\n", filename);
    }

    closedir(dir);
}

