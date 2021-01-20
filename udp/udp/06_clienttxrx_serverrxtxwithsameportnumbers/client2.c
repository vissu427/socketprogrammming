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
//create a socket
int sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
//ADDRESS OF THE CLIENT
struct sockaddr_in client;
client.sin_family=AF_INET;
client.sin_port=htons(9003);
client.sin_addr.s_addr=inet_addr("127.0.0.1");
unsigned int len;
len=sizeof(struct sockaddr_in);
//bind the client address
if((bind(sock,(struct sockaddr*)&client,len))==-1)
{
perror("Error is occured");
exit(-1);
}
//addres of the server
struct sockaddr_in server;
server.sin_family=AF_INET;
server.sin_port=htons(9001);
server.sin_addr.s_addr=inet_addr("127.0.0.1");
//Send the message to the server
char msg[256];
printf("Enter message to send the server:");
scanf("%s",msg);
sendto(sock,msg,strlen(msg),0,(struct sockaddr*)&server,sizeof(server));
char recvmsg[256];
recvfrom(sock,recvmsg,sizeof(recvmsg),0,(struct sockaddr*)&server,&len);
printf("Received message from server is %s",recvmsg);
close(sock);
return 1;
} 

