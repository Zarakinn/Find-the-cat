#include "checker.h"

bool matchCondition(struct dirent* file, const char* filename, struct stat statBuffer, parameter* param)
{   
    
    if (param->type != NULL)
    {
        const char* mimetype = getMegaMimeType(filename);
        if (mimetype != NULL)
        {

            if (strstr(mimetype,param->type) == NULL)
            {
                return false;
            }
        }
        else 
        {
            return false;
        }
    }
    //printf("%s\n",file->d_name);
    if (param->name!= NULL && (strstr(file->d_name,param->name) == NULL))
    {
        return false;
    }

    if (param->isDir != false && param->isDir)
    {
        if (!S_ISDIR(statBuffer.st_mode))
        {
            return false;
        } 
    }

    //printf("Taille du fichier = %ld\n",(long)statBuffer.st_size);
    if (param->size != NULL)
    {
        switch (param->sizeModifier)
        {
        case EQUAL:
            if (statBuffer.st_size != param->size)
                return false;
            break;
        case GREATER:
            if (statBuffer.st_size <= param->size)
                return false;
            break;
        case SMALLER:
            if (statBuffer.st_size >= param->size)
                return false;
            break;
        default:
            printf("Erreur, aucun modifier renseigné pour la taille\n");
            break;
        }

    }
    if (param->timeSinceLastAcess != 0)
    {
        time_t t = time(NULL); // A déplacer car tout le temps le même

        //printf("Date dernier accès : %s\n",ctime(&statBuffer.st_atime));
        //printf("Date actuelle : %s\n", ctime(&t));

        double timeSinceLastAccess = (double)difftime(t,statBuffer.st_atime);
        //printf("Différence : %f\n",timeSinceLastAccess);

        switch (param->timeModifier)
        {
        case EQUAL:
            if (timeSinceLastAccess!= param->size)
                return false;
            break;
        case GREATER:
            if (timeSinceLastAccess <= param->timeSinceLastAcess)
                return false;
            break;
        case SMALLER:
            if (timeSinceLastAccess >= param->timeSinceLastAcess)
                return false;
            break;
        default:
            printf("Erreur, aucun modifier renseigné pour le temps de dernier accès\n");
            break;
        }
    }
    return true;
}
