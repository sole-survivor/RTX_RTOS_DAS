#include<lpc21xx.h>
#include"header.h"
#define CS0 (1<<7)
#define SPIF ((S0SPSR>>7)&1)
void spi0_init(void)
{
  PINSEL0|=0x1500;
  IODIR0|=CS0;
  IOSET0|=CS0;
  S0SPCR=0x20;
  S0SPCCR=15;
}
u8 spi0(u8 data)
{
 S0SPDR=data;
 while(SPIF==0);
 return S0SPDR;
}

