#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define TEST_CNT    100
//gcc -D_REENTRANT -D_POSIX_C_SOURCE  thread2.c -o thread2.exe   -lpthread


extern FILE*fp;


pthread_mutex_t  mutex_file = PTHREAD_MUTEX_INITIALIZER;







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


void *thread_write_uart(void*arg)
{

	uint32_t cnt=0;
	char c='a';
	uint32_t m=0;

	while(m < 100)
	{
		pthread_mutex_lock(&mutex_file);
		//for(cnt=0;cnt<TEST_CNT;cnt++)
		for(cnt=0;cnt<26;cnt++)
		{
			//printf("pthread_write_uart %d\n",cnt+1);
			//printf("1234567890");
			fputc(c+cnt,fp);
		}

		pthread_mutex_unlock(&mutex_file);
		m++;
	}

	pthread_exit("pthread_write_uart,Thank you for the CPU time\n");

}


void *thread_write_console(void*arg)
{

	uint32_t cnt=0;

	char c='1';
	uint32_t m=0;
	while(m<100)
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
	pthread_t thread_write_uart_id;
	pthread_t thread_write_console_id;

	void* thread_result;
	void* thread_read_result;
	void* thread_write_uart_result;
	void* thread_write_console_result;

	fp = fopen("test.log","wt");
	if(fp == NULL)
	{

		perror("open test.log failed\n");
		exit(EXIT_FAILURE);

	}



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
	res = pthread_create(&thread_write_console_id,NULL,thread_write_console,NULL);
	if(res != 0)
	{

		perror("thread_write_console creation failed\n");
		exit(EXIT_FAILURE);

	}
#endif


	printf("Waiting for thread to finish ... \n");

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



	res = pthread_join(thread_write_console_id,&thread_write_console_result);
	if(res !=0)
	{
		perror("thread_write_console join failed\n");
		exit(EXIT_FAILURE);

	}
















	//printf("Thread joined.  it returned %s\n",(char*)thread_result);
	//printf("message is now %s\n",message);
	fclose(fp);
	printf("main thread exit\n");

	exit(EXIT_SUCCESS);



}


