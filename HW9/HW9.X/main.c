#include <stdio.h>
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "uart_rw.h"
#include "ws2812b.h"


int main(){
     UART_Startup();
     ws2812b_setup();
     
     wsColor LEDs[4];
     LEDs[0].r = 0b11111111;
     LEDs[0].g = 0b00000001;
     LEDs[0].b = 0b00000001;
     
     LEDs[1].r = 0b00000001;
     LEDs[1].g = 0b11111111;
     LEDs[1].b = 0b00000001;
     
     LEDs[2].r = 0b00000001;
     LEDs[2].g = 0b00000001;
     LEDs[2].b = 0b11111111;
     
     LEDs[3].r = 0b11111111;
     LEDs[3].g = 0b11111111;
     LEDs[3].b = 0b11111111;
     ws2812b_setColor(LEDs, 4);

 }