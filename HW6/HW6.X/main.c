#include <stdio.h>
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "uart_rw.h"
#include "i2c_master_noint.h"

#define READ 0b01000001
#define WRITE 0b01000000

int main() {
    UART_Startup();
    i2c_master_setup();
    // need to initialize G7 as output
    i2c_master_start(); //send start bit
    i2c_master_send(WRITE); //send the write address
    i2c_master_send(0x00);  //this will tell the chip we want to access the iodir register
    i2c_master_send(0b00000001); //this currently just tells the chip we want all pins to be outputs except GP0
    i2c_master_stop(); //send the stop big 
    while(1){
        
        i2c_master_start(); //send start bit
        i2c_master_send(WRITE); //send the write address
        i2c_master_send(0x09); //tell the chip I want to read GPIO
        i2c_master_restart(); //send the restart bit
        i2c_master_send(READ); //send the read address
        unsigned char val = i2c_master_recv(); //read the values
        i2c_master_ack(1); //acknowledge and stop reading
        i2c_master_stop();
       
        if(val == 0b00000000){ //if GP0 is low, blink light
        i2c_master_start(); //send start bit
        i2c_master_send(WRITE); //send the write address
        i2c_master_send(0x0A); //tell the chip we want to access the OLAT register
        i2c_master_send(0b10000000); //tell the chip to turn on GP7
        i2c_master_stop(); //send stop bit
        
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 48000000 / 10){} //wait
        
        i2c_master_start(); //send start bit
        i2c_master_send(WRITE); //send the write address
        i2c_master_send(0x0A); //tell the chip we want to access the OLAT register
        i2c_master_send(0b00000000); //tell the chip to turn on GP7
        i2c_master_stop(); //send stop bit
        
         _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 48000000 / 10){} //wait
        }

    }
 
}
