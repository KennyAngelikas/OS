#include <stdio.h>       // For printf() and perror()
#include <stdlib.h>      // For exit()
#include <unistd.h>      // For close()
#include <string.h>      // For strlen()
#include <arpa/inet.h>   // For sockaddr_in and inet_pton()

int main() {

    // Step 1: Create a socket
    // AF_INET: IPv4, SOCK_STREAM: TCP
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Client socket created successfully\n");

    // Step 2: Specify server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;  // IPv4
    server_address.sin_port = htons(4598); // Port number (same as server)

    // Convert IP address from text to binary
    if (inet_pton(AF_INET, "129.32.95.93", &server_address.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }

    // Step 3: Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server at 127.0.0.1:4598\n");

    // Step 4: Send a message to the server
    const char *message = "Hello from client!";
    ssize_t send_status = send(client_fd, message, strlen(message), 0);
    if (send_status < 0) {
        perror("Send failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    printf("Message sent to server: %s\n", message);

    // Step 5: Receive response from the server
    char buffer[1024] = {0};
    ssize_t valread = recv(client_fd, buffer, sizeof(buffer), 0);
    if (valread < 0) {
        perror("Receive failed");
    } else if (valread == 0) {
        printf("Server closed the connection\n");
    } else {
        printf("Received from server: %s\n", buffer);
    }

    // Step 6: Clean up and close the socket
    close(client_fd);
    printf("Client socket closed\n");

    return 0;
}