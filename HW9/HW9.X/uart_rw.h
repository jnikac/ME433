#ifndef UART__H__
#define UART__H__

#include <xc.h>
#include <sys/attribs.h>

#define SYSFREQ 48000000

void UART_Startup();
void ReadUART1(char * string, int maxLength);
void WriteUART1(const char * string);

#endif