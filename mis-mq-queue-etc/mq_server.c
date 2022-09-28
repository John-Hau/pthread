#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<mqueue.h>

#define MQ1              "/MQ1"
#define MQ1_PERM         0660
#define MQ1_MSG_MAX_SIZE 256
#define MQ1_MAX_MSG      10 

mqd_t mqd_server;

int main(int argc,char* argv[])
{

	struct mq_attr  attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = MQ1_MAX_MSG;
	attr.mq_msgsize = MQ1_MSG_MAX_SIZE;
	attr.mq_curmsgs = 0;

	if((mqd_server = mq_open(MQ1,O_RDWR|O_CREAT,MQ1_PERM,&attr)) < 0)
	{
		perror("mq_open error");
		exit(EXIT_FAILURE);
	}



	ssize_t len;
	char buf[MQ1_MSG_MAX_SIZE];	
	memset(buf,0,sizeof(buf));

	if((len = mq_receive(mqd_server,buf,MQ1_MSG_MAX_SIZE,0)) < 0)
	{

		perror("mq_receive error");
		exit(EXIT_FAILURE);

	}

	printf("msg is %s\n",buf);

	mq_close(mqd_server);
	mq_unlink(MQ1);


	




	return 0;

}

