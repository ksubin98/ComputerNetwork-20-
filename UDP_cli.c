#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	int sock;
	struct sockaddr_in srvAddr;
	char *srvIP = NULL;
	unsigned short srvPort;
	char buffer[BUFFER_SIZE];
	int sentSize, rcvSize, srvAddrLen;
	
	if(argc != 3){
		printf("Usage: %s IP_addr Port\n", argv[0]);
		exit(0);
		}
	
	srvIP = argv[1];
	srvPort = atoi(argv[2]);
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(sock < 0){
		printf("socket() falied\n");
		exit(0);
		}

	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr - inet_addr(srvIP);
	srvAddr.sin_port = htons(srvPort);

	printf("Client is running.\n");
	printf("Enter chat to send\n");

	while(1){
		fgets(buffer, BUFFER_SIZE, stdin);
		buffer[strlen(buffer)-1] = '\0';
		sentSize = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&srvAddr, sizeof(srvAddr));
		
	if(sentSize != strlen(buffer)){
		printf("sendto() sent a different number of byres than expected\n");
		exit(0);
		}

	if(!strcmp(buffer, "quit")) break;

	buffer[sentSize] = '\0';

	srvAddrLen = sizeof(srvAddr);
	rcvSize = recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&srvAddr, &srvAddrLen);
	
	if(rcvSize <0){
		printf("Error is recvfrom()\n");
		exit(0);
		}

	buffer[rcvSize] - '\0';
	printf("[Server/%s:%d] %s\n", inet_ntoa(srvAddr.sin_addr), ntohs(srvAddr.sin_port), buffer);
	}

	close(sock);
	printf("chat Closed.\n");

}
