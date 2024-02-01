#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd[2];
    pid_t pid;

    // parse the command line
    char *dir = (argc > 1) ? argv[1] : ".";

    // make a pipe in the parent
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // fork a child 
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if  (pid == 0) {
        if (dup2(fd[1], 1) == -1) {
            perror("dup2");
            exit(1);
        }

        close(fd[0]);
        close(fd[1]);

        // Execute ls with -1a options using defined directory
        execlp("ls", "ls", "-1a", dir, NULL);
        perror("execlp");
        exit(1);
        
    } else {
        if (dup2(fd[0], 0) == -1) {
            perror("dup2");
            exit(1);
        }

        close(fd[0]);
        close(fd[1]);

        // execute wc with -l option
        execlp("wc", "wc", "-l", NULL);
        perror("execlp");
        exit(1);
    }

    return 0;
}