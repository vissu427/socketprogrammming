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
int sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
// with out binding the info we are sending the message to server 
//server will pickup some random port number
/*//ADDRESS OF THE CLIENT
struct sockaddr_in client;
client.sin_family=AF_INET;
client.sin_port=htons(9002);
client.sin_addr.s_addr=inet_addr("127.0.0.1");
unsigned int len;

//bind the client address
if((bind(sock,(struct sockaddr*)&client,len))==-1
{
printf("Error is occured");
}*/
//addres of the server
unsigned int len=sizeof(struct sockaddr_in);
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
