#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>



int main(int argc,char* argv[])
{

	printf("argc is %d\n",argc);
#if 1
	if(argc <2)
	{
		perror("error parameter\n");
	}


	int fd_in;
	int fd_out;

	fd_in = open(argv[1],O_RDONLY);
	fd_out = open(argv[2],O_WRONLY);
	uint8_t rbuf[8]={0};


	while(read(fd_in,rbuf,2) != 0)
	{


//		printf("rbuf is %d %d\n",rbuf[0],rbuf[1]);
		uint8_t c = (rbuf[0] - 0x30 )*16  + rbuf[1] - 0x30;

		printf("v is %d\n",c);
		write(fd_out,&c,1);

	}


	close(fd_in);
	close(fd_out);

//	printf("done\n");

#endif

}
