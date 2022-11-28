#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parameterStruct.h"

int main() {

    
    char str[] = "ftc starting-point [-test [parametre]] .";
    // Séparateurs connus.
    const char * separators = " [],.!";

    parameter* param = (parameter*)malloc(sizeof(parameter));


    // On récupère, un à un, tous les mots de la commande et on test le flag test
    char * strToken = strtok ( str, separators );
    while ( strToken != NULL ) {
        if (strcmp(strToken,"-test") ==0)
            printf("La valeur du flag -test est %s\n" ,strToken );
            //printf( "%s\n", &strToken[4]);
            if (sizeof(&strToken[4])==sizeof(int))
                printf("ok\n");
        
    
        // if (sizeof(&strToken[4])==sizeof(a))
        //     printf("ok\n");
        
        // for (a=strToken; *a; a++) {
        //     printf("%s\n",a);
        // } 
        

        printf ( "%s\n", strToken );


        
        //token suivant.
        strToken = strtok ( NULL, separators );
    }

    return EXIT_SUCCESS;
}