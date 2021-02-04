#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
void *connection(void *);
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
while(1)
{
printf("Waiting for newconnections to accept");
//accept the message from the client
int cli=accept(server_sock,(struct sockaddr*)&client,&len);
printf("New client was connected to the port %u from an ip address %s\n",ntohs(client.sin_port),inet_ntoa(client.sin_addr));
printf("create a thread for new client:");
pthread_t thread;
int *new_sock;
new_sock=malloc(1);
*new_sock=cli;
if(pthread_create(&thread,NULL,connection,(void*)new_sock)<0)
{
printf("Thread cannot created");
}
int n;
printf("enter the value 0 for break, 1 for continue:\n");
scanf("%d",&n);
if(n==0)
{
break;
}
}
return 1;
}
void *connection(void *sock_desc)
{
int cli=*(int*)sock_desc;
printf("Client individual thread started:\n");
while(1)
{
//receive the message from the client
char recvmsg[256];
recv(cli,&recvmsg,sizeof(recvmsg),0);
printf("We have recived message is %s from the port \n",recvmsg);

//send the message to client
char sendmsg[256]="We have recieved the message from your end";
strcat(sendmsg,recvmsg);
send(cli,sendmsg,sizeof(sendmsg),0);
//close the client

if(strcmp(recvmsg,"Quit")==0)
{
close(cli);
break;
}
}
}


