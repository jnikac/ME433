#include <stdio.h>
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "uart_rw.h"
#include "spi.h"
#include <math.h>

#define PI 3.14159265

void sendVolt(unsigned char, unsigned char);

int main() {
    UART_Startup();
    double i = 0;
    double j = 0;
    while(1){
        if(i < 128){
            sendVolt(0, i*2);
        }
        else{
            sendVolt(0, (255-i)*2);
        }
        if(i == 255){
            i = 0;
        }
        i++;
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 48000000 / 610){}
  
}
}

void sendVolt(unsigned char c, unsigned char volt){
    unsigned short p = (c << 15);
    p = p|(0b111 << 12);
    p = p|(volt << 4);
    LATAbits.LATA0 = 0;
    spi_io(p>>8);
    spi_io(p);
    LATAbits.LATA0 = 1;
    
}