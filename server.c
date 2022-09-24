#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{    
    // create socket info struictures
    struct sockaddr_in server_info = {0};
    
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(1337);

    socklen_t server_info_len = sizeof(server_info);

    struct sockaddr client_info = {0};
    socklen_t client_info_len = sizeof(client_info);
  

    // create our socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sfd)
    {
        perror("socket");
        return -1;
    }

    // bind 
    if (0 > bind(sfd, (struct sockaddr*)&server_info, server_info_len))
    {
        perror("bind");
        return -1;
    }
    
    // listen 
    if (0 > listen(sfd, 0))
    {
        perror("listen");
        return -1;
    }
    
    // accept 
    int cfd = accept(sfd, &client_info, &client_info_len);
    if (0 > cfd)
    {
        perror("accept");
        return -1;
    }

    // do client stuff (send/recv)
    char *hello = "Hello from Vlad\n";
    ssize_t sent = send(cfd, hello, strlen(hello), 0);

    // clean up
    close(cfd);
}