#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
	char mess[256];
    char sent_mesg[256]="Sending the message from the server";
    int sent;
    unsigned int len;
	//create a server socket
	int sock;
	sock=socket(AF_INET,SOCK_STREAM,0);
	//server address 
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_port=htons(9002);
	server.sin_addr.s_addr=INADDR_ANY;
    len=sizeof(struct sockaddr_in);
	//bind the socket
	bind(sock,(struct sockaddr*)&server,len);
	listen(sock,5);
	int cli;
	cli=accept(sock,(struct sockaddr*)&client,&len);
 
    printf("Port address connected :%u\n",ntohs(client.sin_port));
    
	//receive the message
	recv(cli,&mess,sizeof(mess),0);
    //print the client response
    printf("The server received data:%s\n",mess);
    //send the message
    sent=send(cli,sent_mesg,sizeof(sent_mesg),0);
    sleep(5);
    //printing sending message
    printf("Send %d bytes to the client:%s",sent,inet_ntoa(client.sin_addr));
    close(cli);
    sleep(5);
	//close the socket
	close(sock);
    sleep(5);	
    return 0;
}

