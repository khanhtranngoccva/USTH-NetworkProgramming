/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    // This stores the message.
    char buffer[256];
    // File descriptor for socket system call and accept system call, port number, size of client address
    int sockfd, newsockfd, portno, clilen;
    // 2 socket internet addresses. The first for server and the second for client.
    struct sockaddr_in serv_addr, cli_addr;
    // Argument parsing. If there are less than 2 arguments (including the executable name), program exits.
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    // Create a socket. First arg is socket address domain.
    // AF_INET denotes internet sockets, while AF_UNIX denotes UNIX sockets.
    // Second arg is socket type.
    // SOCK_STREAM denotes (ordered) stream sockets and SOCK_DGRAM denotes (unordered) datagram sockets.
    // Third arg is protocol, and 0 will cause the OS to pick the protocol automatically.
    // SOCK_STREAM => TCP, SOCK_DGRAM => UDP
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // If fails, returns -1. We use this return value to throw an error.
    if (sockfd < 0)
        error((char *) "ERROR opening socket");

    // Zeroes out the serv_addr struct. (I don't know why it's converted to char pointer?)
    bzero((char *) &serv_addr, sizeof(serv_addr));

    // Converts the argument to a port.
    portno = atoi(argv[1]);

    // Address domain of the server address. In the next bind call, must match sockfd's address domain.
    serv_addr.sin_family = AF_INET;

    // The TCP/IP standard represents port numbers in a Big Endian binary form,
    // however computers can also represent numbers in Little Endian. Therefore port numbers
    // has to be converted to Big Endian for use.
    serv_addr.sin_port = htons(portno);

    // IP address. In this case, we use INADDR_ANY, which translates to 0.0.0.0 - a symbolic reference
    // to host IP.
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Binds the socket fd to the address. Must also specify the size of the socket address.
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error((char *) "ERROR on binding");

    // Enable socket to listen for connections, with up to 5 at a time.
    listen(sockfd, 5);

    // Get length for client address to use for socket call.
    clilen = sizeof(cli_addr);

    // Accept a socket and set the cli_addr attributes.
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen);
    if (newsockfd < 0)
        error((char *) "ERROR on accept");

    // Reset the buffer.
    bzero(buffer,256);

    // Read the socket.
    n = read(newsockfd,buffer,255);
    if (n < 0) error((char *) "ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);

    // Write response.
    n = write(newsockfd,"I got your message",18);
    if (n < 0) error((char *) "ERROR writing to socket");
    return 0;
}