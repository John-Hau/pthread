#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>


int main(int argc, char* argv[])
{


	if(argc < 2)
	{

		fprintf(stderr,"usage: %s port\n",argv[0]);
		exit(EXIT_FAILURE);

	}













	return 0;
}
