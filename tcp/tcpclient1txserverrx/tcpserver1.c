#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
int main()
{
	char mess[256];
	//create a server socket
	int sock;
	sock=socket(AF_INET,SOCK_STREAM,0);
	//server address 
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(9002);
	server.sin_addr.s_addr=INADDR_ANY;
	//bind the socket
	bind(sock,(struct sockaddr*)&server,sizeof(server));
	listen(sock,5);
	int cli;
	cli=accept(sock,0,0);
	//recieve the message from the client
	recv(cli,mess,sizeof(mess),0);
    //print the client response
    printf("The server received data:%s\n",mess);
	//close the socket
	close(sock);
	return 0;
}

