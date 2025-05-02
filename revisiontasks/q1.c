#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

FILE *temp_file = NULL;
char filename[] = "/tmp/tempfileXXXXXX";

void handle_sigint(int sig) {
    printf("\nSIGINT received. Cleaning up...\n");

    if (temp_file) {
        fclose(temp_file);
        printf("File closed.\n");
    }

    if (remove(filename) == 0) {
        printf("Temporary file '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting temporary file");
    }

    exit(0);
}

int main() {
    int fd = mkstemp(filename);
    if (fd == -1) {
        perror("Failed to create temporary file");
        return 1;
    }

    temp_file = fdopen(fd, "w");
    if (!temp_file) {
        perror("fdopen failed");
        close(fd);
        remove(filename);
        return 1;
    }

    signal(SIGINT, handle_sigint);

    printf("Writing to temporary file '%s'. Press Ctrl+C to stop and clean up.\n", filename);

    int counter = 1;
    while (1) {
        fprintf(temp_file, "Line %d: Sample data...\n", counter++);
        fflush(temp_file); // Ensure data is written to disk
        sleep(1);
    }

    return 0; }

