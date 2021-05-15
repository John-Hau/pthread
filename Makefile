main.exe:main.o com_uart_port.o modbus.o modbus-rtu.o modbus-data.o
	gcc -o main.exe main.o com_uart_port.o modbus.o modbus-rtu.o modbus-data.o -lpthread
main.o:main.c ./com_uart/com_uart_port.h
	gcc -c main.c
com_uart_port.o:./com_uart/com_uart_port.c ./com_uart/com_uart_port.h
	gcc -c ./com_uart/com_uart_port.c	
modbus.o:./modbus/modbus.c ./modbus/modbus.h ./modbus/modbus-private.h ./modbus/modbus-rtu-private.h ./modbus/config.h ./modbus/modbus-version.h ./modbus/modbus-tcp.h
	gcc -c ./modbus/modbus.c	

modbus-rtu.o:./modbus/modbus-rtu.c ./modbus/modbus.h ./modbus/modbus-private.h ./modbus/modbus-rtu-private.h ./modbus/config.h ./modbus/modbus-version.h ./modbus/modbus-tcp.h
	gcc -c ./modbus/modbus-rtu.c	

modbus-data.o:./modbus/modbus-data.c ./modbus/modbus.h ./modbus/modbus-private.h ./modbus/modbus-rtu-private.h ./modbus/config.h ./modbus/modbus-version.h ./modbus/modbus-tcp.h
	gcc -c ./modbus/modbus-data.c	
clean:
	rm main.exe 
	rm *.o 
