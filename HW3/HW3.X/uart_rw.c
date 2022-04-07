#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "uart_rw.h"

// DEVCFG0
#pragma config DEBUG = OFF // disable debugging
#pragma config JTAGEN = OFF // disable jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // disable flash write protect
#pragma config BWP = OFF // disable boot write protect
#pragma config CP = OFF // disable code protect

// DEVCFG1
#pragma config FNOSC = FRCPLL // use fast frc oscillator with pll
#pragma config FSOSCEN = OFF // disable secondary oscillator
#pragma config IESO = OFF // disable switching clocks
#pragma config POSCMOD = OFF // primary osc disabled
#pragma config OSCIOFNC = OFF // disable clock output
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // disable clock switch and FSCM
#pragma config WDTPS = PS1048576 // use largest wdt value
#pragma config WINDIS = OFF // use non-window mode wdt
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz fast rc internal oscillator
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz (div by 2 gets 4MHz)
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV (mult by 24 to get 96MHz)
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz (divide by 2 to get 48MHz)

// DEVCFG3
#pragma config USERID = 32 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF// allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations

#define DESIRED_BAUD 230400

void UART_Startup(){
    __builtin_disable_interrupts();
    U1MODEbits.BRGH = 0;
    U1BRG = ((SYSFREQ / DESIRED_BAUD) /16) - 1;  //set desired baud
    
    //8 bit no parity stop bit
    
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;
    
    //setup the RPnR values
    
    U1RXRbits.U1RXR = 0b0000;
    RPB3Rbits.RPB3R = 0b0001;
    
    
    //configure TX and RX pins as inp and out
    
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    
    //enable uart
    
    U1MODEbits.ON = 1;
    
       // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    // do your TRIS and LAT commands here
    TRISBbits.TRISB4 = 1; //set pin B4 as an input pin
    TRISAbits.TRISA4 = 0; //set pin A4 as an output pin

    
    __builtin_enable_interrupts();
}

void ReadUART1(char * message, int maxLength){
    char data = 0;
    int complete = 0, num_bytes = 0;
    
    while(!complete){
        if(U1STAbits.URXDA){
            data = U1RXREG;
            if ((data == '\n') || (data == '\r')){
                complete = 1;
            }
            else{
                message[num_bytes] = data;
                ++num_bytes;
                
                if (num_bytes >= maxLength){
                    num_bytes = 0;
                }
            }
        }
    }
    message[num_bytes] = '\0';
}

void WriteUART1(const char * string){
    while (*string != '\0'){
        while(U1STAbits.UTXBF){
            ;
        }
        U1TXREG = *string;
        ++string;
    }
}
