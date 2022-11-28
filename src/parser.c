#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parameterStruct.h"

char* a;
int* b;
char c[]={'-','s','i','d'};
char multiples[] = {'k','M','G'};

int main() {

    
    char str[] = "ftc starting-point -size 9k -date .";
    // Séparateurs connus.
    const char * separators = " [],.!";

    parameter* param = (parameter*)malloc(sizeof(parameter));


    // On récupère, un à un, tous les mots de la commande et on test le flag test
    char * strToken = strtok ( str, separators );
    while ( strToken != NULL ) {

        printf ( "%s\n", strToken );

        if (strcmp(strToken,"-test") ==0){
            printf("La valeur du flag -test est %s\n" ,strToken );
            }


        if (strToken[0]==c[0]){
            if (strToken[1]==c[1] && strToken[2]==c[2]){
                printf(("ok, on est là : %s\n"),strToken);
                strToken = strtok ( NULL, separators );
                printf ("%c\n", strToken[1] );
                if (strToken[1]==multiples[0]){
                    printf("%d\n", (int)strToken[1]*1024);
                }
            
            }
            
        }


        if (sizeof(strToken[0])==sizeof(b)){
                printf("C'est un int\n");
            }

        
        // if (sizeof(&strToken[4])==sizeof(a))
        //     printf("ok\n");
        
        // for (a=strToken; *a; a++) {
        //     printf("%s\n",a);
        // } 
        

        //token suivant.
        strToken = strtok ( NULL, separators );
    }

    return EXIT_SUCCESS;
}