#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


char *arg_list[] = {"-e", "my_string", "-F", "my_file.txt", "-c", "\0"};

int pid;

int main(int argc, char *argv[]) {
    if ((pid = fork()) == 0) {
        if (execvp("grep", arg_list) < 0)
            perror("execvp");
    }
    else {
        wait(NULL);
        printf("Child process terminated\n");
    }
    return 0;

    
}

// code pour acceder au contenu du fichier puis implementer la recherche de pattern a l’intérieur du fichier

//version sans grep
// int main(int argc, char *argv[]) {
//     char *pattern = argv[1];
//     char *file = argv[2];
//     char *line = NULL;
//     size_t len = 0;
//     ssize_t read;
//     FILE *fp = fopen(file, "r");
//     if (fp == NULL)
//         exit(EXIT_FAILURE);
//     while ((read = getline(&line, &len, fp)) != -1) {
//         if (strstr(line, pattern) != NULL)
//             printf("%s", line);
//     }
//     fclose(fp);
//     if (line)
//         free(line);
//     exit(EXIT_SUCCESS);
// }

