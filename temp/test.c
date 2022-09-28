#include <stdio.h>      
#include <stdlib.h>    
#include <string.h>       
#include <unistd.h>      
#include <sys/types.h>   
#include <sys/stat.h>  
#include <fcntl.h>      
#include <termios.h>   
#include <errno.h>       
#include <getopt.h>   
#include <time.h>     
#include <sys/select.h>    
#include "com_uart_port.h"


int main (int argc, char *argv[])
{


	int fdSerial = init_com_port(USER_COM0,115200);

	uint8_t rcv_buf[128]={0};
	uint8_t send_buf[128]={0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x31,0x32,0x33,0x34,0x35,0x36,0x37};
	int len;
	uint32_t ch_cnt =0;

	while(1)    //循环读取数据
	{

		com_send(fdSerial, send_buf, 16);
		//usleep(300000);

		com_recv(fdSerial, rcv_buf, 128, 1000);

		if(rcv_buf[0] != send_buf[0]) 
		{
			perror("com data error");
			exit(EXIT_FAILURE);

		}
		else
		{
			printf("rec is %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %d\n",\
					rcv_buf[0],rcv_buf[1],rcv_buf[2],rcv_buf[3],rcv_buf[4],rcv_buf[5],rcv_buf[6],rcv_buf[7],\
					rcv_buf[8],rcv_buf[9],rcv_buf[10],rcv_buf[11],rcv_buf[12],rcv_buf[13],rcv_buf[14],rcv_buf[15],++ch_cnt);
		}



		send_buf[0]++;
		rcv_buf[0]=0;

		usleep(30000);    //休眠10ms
		//sleep(1);    //休眠1s
		if(send_buf[0] > 0x39)
			break;
	}


	close(fdSerial);
	return 0;
}
