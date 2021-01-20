#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
//creating the server socket
int server_sock=socket(AF_INET,SOCK_STREAM,0);
//define the server address
struct sockaddr_in server,client;
server.sin_family=AF_INET;
server.sin_port=htons(9002);
server.sin_addr.s_addr=INADDR_ANY;
unsigned int len=sizeof(struct sockaddr_in);
//bind the address
bind(server_sock,(struct sockaddr*)&server,len);
//listen
listen(server_sock,5);
int i=1;
while(i<=3)
{
//accept the message from the client
int cli=accept(server_sock,(struct sockaddr*)&client,&len);
//receive the message from the client
char recvmsg[256];
recv(cli,&recvmsg,sizeof(recvmsg),0);
printf("We have recived message is %s from the port :%u,on the ip:%s\n",recvmsg,ntohs(client.sin_port),inet_ntoa(client.sin_addr));
//send the message to client
char sendmsg[256]="We have recieved the message from your end";
send(cli,sendmsg,sizeof(sendmsg),0);
sleep(10);
//close the client
close(cli);
i++;
}
close(server_sock);
sleep(10);
return 0;
}



