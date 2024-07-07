#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_FILE_CONTENT_LENGTH 1024

void server(int fd_client, int fd_server) {
    char filename[MAX_FILENAME_LENGTH];
    char file_content[MAX_FILE_CONTENT_LENGTH];
    int file_fd;

    // Read filename from the client
    read(fd_client, filename, MAX_FILENAME_LENGTH);

    // Attempt to open the file
    file_fd = open(filename, O_RDONLY);

    if (file_fd == -1) {
        // If file opening fails, send an error message to the client
        write(fd_server, "Error: Unable to open file", strlen("Error: Unable to open file"));
    } else {
        // Read file content and send it to the client
        int read_size = read(file_fd, file_content, MAX_FILE_CONTENT_LENGTH);
        write(fd_server, file_content, read_size);
        close(file_fd);
    }

    // Close the pipes
    close(fd_client);
    close(fd_server);
    exit(0);
}

void client(int fd_client, int fd_server) {
    char filename[MAX_FILENAME_LENGTH];
    char file_content[MAX_FILE_CONTENT_LENGTH];

    printf("Enter the filename: ");
    scanf("%s", filename);

    // Send filename to the server
    write(fd_client, filename, strlen(filename) + 1);

    // Read the server's response
    int read_size = read(fd_server, file_content, MAX_FILE_CONTENT_LENGTH);

    // Display the server's response
    printf("Server response: %s\n", file_content);

    // Close the pipes
    close(fd_client);
    close(fd_server);
    exit(0);
}

int main() {
    int fd_client_to_server[2], fd_server_to_client[2];
    pipe(fd_client_to_server);
    pipe(fd_server_to_client);

    pid_t pid = fork();

    if (pid == 0) 
    {
        // Child process (server)
        close(fd_client_to_server[1]);
        close(fd_server_to_client[0]);
        server(fd_client_to_server[0], fd_server_to_client[1]);
    } else if (pid > 0) {
        // Parent process (client)
        close(fd_client_to_server[0]);
        close(fd_server_to_client[1]);
        client(fd_client_to_server[1], fd_server_to_client[0]);

        // Wait for the server to finish
        wait(NULL);
    }

    return 0;
}

