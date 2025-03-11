#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>

#define FIFO_FILE "/tmp/myfifo"

using namespace std;

int main() {
    int fd;
    char buffer[BUFSIZ];
    ssize_t num_bytes;


    mkfifo(FIFO_FILE, 0666);

   
    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (true) { 
        cout << "Producer: Enter a message (or 'exit' to quit): ";
        cin.getline(buffer, BUFSIZ);

        num_bytes = write(fd, buffer, strlen(buffer)); 
        if (num_bytes == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        if (strncmp(buffer, "exit", 4) == 0) { 
            break;
        }
    }

    close(fd); 
    unlink(FIFO_FILE); 

    return 0;
}

