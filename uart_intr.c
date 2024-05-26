#include <rtl.h>
#include <lpc21xx.h>
unsigned char dummy;
char flg;

extern void UART0_Handler(void) __irq
{
	int temp=U0IIR;
	if (temp&4)
	{
		dummy=U0RBR;
		if(dummy=='\r'||dummy=='\n')
		{
			flg=1;
			isr_evt_set(flg,0xffff);
		}
	}
	VICVectAddr=0;
}

