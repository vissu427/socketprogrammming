#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
int main()
{
//creating the socket
int server_sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
//address of server & client
struct sockaddr_in server,client;
server.sin_family=AF_INET;
server.sin_port=htons(9001);
server.sin_addr.s_addr=inet_addr("127.0.0.1");
unsigned int len=sizeof(struct sockaddr);

if((bind(server_sock,(struct sockaddr*)&server,len))==-1)
{
perror("Error has been occured");
exit(-1);
}
//recieve message from the clientint k;
/*client.sin_family=AF_INET;
client.sin_port=htons(9002);
client.sin_addr.s_addr=inet_addr("127.0.0.1");*/
unsigned int size=sizeof(server);
int i=1;
while(i<=2)
{
char recv[256];
int k=recvfrom(server_sock,recv,sizeof(recv),0,(struct sockaddr*)&client,&size);
recv[k]='\0';
printf("recived message from the client is :%s:the port is %u\n",recv,ntohs(client.sin_port));
char send[256];
printf("enter message to send");
scanf("%s",send);
sendto(server_sock,send,strlen(send),0,(struct sockaddr*)&client,sizeof(client));
i++;
}
close(server_sock);
sleep(5);

return 0;
}
