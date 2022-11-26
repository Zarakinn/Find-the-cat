#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    
    char str[] = "ftc starting-point [-test [parametre]] .";
    // Séparateurs connus.
    const char * separators = " [],.!";

    // On récupère, un à un, tous les mots de la commande et on test le flag test
    char * strToken = strtok ( str, separators );
    while ( strToken != NULL ) {
        if (strcmp(strToken,"-test") ==0)
            printf("La valeur du flag -test est %s\n" ,strToken );
        printf ( "%s\n", strToken );
        //token suivant.
        strToken = strtok ( NULL, separators );
    }

    return EXIT_SUCCESS;
}