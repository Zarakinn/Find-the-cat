#include "parser.h"

char sizeMultiples[] = {'c','k','M','G'};
char timeMultiples[] = {'m','h','j'};

parameter* parse(int argc, char *argv[]) {

    parameter* param = (parameter*)malloc(sizeof(parameter));
    param->carrySearch = true;
    param->isDir = false;

    for(int i = 2; i < argc; i+=1){
        //printf("I : %i\n",i);
        //printf("Val : %s\n", argv[i]);
        if(argv[i][0]=='-'){ // on a reconnu un paramètre
            if(strcmp(argv[i],"-test")==0)
            {
                //printf("La valeur du flag -test est %s\n",argv[i+1]);

                if (argc < i+2)
                {
                    fprintf(stderr, "Erreur, pas assez d'arguement\n");
                }
                else {
                    printf("La valeur du flag %s est %s\n",argv[i+1],argv[i+2]);
                }
                param->carrySearch = false;
                return param;
            }
            else if(strcmp(argv[i],"-name")==0){
                if ( i + 1 >= argc)
                {
                    param->carrySearch = false;
                    fprintf(stderr,"Erreur, pas d'argument après le paramètre -name\n");
                    return param;
                }
                //printf("Param name : %s\n",argv[i+1]);
                //     Check ne commence pas par -param, ie que 
                param->name = argv[i+1];
                i++;
            }
            else if(strcmp(argv[i],"-date")==0){
                if ( i + 1 >= argc)
                {
                    param->carrySearch = false;
                    fprintf(stderr,"Erreur, pas d'argument après le paramètre -date\n");
                    return param;
                }
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
                    fprintf(stderr,"Erreur, multiple de date %c non reconnu.\n",multiple);
                    param->carrySearch = false;
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
                        param->carrySearch = false;
                        fprintf(stderr,"Erreur, la date ne doit être composé que de chiffre, hormis l'opérateur du début et un multiple à la fin\n");
                        break;
                    }
                }
                //printf("Date reconnu : %f\n",param->timeSinceLastAcess);
                i++;
            }
            else if(strcmp(argv[i],"-size")==0){
                if ( i + 1 >= argc)
                {
                    param->carrySearch = false;
                    fprintf(stderr,"Erreur, pas d'argument après le paramètre -size\n");
                    return param;
                }
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
                    fprintf(stderr,"Erreur, multiple de  taille %c non reconnu.\n",multiple);
                    param->carrySearch = false;
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
                    param->sizeModifier = EQUAL;
                    param->size = sizeInByte(size);
                    break;
                }

                //Ici il faut vérifier que size est compris que de numéro hormis le premier si hasModifier et le dernier si not invalid
                for (int l = 0 + (int)hasModifier; l < strlen(size) - (int)(!invalid); l++)
                {
                    if (!isdigit(size[l]))
                    {
                        param->size = NULL;
                        param->carrySearch = false;
                        fprintf(stderr,"Erreur, la taille ne doit être composé que de chiffre, hormis l'opérateur du début et un multiple à la fin\n");
                    }
                }
                //printf("Taille reconnu : %lu\n",param->size);
                i++;
            }
            else if(strcmp(argv[i],"-mime")==0){
                if ( i + 1 >= argc)
                {
                    param->carrySearch = false;
                    fprintf(stderr,"Erreur, pas d'argument après le paramètre -mime\n");
                    return param;
                }
                // TODO - vérifier que le paramèter est dans la banque de donnée de type mime
                param->type = argv[i+1];
                i++;
            }
            else if(strcmp(argv[i],"-ctc")==0){
                //printf("ctc : %s\n",argv[i+1]);
                param->patern = argv[i+1];
                i++;
            }
            else if(strcmp(argv[i],"-dir")==0){
                //printf("Dir : %s\n",argv[i+1]);
                param->isDir = argv[i+1];
                i++;
            }
            else 
            {   
                param->carrySearch = false;
                fprintf(stderr,"Erreur, paramètre : '%s' non reconnu\n",argv[i]);
                return param;
            }
        }
        else {param->carrySearch = false; fprintf(stderr,"Erreur, paramètre attendu\n");}
    }
    return param;
}
