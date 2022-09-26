#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

int exists(const char *fname)
{
    FILE *file;
    file = fopen(fname, "r");
    if ( file == NULL)
    {
        perror("No config file ");
        return(-1);
    }
    fclose(file);
}

int main(int argc, char **argv)
{
    exists("config.h");
    
    // create server info
    struct sockaddr_in server_info = {0};
    server_info.sin_family = AF_INET;
    server_info.sin_addr.s_addr = htonl(IP); //localhost ip addr
    server_info.sin_port = htons(PORT);
    
    socklen_t server_info_len = sizeof(server_info);

    // create socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);// sock file descriptor
    if (0 > sfd)
    {
        perror("socket error");
        return -1;
    }
    
    // connect to server with socket
    if (0 > connect(sfd, (struct sockaddr*)&server_info, server_info_len))
    {
        perror("connect error");
        return -1;
    }
    
    // do client stuff (reading Server String )
    char buffer[256];
    double num1,num2, ans;
    int choice;

    bzero(buffer,256);
	num1 = read(sfd,buffer,256);
	if(num1 < 0)
    {
		perror("Error reading From Socket");
        return -1;
	}

	printf("Server - %s\n",buffer);
	scanf("%lf",&num1);
	write(sfd,&num1,sizeof(double));

	bzero(buffer,256);
    num2 = read(sfd,buffer,256);
    if(num2 < 0)
    {
        perror("Error reading From Socket");
        return -1;
    }

    printf("Server - %s\n",buffer);
    scanf("%lf",&num2);
    write(sfd,&num2,sizeof(double));

	bzero(buffer,256);
    choice = read(sfd,buffer,256);
    if(choice < 0)
    {
        perror("Error reading From Socket");
        return -1;
    }

    printf("Server - %s\n",buffer);
    scanf("%d",&choice);
    write(sfd,&choice,sizeof(int));

	read(sfd,&ans,sizeof(double));
	printf("Server : The answere is : %lf\n",ans);

    // clean up
    close(sfd);
    return 0;

}