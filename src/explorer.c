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

void printDirectory(const char* path)
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

        if (!matchCondition(file,statBuffer,0))
            continue;

        printf("%s\n", filename);
        

        if (S_ISDIR(statBuffer.st_mode)) 
        {   
            printDirectory(filename);
        }
    }

    closedir(dir);
}

