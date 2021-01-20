#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
int main()
{
//create a socket
int client_sock=socket(AF_INET,SOCK_STREAM,0);
//specify an address for client
struct sockaddr_in client;
client.sin_family=AF_INET;
client.sin_port=htons(9007);
client.sin_addr.s_addr=INADDR_ANY;
unsigned int len=sizeof(struct sockaddr_in);
bind(client_sock,(struct sockaddr*)&client,len);
//specify server address to connect
struct sockaddr_in server;
server.sin_family=AF_INET;
server.sin_port=htons(9002);
server.sin_addr.s_addr=INADDR_ANY;
int connection=connect(client_sock,(struct sockaddr*)&server,len);
//checking connection
if(connection==-1)
{
printf("Error has been occured:");
}
while(1)
{
//sending message to the server
char sendmsg[256];
printf("Send message to server");
scanf("%s",sendmsg);
send(client_sock,sendmsg,sizeof(sendmsg),0);

//receive message from server
char recvmsg[256];
recv(client_sock,&recvmsg,sizeof(recvmsg),0);
printf("The server mesage recived :%s\n",recvmsg);

if(strcmp(sendmsg,"Quit")==0)
{
close(client_sock);
    break;
}
}
return 0;
}

