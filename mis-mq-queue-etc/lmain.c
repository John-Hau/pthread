#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>


void* client_task(void*arg)
{

	while(1)
	{
		printf("client\n");
		sleep(1);

	}


}



void* server_task(void* arg)
{
	while(1)
	{
		printf("server\n");
		sleep(1);

	}


}


int main(int argc,char* argv[])
{

	pthread_t client, server;
	if(pthread_create(&client,NULL,client_task,NULL) != 0)
	{
		perror("pthread create client\n");
		exit(EXIT_FAILURE);

	}


	if(pthread_create(&server,NULL,server_task,NULL) != 0)
	{
		perror("pthread create server\n");
		exit(EXIT_FAILURE);

	}

	if(pthread_join(client,NULL) != 0)
	{

		perror("pthread join client\n");
		exit(EXIT_FAILURE);

	}


	if(pthread_join(server,NULL) != 0)
	{
		perror("pthread join server\n");
		exit(EXIT_FAILURE);

	}

	return 0;
}
