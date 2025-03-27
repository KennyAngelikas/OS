#include <sys/types.h>   // Data types used in socket programming
#include <sys/socket.h>  // Socket functions and structures
#include <arpa/inet.h>   // Functions for IP addresses (e.g., htons, inet_ntoa)
#include <unistd.h>      // Close function
#include <stdio.h>       // Standard I/O functions
#include <stdlib.h>      // Standard library functions
#include <string.h>      // String handling functions

int main() {

    // Step 1: Create a Socket
    // A socket is an integer that points to a file descriptor table entry.
    // You manipulate the socket through the file descriptor.
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);  // server_fd = (3, 4, ..); non-negative int that acts as a key

    // Error handling for socket creation
    if (server_fd == -1) {
        perror("Socket creation failed");  // Print the reason for the failure
        exit(EXIT_FAILURE);  // Exit the program with an error code
    }
    printf("Socket created successfully\n");

    // Step 2: Bind the Socket to an IP and Port
    // Bind associates the socket with a specific IP address and port.
    // This is like registering your "address" where you can receive messages.
    struct sockaddr_in address;
        address.sin_family = AF_INET;         // Specify IPv4 address family
        // address.sin_addr.s_addr = INADDR_ANY; // Listen on any available network interface
        inet_pton(AF_INET, "129.32.95.93", &address.sin_addr); // Bind to the specific IP address
        address.sin_port = htons(4598);       // Convert port number to network byte order (big-endian)

    // Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");  // Print the reason for the failure
        close(server_fd);       // Clean up the socket
        exit(EXIT_FAILURE);     // Exit the program with an error code
    }
    printf("Socket successfully bound to port 4598\n");

    // Step 3: Listen for Incoming Connections
    // Listen switches the "closed" sign to "open" - letting clients know they can connect.
    // It sets the socket to passive mode, meaning it will accept incoming connections.
    if (listen(server_fd, 3) < 0) {  // 3 is the maximum queue length for pending connections
        perror("Listen failed");
        close(server_fd);  // Clean up the socket
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port 4598...\n");

    // Print the actual IP address the server is bound to
    char server_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(address.sin_addr), server_ip, INET_ADDRSTRLEN);
    printf("Server listening on IP: %s, Port: %d\n", server_ip, ntohs(address.sin_port));


    // Step 4: Accept an Incoming Connection
    // The accept call "lets one client in" and assigns them to a new socket.
    // The original listening socket remains open to accept more connections.
    int addrlen = sizeof(address);
    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    
    // Error handling for accept
    if (new_socket < 0) {
        perror("Accept failed");
        close(server_fd);  // Clean up the socket
        exit(EXIT_FAILURE);
    }

    // Print client information after accepting the connection
    printf("Connection accepted from %s:%d\n",
           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    // Step 5: Receive Data from Client
    // Buffer to store received data
    char buffer[1024] = {0};

    // Read data sent by the client
    ssize_t valread = recv(new_socket, buffer, sizeof(buffer), 0);
    if (valread < 0) {
        perror("Receive failed");
        close(new_socket);  // Close client-specific socket
        close(server_fd);   // Close server socket
        exit(EXIT_FAILURE);
    } else if (valread == 0) {
        printf("Client disconnected\n");
    } else {
        // Print the received message
        printf("Received from client: %s\n", buffer);
    }

    // Step 6: Send a Response to the Client
    // Prepare a response message
    const char *response = "Hello from server!";
    
    // Send the response to the client
    ssize_t valsend = send(new_socket, response, strlen(response), 0);
    if (valsend < 0) {
        perror("Send failed");
        close(new_socket);  // Close client-specific socket
        close(server_fd);   // Close server socket
        exit(EXIT_FAILURE);
    } else {
        printf("Response sent to client\n");
    }

    // Step 7: Clean Up
    // Close both client and server sockets to free resources
    close(new_socket);  // Close the client-specific socket
    close(server_fd);   // Close the server socket
    printf("Server shutdown successfully\n");

    return 0;
}