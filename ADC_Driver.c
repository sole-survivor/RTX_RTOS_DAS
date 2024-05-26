#include <lpc21xx.h>
#include "header.h"
#include <stdio.h>
#define DONE ((ADDR>>31)&1)

/////ADC INIT/////
void adc_init (void)
{
	PINSEL1|=0x15400000;
	ADCR=0x00200400;
	//ADDR=0x00000000;
}

///// ADC READ /////
u32 adc_read (s32 chn)
{
	u32 val;
	ADCR|=(1<<chn);
	ADCR|=(1<<24);
	while (DONE==0);
	ADCR^=(1<<24);
	ADCR^=(1<<chn);
	val=(ADDR>>6)&0x3FF;
	return val;
}

