# MPLAB IDE generated this makefile for use with GNU make.
# Project: adc_test.mcp
# Date: Fri Mar 25 03:10:06 2016

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

adc_test.cof : adc.o
	$(LD) /p18F4480 /l"C:\Program Files\Microchip\mplabc18\v3.46\lib" "adc.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"adc_test.cof" /M"adc_test.map" /W

adc.o : adc.c lcd_diver.c C:/Program\ Files/Microchip/mplabc18/v3.47/h/delays.h adc_driver.c C:/Program\ Files/Microchip/mplabc18/v3.47/h/string.h uart_driver.c adc.c C:/Program\ Files/Microchip/mplabc18/v3.47/h/p18f4480.h C:/Program\ Files/Microchip/mplabc18/v3.47/h/p18cxxx.h delay.h C:/Program\ Files/Microchip/mplabc18/v3.47/h/stddef.h
	$(CC) -p=18F4480 "adc.c" -fo="adc.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "adc.o" "adc_test.cof" "adc_test.hex"

