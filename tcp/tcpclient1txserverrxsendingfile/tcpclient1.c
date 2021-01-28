#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<errno.h>
#include<strings.h>
int main()
{
	//create a socket//
	int sock;
	sock=socket(AF_INET,SOCK_STREAM,0);
	//specify the address of the socket//
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(9002);
	server.sin_addr.s_addr=INADDR_ANY;
	int connection_status=connect(sock,(struct sockaddr*)&server,sizeof(server));
	//check for error connection status//
	if(connection_status==-1)
	{
		printf("There is an error making a connection to the remote socket\n\n");
	}
	//send file to the server//
	char mesg[1024]={0};
    int n;
	 FILE *fp;
    char *filename="send.txt";
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        perror("error in reading the file");
        exit(1);
    }
    while(fgets(mesg,sizeof(mesg),fp)!=NULL)
    {
        if(send(sock,mesg,sizeof(mesg),0)==-1)
        {
            perror("Error in sending the file");
            exit(1);
        }
        bzero(mesg,sizeof(mesg));
    }
    printf("successfully file is sent");
    //close the socket
	close(sock);
	return 0;
}
