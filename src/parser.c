#include "parser.h"

char sizeMultiples[] = {'c','k','M','G'};
char timeMultiples[] = {'m','h','j'};

parameter* parse(int argc, char *argv[]) {

    parameter* param = (parameter*)malloc(sizeof(parameter));

    if (argc%2 != 0) 
    { 
        printf("Erreur, chaque paramètre doit avoir un argument.\n");
        return 0;
    }

    for(int i = 2; i < argc; i+=2){
        //printf("I : %i\n",i);
        //printf("Val : %s\n", argv[i]);
        if(argv[i][0]=='-'){ // on a reconnu un paramètre
            if(strcmp(argv[i],"-test")==0)
            {
                printf("La valeur du flag -test est %s\n",argv[i+1]);
                //a changer
            }
            else if(strcmp(argv[i],"-name")==0){
                //printf("Param name : %s\n",argv[i+1]);
                //     Check ne commence pas par -param, ie que 
                param->name = argv[i+1];
            }
            else if(strcmp(argv[i],"-date")==0){
                
                char* time = argv[i+1];
                char multiple = time[strlen(time)-1];
                bool invalid = true;
                for(int l = 0; l< (int)sizeof(timeMultiples); l++)
                {
                    if (multiple == timeMultiples[l])
                    {
                        invalid = false;
                        break;
                    }
                }
                if (invalid & !isdigit(multiple))
                {
                    printf("Erreur, multiple de date %c non reconnu.\n",multiple);
                    continue; // on ne s'arrête pas, on continue au prochain paramètre
                }
                bool hasModifier = false;
                switch (time[0])
                {
                case '+':
                    param->timeModifier = GREATER;
                    param->timeSinceLastAcess = timeInSecond(time+1);;
                    hasModifier = true;
                    //printf("+ reconnu\n");
                    break;
                case '=':
                    param->timeModifier = EQUAL;
                    param->timeSinceLastAcess = timeInSecond(time+1);;
                    hasModifier = true;
                    //printf("= reconnu\n");
                    break;
                case '-':
                    param->timeModifier = SMALLER;
                    param->timeSinceLastAcess = timeInSecond(time+1);;
                    hasModifier = true;
                    //printf("- reconnu\n");
                    break;
                default:
                    param->timeModifier = SMALLER;
                    param->timeSinceLastAcess = timeInSecond(time);;
                    break;
                }

                //Ici il faut vérifier que time est compris que de numéro hormis le premier si hasModifier et le dernier si not invalid
                for (int l = 0 + (int)hasModifier; l < strlen(time) - (int)(!invalid); l++)
                {
                    if (!isdigit(time[l]))
                    {
                        param->timeSinceLastAcess = 0;
                        printf("Erreur, la date ne doit être composé que de chiffre, hormis l'opérateur du début et un multiple à la fin\n");
                    }
                }
                //printf("Date reconnu : %f\n",param->timeSinceLastAcess);
            }
            else if(strcmp(argv[i],"-size")==0){
                
                char* size = argv[i+1];                
                char multiple = size[strlen(size)-1];
                
                bool invalid = true;
                for(int l = 0; l< (int)sizeof(sizeMultiples); l++)
                {
                    if (multiple == sizeMultiples[l])
                    {
                        invalid = false;
                        break;
                    }
                }
                if (invalid)
                {
                    if (isdigit(multiple)) // Il n'y a pas de multiple, c'est un chiffre
                    {
                        continue;
                    }
                    printf("Erreur, multiple de  taille %c non reconnu.\n",multiple);
                    continue; // on ne s'arrête pas, on continue au prochain paramètre
                }

                bool hasModifier = false;
                switch (size[0])
                {
                case '+':
                    param->sizeModifier = GREATER;
                    param->size = sizeInByte(size+1);
                    hasModifier = true;
                    //printf("+ reconnu\n");
                    break;
                case '=':
                    param->sizeModifier = EQUAL;
                    param->size = sizeInByte(size+1);
                    hasModifier = true;
                    //printf("= reconnu\n");
                    break;
                case '-':
                    param->sizeModifier = SMALLER;
                    param->size = sizeInByte(size+1);
                    hasModifier = true;
                    //printf("- reconnu\n");
                    break;
                default:
                    param->sizeModifier = SMALLER;
                    param->size = sizeInByte(size);
                    break;
                }

                //Ici il faut vérifier que size est compris que de numéro hormis le premier si hasModifier et le dernier si not invalid
                for (int l = 0 + (int)hasModifier; l < strlen(size) - (int)(!invalid); l++)
                {
                    if (!isdigit(size[l]))
                    {
                        param->size = NULL;
                        printf("Erreur, la taille ne doit être composé que de chiffre, hormis l'opérateur du début et un multiple à la fin\n");
                    }
                }
                //printf("Taille reconnu : %lu\n",param->size);
            }
            else if(strcmp(argv[i],"-mime")==0){
                printf("Mime : %s\n",argv[i+1]);
                param->type = argv[i+1];
            }
            else if(strcmp(argv[i],"-ctc")==0){
                printf("ctc : %s\n",argv[i+1]);
                param->patern = argv[i+1];
            }
            else if(strcmp(argv[i],"-dir")==0){
                printf("Dir : %s\n",argv[i+1]);
                param->isDir = argv[i+1];
            }
            else 
            {
                printf("Erreur, paramètre : '%s' non reconnu\n",argv[i]);
            }
        }
        else {printf("Erreur, paramètre attendu\n");}
    }
    return param;
}
