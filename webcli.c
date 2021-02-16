#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	int cSock;
	struct sockaddr_in srvAddr;
	char *srvIP = NULL;
	unsigned short srvPort;
	char buffer[BUFFER_SIZE];
	int ret;
	//char *one = "Get /HTTP/1.1\r\n";
	//char *two = "Host: kostat.go.kr\r\n";
	//char *three = "\r\n";
	int rcvSize;
	
	srvPort = 80;


	if(argc != 2){
		printf("Usage: IP Addr\n");
		exit(0);
		}
	srvIP = argv[1];
	
	//creata socket
	cSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(cSock < 0){
		printf("socket() failed.\n");
		exit(0);
		}

	//set IP, Port
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = inet_addr(srvIP);
	srvAddr.sin_port = htons(srvPort);

	ret = connect(cSock, (struct sockaddr *)&srvAddr, sizeof(srvAddr));
	if(ret < 0){
		printf("Client cannot to the server.\n");
		exit(0);
		}
	else{
		

		memset(buffer, '\0', BUFFER_SIZE+1);
		
		write(cSock, "GET / HTTP/1.1\r\n" , strlen("GET / HTTP/1.1\r\n"));	
		write(cSock, "Host: kostat.go.kr\r\n", strlen("Host: kostat.go.kr\r\n"));
		write(cSock, "\r\n", strlen("\r\n"));

		rcvSize = read(cSock, buffer, BUFFER_SIZE);

		buffer[rcvSize];
	
		if( 0 == rcvSize){
			printf("failed to get Web source\n");
					}
		else{
			printf("%s \n", buffer);
			}
	close(cSock);
	}	

}


