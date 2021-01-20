#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
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
printf("Error has been occured");
}
//recieve message from the clientint k;
/*client.sin_family=AF_INET;
client.sin_port=htons(9002);
client.sin_addr.s_addr=inet_addr("127.0.0.1");*/

char recv[256];
recvfrom(server_sock,recv,sizeof(recv),0,(struct sockaddr*)&client,&len);
//recv[k]="\0";
printf("recived message from the client is :%s",recv);
close(server_sock);
return 0;
}
