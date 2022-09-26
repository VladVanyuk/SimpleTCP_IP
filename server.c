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
    bzero((char *) &server_info,sizeof(server_info)); // it clears all the data to what it it reference to 
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(8080);

    socklen_t server_info_len = sizeof(server_info);

    struct sockaddr client_info = {0};
    socklen_t client_info_len = sizeof(client_info);
    
    char buffer[255]; 

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
S:    if (0 > listen(sfd, 0))
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
    double num1,num2, ans;
    int choice;

	num1 = write(cfd,"Enter Number 1 : ",strlen("Enter Number 1"));
	if(num1 < 0)
    {
		perror("Error Writing to socket");
        return -1;
	}
	read(cfd,&num1,sizeof(double));
	printf("Client Number 1 is : %lf\n",num1);

	num2 = write(cfd,"Enter Number 2 : ",strlen("Enter Number 2"));
    if(num2 < 0)
    {
        perror("Error Writing to socket");
        return -1;
    }
    read(cfd,&num2,sizeof(double));
    printf("Client Number 2 is : %lf\n",num2);

	choice = write(cfd,"Enter Your Choice\n1.Add\n2.Subtract\n3.Division\n4.Multiplication\n5.Turn off server\nelse:Exit",strlen("Enter Your Choice\n1.Add\n2.Subtract\n3.Division\n4.Multiplication\n5.Turn off server\nelse:Exit"));
	if(choice < 0)
    {
		perror("Error on Writing");
        return -1;
	}
	read(cfd,&choice,sizeof(int));
    printf("Client - Choice is : %d\n",choice);
	switch(choice)
    {
		case 1:
			ans = num1 + num2;
			break;
		case 2:
		    ans = num1-num2;
			break;
		case 3:
		    ans = num1/num2;	
			break;
		case 4:
			ans = num1*num2;
			break;
		case 5:
            close(cfd);
		    goto Q;
	        break;
        default:
            printf("Choose one of whe choices!");
            close(cfd);	       
	}

	write(cfd,&ans,sizeof(double)); 
	if(choice != 5)
    {
		close(cfd);
        goto S;
	}

    // clean up
Q:  close(sfd);
    return 0;
}