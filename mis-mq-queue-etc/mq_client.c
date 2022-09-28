#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<mqueue.h>

#define MQ1              "/MQ1"
#define MQ1_MAX_MSG       10
#define MQ1_MSG_MAX_SIZE  256
#define MQ1_PERM          0660

mqd_t mqd_client;
int main(int argc,char* argv[])
{

	struct mq_attr  attr;
	attr.mq_flags = 0;
	attr.mq_msgsize = MQ1_MSG_MAX_SIZE;
	attr.mq_maxmsg = MQ1_MAX_MSG;
	attr.mq_curmsgs =0;


	if((mqd_client = mq_open(MQ1,O_RDWR|O_CREAT,MQ1_PERM,&attr)) < 0)
	{

		perror("mq_open error");
		exit(EXIT_FAILURE);

	}


	char* buf="hello world mq";
	if(mq_send(mqd_client,buf,strlen(buf),0) < 0)
	{
		perror("mq_send error");
		exit(EXIT_FAILURE);

	}


	return 0;
}
