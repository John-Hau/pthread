#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define ERR_MSG_EXIT(m) {                    \ 
	                 perror(m);          \
			 exit(EXIT_FAILURE); \
			}                    \

#define MSGQ_SIZE  1024

typedef struct msgq
{
	long type;
	uint8_t buffer[MSGQ_SIZE];
}msgq_t;









msgq_t m1,m2,m3;


int main(int argc, char* argv[])
{


	key_t key = 1919;
	int msgflg = 0;
	int msgid;

	if((msgid = msgget(key,msgflg | IPC_CREAT)) < 0)
	{
		ERR_MSG_EXIT("msgget: failed");
	} 




	if(msgrcv(msgid,&m1,MSGQ_SIZE,2,msgflg) < 0)
	{

		ERR_MSG_EXIT("msgrcv: failed");
	}


	printf("msg received is %s\n",m1.buffer);



	printf("done\n");

	return 0;



}















