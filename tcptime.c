#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 256

int main(int argc,char *argv[])
{
	int conn,n; // initialising a file descriptor
	struct sockaddr_in serveraddr;
	char buffr[MAX+1]; // buffer
	if((conn=socket(AF_INET,SOCK_STREAM,0))<0) // creating a scoket at client host
		perror("Socket not connected");
	bzero(&serveraddr,sizeof(serveraddr));	//initialising server address to be zero
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(13); //port number for day time service
	if (inet_pton(AF_INET,argv[1],&serveraddr.sin_addr)<=0) // convert character string into network address structure
		perror("Invalid IP adress");
	if (connect(conn,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0) // establishing a TCP connecction with server
		perror("Connection Error");
	while((n=read(conn,buffr,MAX))>0) // received data is stored into buffr
	{
		buffr[n]='\0';
		fputs(buffr,stdout); // printing out the data
	}
	exit(0);
}


