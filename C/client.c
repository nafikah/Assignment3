#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serv_addr; 
    char message[1000], server_reply[2000];
 

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    puts("socket created"); 

    
    serv_addr.sin_addr.s_addr = inet_addr("192.168.202.134");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080); 
 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
    puts("connected");

	while(1)
	{
	printf("Enter message: ");
	scanf("%s", message);
	
		if( send(sockfd, message, strlen(message), 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
                puts("sending success!");
	
		if( recv(sockfd, server_reply, 2000, 0) < 0)
		{
			puts("recv failed");
			break;
		}
		puts("Server reply ");
		puts(server_reply);
	} 

    return 0;
}
