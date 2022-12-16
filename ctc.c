#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


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


