//
// Created by khanh on 4/17/2023.
//
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error((char *) "ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    // Zero out the server address.
    bzero((char *) &serv_addr, sizeof(serv_addr));

    // Connect client socket to a server IP + port combination.
    serv_addr.sin_family = AF_INET;

    // Set IP address of the server address object.
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    // Convert port number to big endian.
    serv_addr.sin_port = htons(portno);

    // Request a connection.
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error((char *) "ERROR connecting");
    printf("Please enter the message: ");

    bzero(buffer,256);

    // Get 255 characters.
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
         error((char *) "ERROR writing to socket");

    // Read response from socket.
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0)
         error((char *) "ERROR reading from socket");
    printf("%s\n",buffer);
    return 0;
}