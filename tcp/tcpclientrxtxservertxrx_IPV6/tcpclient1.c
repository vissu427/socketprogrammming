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
	sock=socket(AF_INET6,SOCK_STREAM,0);
    char recv_mesg[256];
	//specify the address of the socket//
	struct sockaddr_in6 server;
	server.sin6_family=AF_INET6;
	server.sin6_port=htons(12345);
	server.sin6_addr=in6addr_any;
	int connection_status=connect(sock,(struct sockaddr*)&server,sizeof(server));
	//check for error connection status//
	if(connection_status==-1)
	{
		printf("There is an error making a connection to the remote socket\n\n");
	}
	//send data to the server//
	char mesg[256]="I have reached to you";
	send(sock,mesg,sizeof(mesg),0);
    //receive data from the server
    recv(sock,&recv_mesg,sizeof(recv_mesg),0);
    printf("Reeceived server data :%s\n",recv_mesg);

	//close the socket
	close(sock);
	return 0;
}
