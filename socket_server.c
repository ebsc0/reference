#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include "common.h"

int main(int argc, char** argv)
{
    /* create socket */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd != 0)
    {
        perror("socket failed");
        return -1;
    }

    /* bind */
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2520);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, &server_addr, sizeof(server_addr)) != 0) /* bind socket with addr info (assign address format, port, protocol) */
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
    int newsockfd = accept(sockfd, &client_addr, sizeof(client_addr));
    if(newsockfd != 0)
    {
        /* error */
        perror("accept failed");
        close(sockfd);
        return -1;
    }

    /* send message */
    int message = ntohl(42);
    if(send(newsockfd, &message, sizeof(message), 0) != 0)
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