#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

using namespace std;

int main() {
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) { 
        cerr << "Pipe failed" << endl;
        return 1;
    }

    pid = fork();
    if (pid < 0) { 
        cerr << "Fork Failed" << endl;
        return 1;
    }

    if (pid > 0) { 
        close(fd[READ_END]);

        cout << "Enter a message: ";
        cin.getline(write_msg, BUFFER_SIZE); 

        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        close(fd[WRITE_END]);
    } else { 
        close(fd[WRITE_END]); 
        read(fd[READ_END], read_msg, BUFFER_SIZE); 
        cout << "Read: " << read_msg << endl;
        close(fd[READ_END]); 
    }

    return 0;
}

