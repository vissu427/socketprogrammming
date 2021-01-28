#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<errno.h>
#include<strings.h>
int main()
{
	char mess[1024];
	//create a server socket
	int sock;
	sock=socket(AF_INET,SOCK_STREAM,0);
	//server address 
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_port=htons(9002);
	server.sin_addr.s_addr=INADDR_ANY;
	//bind the socket
	bind(sock,(struct sockaddr*)&server,sizeof(server));
	listen(sock,5);
	int cli;
    unsigned int len;
    len=sizeof(client);
	cli=accept(sock,(struct sockaddr*)&client,&len);
	//recieve the message from the client
	int n;
    FILE *fp;
    char *filename="recv.txt";
    fp=fopen(filename,"w");
    while(1)
      {
        n=recv(cli,mess,sizeof(mess),0);
        if(n<=0)
         {
            break;
            
         }
        fprintf(fp,"%s",mess);
        bzero(mess,sizeof(mess));
      }
        printf("file is received");
                    
            
    
    //print the client response
    //printf("The server received data:%s\n",mess);
	//close the socket
	close(sock);
	return 0;
}

