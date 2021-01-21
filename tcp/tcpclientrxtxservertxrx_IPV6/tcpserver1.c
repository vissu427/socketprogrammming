#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
int main()
{
	char mess[256];
    char sent_mesg[256]="Send the message";
	//create a server socket
	int sock;
	sock=socket(AF_INET6,SOCK_STREAM,0);
	//server address 
	struct sockaddr_in6 server,client;
	server.sin6_family=AF_INET6;
	server.sin6_port=htons(12345);
	server.sin6_addr=in6addr_any;
	//bind the socket
	bind(sock,(struct sockaddr*)&server,sizeof(server));
	listen(sock,5);
	int cli;
	cli=accept(sock,0,0);
	//receive the message
	recv(cli,&mess,sizeof(mess),0);
    //print the client response
    printf("The server received data:%s\n",mess);
    //send the message
    send(cli,sent_mesg,sizeof(sent_mesg),0);
	//close the socket
	close(sock);
	return 0;
}

