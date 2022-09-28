enum COM_PORT {
	USER_COM0,
	USER_COM1,
	USER_COM2,
};


//#define DEV_NAME    "/dev/ttymxc3"    ///< 串口设备
//#define DEV_NAME    "/dev/ttyS19"    ///< 串口设备
//#define DEV_NAME    "/dev/ttyS26"    ///< 串口设备
#define DEV_NAME    "/dev/ttyS9"    ///< 串口设备

extern int32_t init_com_uart(enum COM_PORT port,uint32_t baudrate);
extern int com_uart_recv(int fd, char *rcv_buf, int data_len, int timeout);
extern int com_uart_send(int fd, char *send_buf, int data_len);
