#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    // Checks for minimum arguments
    if (argc < 3) {
        fprintf(stderr, "Usage: %s output_file command [args]\n", argv[0]);
        return 1;
    }

    // Opens the output file
    int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Moves stdout to file
    if (dup2(fd, 1) == -1) {
        perror("dup2");
        return 1;
    }

    close(fd);

    // Execute the command
    execvp(argv[2], argv + 2);

    perror("execvp");
    return 1;
}