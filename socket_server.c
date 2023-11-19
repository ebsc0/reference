#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include "common.h"

int main(int argc, char** argv)
{
    /* create socket */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket failed");
        return -1;
    }

    /* bind */
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2520);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) != 0) /* bind socket with addr info (assign address format, port, protocol) */
    {
        /* error */
        perror("bind failed");
        close(sockfd);
        return -1;
    }

    /* listen */
    if(listen(sockfd, 5) != 0) /* listen for connect from client with backlog of 5 */
    {
        /* error */
        perror("listen failed");
        close(sockfd);
        return -1;
    }
    
    /* accept */
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int newsockfd = accept(sockfd, (struct sockaddr*) &client_addr, &client_addr_len);
    if(newsockfd == -1)
    {
        /* error */
        perror("accept failed");
        close(sockfd);
        return -1;
    }

    /* send message */
    char* message = "hello";
    if(send(newsockfd, message, strlen(message), 0) == -1)
    {
        perror("send failed");
        close(newsockfd);
        close(sockfd);
        return -1;
    }

    close(newsockfd); /* close server-client socket */

    close(sockfd); /* close server socket */

    return 0;
}