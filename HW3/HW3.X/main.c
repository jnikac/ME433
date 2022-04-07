#include <stdio.h>
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "uart_rw.h"

int main() {
    UART_Startup();
    while(1){
        if(!PORTBbits.RB4){
            char hold[100];
            sprintf(hold, "%s\r\n", "Hello");
            WriteUART1(hold);
        }
    }
}