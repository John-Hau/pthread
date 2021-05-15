main.exe:main.o com_uart_port.o
	gcc -o main.exe main.o com_uart_port.o -lpthread
main.o:main.c ./com_uart/com_uart_port.h
	gcc -c main.c
com_uart_port.o:./com_uart/com_uart_port.c ./com_uart/com_uart_port.h
	gcc -c ./com_uart/com_uart_port.c	

clean:
	rm main.exe 
