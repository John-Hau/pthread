#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>


#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>

int sockfd;





void sig_handler(int sig_no)
{

	if(sig_no == SIGINT)
	{
		close(sockfd);
		exit(EXIT_SUCCESS);

	}

}





void out_client(struct sockaddr_in *addr);
{

	int port = ntohs(addr->sin_port);

	char buf[16] = {0};
	if(inet_ntop(AF_INET,(struct sockaddr*)addr->sa_addr.s_addr,buf,sizeof(buf)) <= 0)
	{
		perror("inet_ntop failed")
		exit(EXIT_FAILURE);
	}




}






int main(int argc, char* argv[])
{


	if(argc < 2)
	{
		printf("usage:%s portnum\n",argv[0]);
		exit(EXIT_FAILURE);
	}



	signal(SIGINT,sig_handler);


	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{

		perror("socket  failed\n");
		exit(EXIT_FAILURE);

	}



	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[1]));
	serveraddr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}


	if(listen(sockfd,10) < 0)
	{

		perror("listen failed");
		exit(EXIT_FAILURE);
	}


	struct sockaddr_in clientaddr; 
	socklen_t len = sizeof(clientaddr);

	while(1)
	{

		int fd;

		fd = accept(sockfd,(struct sockaddr*)&clientaddr,&len);
		if(fd < 0)
			continue;




		long t = time(NULL);
		char *s = ctime(&t);
		
		out_client(&clientaddr);

		write(fd,s,strlen(s));

	}

	return 0;

}
