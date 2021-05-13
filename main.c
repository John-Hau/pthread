#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <mqueue.h>
#include "com_uart_port.h"

#define TEST_CNT    100

#define MSG_IPC_BUF_SIZE  8192

//gcc -D_REENTRANT -D_POSIX_C_SOURCE  thread2.c -o thread2.exe   -lpthread


extern FILE*fp;
int fdSerial; 

pthread_mutex_t  mutex_file = PTHREAD_MUTEX_INITIALIZER;

#define MSG_LEN  128
typedef mqd_t msg_id_t;

typedef struct msg_ipc
{
	uint8_t len;
	uint8_t msg_content[MSG_LEN];
}msg_ipc_t;


mqd_t mqfd;



uint8_t msg_sbuffer[8192]={0};
uint8_t msg_rbuffer[8192]={0};

struct mq_attr attr;

void*thread_function(void*arg);
void*thread_read(void*arg);

char message[64] = "Hello World";

void *thread_function(void*arg)
{
	printf("thread function is running. Argument was %s\n",(char*)arg);
	sleep(3);
	strcpy(message,"Bye");
	pthread_exit("Thank you for the CPU time\n");
}




void *thread_read(void*arg)
{

	printf("thread read is running. Argument was %s\n",(char*)arg);
	sleep(3);
	strcpy(message,"Bye");
	pthread_exit("Thank you for the CPU time\n");

}




int mq_msg_get(msg_id_t msg_id,msg_ipc_t *msg)
{


	int nr=mq_receive(mqfd,msg_rbuffer,8192,0);
	return nr;
}


int mq_msg_put(msg_id_t msg_id,msg_ipc_t *msg)
{

	int ns=mq_send(mqfd,msg->msg_content,msg->len,0);
	return ns;
}



void *thread_get_message_from_uart_port(void*arg)
{

	uint32_t cnt=0;

	char c='1';
	uint32_t m=0;
	while(m<10)
	{
		pthread_mutex_lock(&mutex_file);
		//for(cnt=0;cnt<TEST_CNT;cnt++)
		for(cnt=0;cnt<9;cnt++)
		{
			//printf("pthread_write_console %d\n",cnt+1);
			//printf("abcdefghijklmnopqrstuvwxyz",cnt+1);
			fputc(c+cnt,fp);
		}

		pthread_mutex_unlock(&mutex_file);
		m++;
	}
	pthread_exit("pthread_write_console,Thank you for the CPU time\n");

}



void *thread_read_uart(void*arg)
{
	uint8_t uart_rcv_buf[256]={0};
	while(1)
	{
		//com_recv(fdSerial, rcv_buf, 128, 1000);
		//uint32_t nr = com_recv(fdSerial, uart_rcv_buf, 128, -1);
		uint32_t nr = com_recv(fdSerial, uart_rcv_buf, 1, -1);
		//printf("uart receiving and nr is %d and string is %s\n",nr,uart_rcv_buf);
		printf("uart receiving and nr is %d and ch is %c\n",nr,uart_rcv_buf[0]);
		memset(uart_rcv_buf,0,sizeof(uart_rcv_buf));
	}

	pthread_exit("pthread_read_uart,Thank you for the CPU time\n");

}




void *thread_write_uart(void*arg)
{
	uint8_t uart_send_buf[128]={0};
	strcpy(uart_send_buf,"1 uart hello\n");

	while(1)
	{
		com_send(fdSerial, uart_send_buf, strlen(uart_send_buf));
		sleep(2);
		printf("uart sending\n");


		uart_send_buf[0]++;
		if(uart_send_buf[0] > '9') 
		{
			uart_send_buf[0] = '1';
		}
	}

	pthread_exit("pthread_write_uart,Thank you for the CPU time\n");

}



void *thread_write_console(void*arg)
{

	uint32_t cnt=0;

	char c='1';
	uint32_t m=0;
	while(m<10)
	{
		pthread_mutex_lock(&mutex_file);
		//for(cnt=0;cnt<TEST_CNT;cnt++)
		for(cnt=0;cnt<9;cnt++)
		{
			//printf("pthread_write_console %d\n",cnt+1);
			//printf("abcdefghijklmnopqrstuvwxyz",cnt+1);
			fputc(c+cnt,fp);
		}

		pthread_mutex_unlock(&mutex_file);
		m++;
	}
	pthread_exit("pthread_write_console,Thank you for the CPU time\n");

}



FILE*fp = NULL;

int main(int argc ,char* argv[])
{

	int res;

	pthread_t a_thread;
	pthread_t thread_read_id;
	pthread_t thread_read_uart_id;
	pthread_t thread_write_uart_id;
	pthread_t thread_write_console_id;

	void* thread_result;
	void* thread_read_result;
	void* thread_write_uart_result;
	void* thread_read_uart_result;
	void* thread_write_console_result;

	fdSerial = init_com_port(USER_COM0,115200);

#if 0
	attr.mq_maxmsg=16;
	attr.mq_msgsize=MSG_IPC_BUF_SIZE;
	attr.mq_flags=0;

	//mode_t mode  = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	mqfd=mq_open("myipc",O_RDWR|O_CREAT,0644,&attr);

	if(mqfd == -1)
	{
		perror("mq_open failure");
		exit(EXIT_FAILURE);
	}

	strcpy(msg_sbuffer,"hello");
	int ns=mq_send(mqfd,msg_sbuffer,8,0);
	int nr=mq_receive(mqfd,msg_rbuffer,MSG_IPC_BUF_SIZE,0);

	if(nr >0)
	{
		printf("receiving OK nr is %d msg_rbuffer is %s\n",nr,msg_rbuffer);
	}

	mq_close(mqfd);
	//mq_unlink("./myipc");
	printf("end\n");
//	return 0;


	fp = fopen("test.log","wt");
	if(fp == NULL)
	{

		perror("open test.log failed\n");
		exit(EXIT_FAILURE);

	}

#endif
















#if 0
	res = pthread_create(&a_thread,NULL,thread_function,(void*)message);

	if(res != 0)
	{
		perror("Thread creation failed\n");
		exit(EXIT_FAILURE);
	}

#endif






#if 0
	res = pthread_create(&thread_read_id,NULL,thread_read,(void*)message);

	if(res != 0)
	{
		perror("Thread creation failed\n");
		exit(EXIT_FAILURE);
	}

#endif





#if 1
	res = pthread_create(&thread_write_uart_id,NULL,thread_write_uart,NULL);
	if(res != 0)
	{
		perror("thread_write_uare creation failed\n");
		exit(EXIT_FAILURE);

	}

#endif

#if 1
	res = pthread_create(&thread_read_uart_id,NULL,thread_read_uart,NULL);
	if(res != 0)
	{
		perror("thread_read_uare creation failed\n");
		exit(EXIT_FAILURE);

	}

#endif





#if 0
	res = pthread_create(&thread_write_console_id,NULL,thread_write_console,NULL);
	if(res != 0)
	{

		perror("thread_write_console creation failed\n");
		exit(EXIT_FAILURE);

	}
#endif



#if 0
	res = pthread_join(a_thread,&thread_result);
	if(res !=0)
	{
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);

	}

#endif






	res = pthread_join(thread_write_uart_id,&thread_write_uart_result);
	if(res !=0)
	{
		perror("thread_write_uart join failed\n");
		exit(EXIT_FAILURE);

	}

	res = pthread_join(thread_read_uart_id,&thread_read_uart_result);
	if(res !=0)
	{
		perror("thread_read_uart join failed\n");
		exit(EXIT_FAILURE);

	}


#if 0
	res = pthread_join(thread_write_console_id,&thread_write_console_result);
	if(res !=0)
	{
		perror("thread_write_console join failed\n");
		exit(EXIT_FAILURE);

	}

#endif





	printf("Waiting for thread to finish ... \n");








	//printf("Thread joined.  it returned %s\n",(char*)thread_result);
	//printf("message is now %s\n",message);
	//fclose(fp);
	printf("main thread exit\n");

	exit(EXIT_SUCCESS);



}


