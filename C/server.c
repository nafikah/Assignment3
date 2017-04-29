#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int client_sock, c , read_size;
    int listenfd;
    char client_message[2000], *begin, *end, temp;
    struct sockaddr_in serv_addr,client; 

    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
    { printf("Could not create socket"); 
    }
    puts("Socket created");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080); 

    if( bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
    {
	perror("bind failed. Error");
	return 1;
    }
    puts("bind done"); 

    listen(listenfd, 3); 

	puts("Waiting for incoming connection..");
	c = sizeof(struct sockaddr_in);

	client_sock = accept(listenfd,(struct sockaddr *) &client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");
	
	while( (read_size = recv(client_sock, client_message, 2000 , 0)) < 0)
	{
               
		begin = client_message;
		end = begin + strlen(client_message) -1;
             

    			while(end>begin)
			{
			temp = *begin;
			*begin = *end;
			*end = temp;

			++begin;
			--end;
			}
	}
		write(client_sock,client_message, strlen(client_message));
		
	
	if(read_size == 0)
	{
		puts("client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
		perror("recv failed");

	return 0;
}
