#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<libgen.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netinet/sctp.h>
#include<arpa/inet.h>
#define MY_PORT_NUM 62324
static void die(const char*s)
{
perror(s);
exit(1);
}
static void server(void)
{
int listen_fd,conn_fd,flags,ret,in;
struct sctp_sndrcvinfo sndrcvinfo;
struct sockaddr_in servaddr={
.sin_family=AF_INET,
.sin_addr.s_addr=htonl(INADDR_ANY),
.sin_port=htons(MY_PORT_NUM),
};
struct sctp_initmsg initmsg={
.sinit_num_ostreams=5,
.sinit_max_instreams=5,
.sinit_max_attempts=4,
};
listen_fd=socket(AF_INET,SOCK_STREAM,IPPROTO_SCTP);
if(listen_fd<0)
{
die("socket");
}
ret=bind(listen_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(ret<0)
{
die("bind");
}
ret=setsockopt(listen_fd,IPPROTO_SCTP,SCTP_INITMSG,&initmsg,sizeof(initmsg));
if(ret<0)
{
die("setsockopt()");
}
ret=listen(listen_fd,initmsg.sinit_max_instreams);
if(ret<0)
{
die("listen()");
}
for(;;)
{
char buffer[1024];
char send[1024];
printf("waiting for connection");
fflush(stdout);
conn_fd=accept(listen_fd,(struct sockaddr*)NULL,NULL);
if(conn_fd<0)
{
die("accept()");
}
printf("new client connected");
fflush(stdout);
in=sctp_recvmsg(conn_fd,buffer,sizeof(buffer),NULL,0,&sndrcvinfo,&flags);
printf("Received data:%s\n",buffer);
printf("send message to client:");
scanf("%s",send);
in=sctp_sendmsg(conn_fd,send,sizeof(send),NULL,0,0,0,0,0,0);
if(in>0)
{
die("sctp_sendmsg");
}
close(conn_fd);
}
}
static void client(void)
{
int conn_fd,ret,flags;
struct sctp_sndrcvinfo sndrcvinfo;
char recv[1024];
char msg[1024];
printf("Enter message to send:");
scanf("%s",msg);
struct sockaddr_in servaddr=
{
.sin_family=AF_INET,
.sin_port=htons(MY_PORT_NUM),
.sin_addr.s_addr=inet_addr("127.0.0.1"),
};
conn_fd=socket(AF_INET,SOCK_STREAM,IPPROTO_SCTP);
if(conn_fd<0)
{
die("socket()");
}
ret=connect(conn_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(ret<0)
{
die("connect()");
}
ret=sctp_sendmsg(conn_fd,msg,sizeof(msg),NULL,0,0,0,0,0,0);
if(ret<0)
{
die("sctp_sendmsg");
}
ret=sctp_recvmsg(conn_fd,recv,sizeof(recv),NULL,0,&sndrcvinfo,&flags);
printf("recived data :%s\n",recv);

close(conn_fd);
}
int main(int argc,char **argv)
{
if(strstr(basename(argv[0]),"server"))
server();
else
client();
return 0;
}
