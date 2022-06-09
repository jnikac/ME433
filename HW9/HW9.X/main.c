#include <stdio.h>
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "uart_rw.h"
#include "ws2812b.h"


int main(){
     UART_Startup();
     ws2812b_setup();
     
     wsColor LEDs[4];
     int i = 0;
     while(1){
        LEDs[0] = HSBtoRGB(i, .5, .5);
        LEDs[1] = HSBtoRGB(i + 20 , .5, .5);
        LEDs[2] = HSBtoRGB(i + 40, .5, .5);
        LEDs[3] = HSBtoRGB(i + 80, .5, .5);

  
        ws2812b_setColor(LEDs, 4);
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 48000000 / 1000){} //wait
        i++;
        if(i == 255){
            i = 0;
        }

     }

 }