#include <stdio.h>
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "i2c_master_noint.h"
#include "font.h"
#include "ssd1306.h"
#include "uart_rw.h"

void draw_char(unsigned char startx, unsigned char starty, unsigned char ascii);

int main() {
     UART_Startup();
     i2c_master_setup();
     ssd1306_setup();
     char message[50];
     for(int i = 0; i < 100000; ++i){
        _CP0_SET_COUNT(0);
        sprintf(message, "my var = %d", i);
        draw_char_array(0, 0, message);
        ssd1306_update();
        double t = ((double)_CP0_GET_COUNT())/(48000000.0/2.0); //time in seconds
        sprintf(message, "FPS = %f", 1.0/t);
        draw_char_array(0, 10, message);
     }
     
}
void draw_char_array(unsigned char startx, unsigned char starty, unsigned char * carray){
    int count = 0;
    int complete = 0;
    int x_pos = startx;
    int y_pos = starty;
    while(!complete){
        if(carray[count] == '\0'){
            complete = 1;
        }
        else{
            draw_char(x_pos, y_pos, carray[count]-32);
            count = count + 1;
            if(x_pos > 118){ //if we are too close to end to make a new char
                x_pos = 0; //reset x 
                y_pos = y_pos + 8; //jump to next line
            }
            else{
                x_pos = x_pos + 5; //if not to close to line just move 5 spaces over
            }
        }
    }
}

void draw_char(unsigned char startx, unsigned char starty, unsigned char ascii){
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 8; ++j){
            ssd1306_drawPixel(startx + i, starty + j, (ASCII[ascii][i] >> j) & 0b1); //this should set the x and y positions then print the char
        }
    }
}
