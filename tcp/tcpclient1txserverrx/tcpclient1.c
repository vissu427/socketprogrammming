#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main()
{
	//create a socket//
	int sock;
	sock=socket(AF_INET,SOCK_STREAM,0);
	//specify the address of the socket//
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(9002);
	server.sin_addr.s_addr=INADDR_ANY;
	int connection_status=connect(sock,(struct sockaddr*)&server,sizeof(server));
	//check for error connection status//
	if(connection_status==-1)
	{
		printf("There is an error making a connection to the remote socket\n\n");
	}
	//send message to the server//
	char mesg[256]="I have reached to you";
	send(sock,&mesg,sizeof(mesg),0);

	//close the socket
	close(sock);
	return 0;
}
