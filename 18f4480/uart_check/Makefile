# MPLAB IDE generated this makefile for use with GNU make.
# Project: uart_check.mcp
# Date: Mon Mar 07 01:05:03 2016

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

uart_check.cof : uart2_check.o
	$(LD) /p18F4480 /l"C:\Program Files\Microchip\mplabc18\v3.46\lib" "uart2_check.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"uart_check.cof" /M"uart_check.map" /W

uart2_check.o : E:/18f4480/test_uart/uart2_check.c C:/Program\ Files/Microchip/mplabc18/v3.47/h/delays.h E:/18f4480/test_uart/lcd_driver.c E:/18f4480/test_uart/uart2_check.c C:/Program\ Files/Microchip/mplabc18/v3.47/h/p18cxxx.h C:/Program\ Files/Microchip/mplabc18/v3.47/h/p18f4480.h E:/18f4480/test_uart/delay.h
	$(CC) -p=18F4480 "E:\18f4480\test_uart\uart2_check.c" -fo="uart2_check.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "uart2_check.o" "uart_check.cof" "uart_check.hex"

