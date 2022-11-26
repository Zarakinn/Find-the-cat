#include "checker.h"



bool matchCondition(struct dirent* file, struct stat statBuffer, int cond)
{

    if (strstr(file->d_name,"git") != NULL)
    {
        return false;
    }

    //printf("Taille du fichier = %ld\n",(long)statBuffer.st_size);
    if (statBuffer.st_size < 500)
    {
        return false;
    }

    time_t t = time(NULL); // A déplacer car tout le temps le même

    //printf("Date dernier accès : %s\n",ctime(&statBuffer.st_atime));
    //printf("Date actuelle : %s\n", ctime(&t));

    double timeSinceLastAccess = (double)difftime(t,statBuffer.st_atime);
    //printf("Différence : %f\n",timeSinceLastAccess);

    if (timeSinceLastAccess > 20)
    {
        return false;
    }

    return true;
}
