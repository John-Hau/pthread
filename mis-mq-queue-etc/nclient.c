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

int main(int argc,char* argv[])
{

	if(argc  < 3)
	{
		fprintf(stderr,"usage:%s ip port\n",argv[0]);
		exit(EXIT_FAILURE);

	}



	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	}


	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port =  htons(atoi(argv[2]));
	if(inet_pton(AF_INET,argv[1],&serveraddr.sin_addr.s_addr) <= 0)
	{
		perror("inet_pton failed\n");
		exit(EXIT_FAILURE);

	}

        if(connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) <0)	
	{
		perror("connect failed\n");
		exit(EXIT_FAILURE);
	}

	char buf[64] = {0};

	while(1)
	{

		if(read(sockfd,buf,sizeof(buf)) <0)
		{
			perror("read sockfd failed\n");

		}
		printf("buf is %s\n",buf);
		sleep(1);


	}






	return 0;
}
