#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ss{
    char name;
    char type;
    int size;
} typedef Parametre;

char* a;
int b;

int main() {

    
    char str[] = "ftc starting-point [-test [parametre]] .";
    // Séparateurs connus.
    const char * separators = " [],.!";

    // On récupère, un à un, tous les mots de la commande et on test le flag test
    char * strToken = strtok ( str, separators );
    while ( strToken != NULL ) {
        if (strcmp(strToken,"-test") ==0)
            printf("La valeur du flag -test est %s\n" ,strToken );
            //printf( "%s\n", &strToken[4]);
            if (sizeof(&strToken[4])==sizeof(b))
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