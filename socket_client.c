#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include "common.h"

int main(int argc, char** argv)
{
    /* get server address */
    struct addrinfo hints;
    struct addrinfo *server;

    memset(&hints, 0, sizeof(hints)); /* specify connection */
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo("localhost", "2520", &hints, &server) != 0) /* use getaddrinfo to get server info */
    {
        /* error */
        perror("getaddrinfo failed");
        return 1;
    }

    /* create socket */
    int sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    if(sockfd == -1)
    {
        /* error */
        perror("socket failed");
        freeaddrinfo(server);
        return -1;
    }

    /* connect to server */
    if(connect(sockfd, server->ai_addr, server->ai_addrlen) != 0)
    {
        /* error */
        perror("connect failed");
        freeaddrinfo(server);
        close(sockfd);
        return -1;
    }

    /* recieve message from server */
    char* message;
    if(recv(sockfd, message, strlen(message), 0) == -1)
    {
        perror("recv failed");
        freeaddrinfo(server);
        close(sockfd);
        return -1;
    }

    printf("Client: recieved %s from server...", message);
    freeaddrinfo(server);
    close(sockfd);

    return 0;
}
