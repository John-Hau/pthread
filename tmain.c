#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>



int main(int argc,char* argv[])
{

#if 0
	if(mkfifo("mypipe",0600) == -1)
	{

		perror("mkfifo failed\n");
		exit(EXIT_FAILURE);

	}
#endif


	int fd; 
	fd = open("mypipe",O_WRONLY);

	if(fd < 0)
	{
		perror("open mypipe failed\n");
		exit(EXIT_FAILURE);
	}



	char buf[16] = {0};
	write(fd,"hello",6);

	close(fd);



	fd = open("mypipe",O_RDONLY);

	if(fd < 0)
	{
		perror("open mypipe failed\n");
		exit(EXIT_FAILURE);
	}


	read(fd,buf,12);
	printf("read %s\n",buf);


	close(fd);


	return 0;
}
