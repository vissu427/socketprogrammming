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
//create a socket
int sock=socket(PF_INET6,SOCK_DGRAM,0);
if(sock<0)
{
printf("errorr");
}
//ADDRESS OF THE CLIENT
struct sockaddr_in6 server;
server.sin6_family=AF_INET6;
server.sin6_port=htons(12346);
inet_pton(AF_INET6,"::1",&server.sin6_addr);
//server.sin6_addr=in6addr_any;
unsigned int len;
//bind the client address
if((bind(sock,(struct sockaddr*)&server,sizeof(server)))==-1)
{
printf("Error is occured");
}
//addres of the server
memset(&server,0,sizeof(server));
struct sockaddr_in6 client;
client.sin6_family=AF_INET6;
client.sin6_port=htons(12345);
inet_pton(AF_INET6,"::1",&client.sin6_addr);
//client.sin6_addr=in6addr_any;
len=sizeof(client);
//Send the message to the server
char msg[256];
printf("Enter message to send the server:");
scanf("%s",msg);
sendto(sock,msg,sizeof(msg),0,(struct sockaddr*)&client,sizeof(client));
char recvmsg[256];
recvfrom(sock,recvmsg,sizeof(recvmsg),0,(struct sockaddr*)&client,&len);
printf("Received message from server is %s\n",recvmsg);
close(sock);
return 1;
} 

