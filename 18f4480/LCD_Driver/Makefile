# MPLAB IDE generated this makefile for use with GNU make.
# Project: lcd_driver.mcp
# Date: Tue Jul 21 12:24:49 2015

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

lcd_driver.cof : lcd_diver.o
	$(LD) /p18F4480 /l"C:\Program Files\Microchip\mplabc18\v3.46\lib" "lcd_diver.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"lcd_driver.cof" /M"lcd_driver.map" /W

lcd_diver.o : lcd_diver.c C:/Program\ Files/Microchip/mplabc18/v3.46/h/p18f4480.h
	$(CC) -p=18F4480 "lcd_diver.c" -fo="lcd_diver.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "lcd_diver.o" "lcd_driver.cof" "lcd_driver.hex"

