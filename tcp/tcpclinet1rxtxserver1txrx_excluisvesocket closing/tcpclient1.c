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
    char recv_mesg[256];
	//specify the address of the socket//
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(9001);
	client.sin_addr.s_addr=INADDR_ANY;
    bind(sock,(struct sockaddr*)&client,sizeof(client));
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
	//send data to the server//
	char mesg[256]="I have reached to you";
	send(sock,mesg,sizeof(mesg),0);
    //receive data from the server
    recv(sock,&recv_mesg,sizeof(recv_mesg),0);
    printf("Reeceived server data :%s\n",recv_mesg);

	//close the socket
	close(sock);
//sleep the socket
    sleep(10);
	return 0;
}
