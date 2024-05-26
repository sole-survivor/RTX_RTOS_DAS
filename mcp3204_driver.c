#include<lpc21xx.h>
#include"header.h"
#define CS0 (1<<7)
unsigned short int mcp3204_adc_read(unsigned int ch_num)
{
   unsigned char byteH=0,byteL=0,channel=0;
   unsigned short int result;
   channel=ch_num<<6;
   IOCLR0=CS0;
   spi0(0x06);
   byteH=spi0(channel);
   byteL=spi0(0x0);
   IOSET0=CS0;
   byteH&=0x0F;
   result=(byteH<<8)| (byteL);
   return result;
}

