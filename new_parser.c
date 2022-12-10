#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "new_parser.h"

//parser la commande en entrée

struct ss{
    char name;
    char type;
    int size;
} typedef Parametre;

char* a;
int* b;
char multiples[] = {'c','k','M','G'};
int multiples2[] = {1,1024,1024*1024,1024*1024*1024};


long int findSize(char* file_name)
{
    
    FILE* fp = fopen(file_name, "r");
  
    
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
  
    fseek(fp, 0L, SEEK_END);
  
    // calcul de la taille du fichier ( positionement sur le bit de fin)
    long int res = ftell(fp);
  
    // fermeture
    fclose(fp);
  
    return res;
}


double timeInSecond(char* size)
{
    double res = 0;

    char coef = size[strlen(size) - 1];
    switch (coef)
    {
    case 'm':
        res = atoi(size) * m; //conversion en double
        break;
    case 'h':
        res = atoi(size);
        res *= H;
        res *= m;    // multiplication par le coeff
        break;
    case 'j':
        res = atoi(size);
        res *= H;
        res *= m;
        res *= J;
        break;
    default:
        res = atoi(size);
        break;
    }

    return res;
}

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

bool matchCondition(struct dirent* file, struct stat statBuffer, parameter* param)
{

    //printf("%s\n",file->d_name);
    if (param->name!= NULL && (strstr(file->d_name,param->name) == NULL))
    {
        return false;
    }
    //printf("Taille du fichier = %ld\n",(long)statBuffer.st_size);
    if (param->size != NULL && statBuffer.st_size < param->size)
    {
        switch (param->sizeModifier)
        {
        case EQUAL:
            if (statBuffer.st_size != param->size)
                return false;
            break;
        case GREATER:
            if (statBuffer.st_size < param->size)
                return false;
            break;
        case SMALLER:
            if (statBuffer.st_size > param->size)
                return false;
            break;
        default:
            printf("Erreur, aucun modifier renseigné pour la taille\n");
            break;
        }

        return false;
    }
    if (param->timeSinceLastAcess != 0)
    {
        time_t t = time(NULL); // A déplacer car tout le temps le même

        printf("Date dernier accès : %s\n",ctime(&statBuffer.st_atime));
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
            if (timeSinceLastAccess < param->timeSinceLastAcess)
                return false;
            break;
        case SMALLER:
            if (timeSinceLastAccess > param->timeSinceLastAcess)
                return false;
            break;
        default:
            printf("Erreur, aucun modifier renseigné pour le temps de dernier accès\n");
            break;
        }
    }

    return true;
}









bool argsize = false;


int main(int argc, char *argv[]) {

    for(int i = 1; i < argc; i++){
        char* val = argv[i];
        if(argv[i][0]=='-'){ // on a reonnu un paramètre
            if(strcmp(argv[i],"-name")==0){
                printf("ok, on est là : %s\n",argv[1]);
            }
            if(strcmp(argv[i],"-date")==0){
                printf("ok, on est là : %s\n",argv[i]);
                printf("Temps en sec : %f\n", timeInSecond(argv[i+1]));
                // printf("Temps en sec : %f\n", timeInSecond("5m"));
            }
            if(strcmp(argv[i],"-size")==0 && !argsize){
                printf("ok, on est là : %s\n",argv[i]);
                char* file_name;
                file_name = argv[2];
                // long int res = findSize(file_name);
                // printf("Size of the file is %ld bytes \n", res);
                
                if (i+1 <= argc && !argsize){
                    printf("%s\n",argv[i+1]);
                    char taille = argv[i+1][strlen(argv[i+1])-1];
                    printf("%c\n",taille);
                    char taille_officielle;
                    int multiple_officiel;
                    //vérifie que la taille fait bien partie des tailles multiples
                    bool stop = false;
                    for(long int j = 0; j < sizeof(multiples) && !stop && !argsize; j++){
                        printf("on est dans la boucle %ld\n",j);
                        if(taille == multiples[j]){
                            taille_officielle = multiples[j];
                            multiple_officiel = multiples2[j];
                            stop=true;
                        }

                        if(taille != 'k' && taille != 'c' && taille != 'M' && taille !='G'){
                            printf("La taille n'est pas valide\n");
                            return(0);
                        }
                        // if(j==sizeof(multiples)-1){
                        //     printf("La taille n'est pas valide\n");
                        //     return(0);
                    }
                    printf("on a passé la boucle\n");
                    //printf("%c\n",taille_officielle);
                    if(stop){
                        printf("on a trouvé la taille\n");
                        printf("symbole de taille : %c\n",taille_officielle);
                        printf("valeur en multiple : %d\n",multiple_officiel);
                        //on a trouvé la taille, on peut maintenant comparer la taille du fichier à la taille donnée
                        long int res = findSize(file_name);
                        printf("Size of the file is %ld bytes \n", res);
            
                    }
                    argsize = true;
                    }
                }
            }

        
            if(strcmp(argv[i],"-mime")==0){
                printf("ok, on est là : %s\n",argv[i]);
            }
            if(strcmp(argv[i],"-ctc")==0){
                printf("ok, on est là : %s\n",argv[i]);
            }
            if(strcmp(argv[i],"-dir")==0){
                printf("ok, on est là : %s\n",argv[i]);
            }
        }

    }






