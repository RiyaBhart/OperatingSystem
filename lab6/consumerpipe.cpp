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

   
    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (true) { 
        num_bytes = read(fd, buffer, BUFSIZ); 
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        buffer[num_bytes] = '\0'; 
        cout << "\nConsumer: Received message: " << buffer;

        if (strncmp(buffer, "exit", 4) == 0) { 
            break;
        }
    }

    close(fd); 
    unlink(FIFO_FILE); 

    return 0;
}

