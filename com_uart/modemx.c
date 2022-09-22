
#include "modemx.h"
#include <string.h>
#include <stdint.h>

int32_t xmodem_cal_crc(char *ptr, int count)
{
	int  crc;
	char i;
	crc = 0;
	while (--count >= 0)
	{
		crc = crc ^ (int) *ptr++ << 8;
		i = 8;
		do
		{
			if (crc & 0x8000)
				crc = crc << 1 ^ 0x1021;
			else
				crc = crc << 1;
		} while(--i);
	}
	return (crc);
}

int32_t xmodem_receiver_start_initial_token(int fd,uint8_t token)
{

	com_send(fd,&token,1);
	return 0;
}



int32_t xmodem_receiver_get_one_packet(int fd, uint8_t*buf)
{
	com_recv(fd, buf, XMODEM_PACKET_LEN, 1000);

	uint8_t is_ack;
	is_ack = XMODEM_ACK;
	com_send(fd,&is_ack,1);
	return 0;
}




int32_t xmodem_receiver_state_machine(int fd, uint8_t*buf)
{

	switch(xmodem_state)
	{
		case XMODEM_SOH:
			break;

		case XMODEM_EOT:
			break;


		case XMODEM_GET_PACKET:
			break;


		default:
			break;

	}

}
