#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

int sockfd;

void prompt_client(struct sockaddr_in * sockaddr)
{

	char ip[16] = {0};

	int port = ntohs(sockaddr->sin_port);

	inet_ntop(AF_INET,&sockaddr->sin_addr.s_addr,ip,sizeof(ip));

	printf("client port is %d\n",port);
	printf("client addr is %s\n",ip);

}









int main(int argc,char* argv[])
{

	if(argc < 2)
	{
		fprintf(stderr,"usage: %s port\n",argv[0]);
		exit(EXIT_FAILURE);
	}


	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{

		perror("socket failed\n");
		exit(EXIT_FAILURE);

	}


	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[1]));
	serveraddr.sin_addr.s_addr = INADDR_ANY;



	if(bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
	{

		perror("bind faild\n");
		exit(EXIT_FAILURE);

	}


	if(listen(sockfd,10) < 0)
	{
		perror("listen failed\n");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in clientaddr;
	socklen_t len  = sizeof(clientaddr);

	while(1)
	{

		int fd =  accept(sockfd,(struct sockaddr*)&clientaddr,&len);
		if(fd < 0)
			continue;


		prompt_client(&clientaddr);

		long t = time(NULL);
		char *s = ctime(&t);
		if(write(fd,s,strlen(s))  != strlen(s))
		{
			printf("server write failed\n");
		}


	}









}
