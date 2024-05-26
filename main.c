#include <LPC21XX.h>
#include <RTL.h>
#include"header.h"
OS_TID tid1,tid2,tid3,tid4;

__task void task4 (void)
{
	u16 mcp_ret;
	u32 light;
	for (;;)
	{
		mcp_ret = mcp3204_adc_read(0);
		light=100-((mcp_ret*100)/4095);
		uart0_tx_string("Light intensity: ");
		uart0_tx_int(light);
		uart0_tx_string(" % \r\n");
		uart0_tx_string("-------------------------------------------\r\n");
		os_dly_wait(100);
		os_tsk_pass();
	}
}

__task void task3 (void)
{
	tid4=os_tsk_create(task4,1);
	u32 adc2;
	float p_vout,pot;
	for (;;)
	{
		adc2=adc_read(2);
		p_vout=(adc2*3.3)/1023;
		pot=((p_vout/3.3)+0.095)/0.009;
		uart0_tx_string("Pressure is: ");
		uart0_tx_int(pot);
		uart0_tx_string(" kpa \r\n");
		os_dly_wait(100);
		os_tsk_pass();
	}
}

__task void task2 (void)
{
	tid3=os_tsk_create(task3,1);
	u32 adc1;
	float temp,t_vout;
	for (;;)
	{
		adc1=adc_read(1);
		t_vout=(adc1*3.3)/1023;
		temp=(t_vout-0.5)/0.01;
		uart0_tx_string("Temperature is: ");
		uart0_tx_int(temp);
		uart0_tx_string(" Degrees \r\n");
		os_dly_wait(100);
		os_tsk_pass();
	}
}


__task void task1 (void)
{
	tid1=os_tsk_self();
	os_tsk_prio_self(1);
	tid2=os_tsk_create(task2,1);
	u8 s,m,h,dd,mm,yy,w;
	s8* a[8]={" ","SUN","MON","TUE","WED","THU","FRI","SAT"};
	
	for (;;)
	{
		uart0_tx_string("-------------------------------------------\r\n");
		h=i2c_rd(0xD0,0x2);
    m=i2c_rd(0xD0,0x01);
    s=i2c_rd(0xD0,0x0);
		uart0_tx_string("TIME: ");
		h=h&0x1f;
		uart0_tx((h/0x10)+48);
		uart0_tx((h%0x10)+48);
		uart0_tx(':');
		uart0_tx((m/0x10)+48);
		uart0_tx((m%0x10)+48);
		uart0_tx(':');
		uart0_tx((s/0x10)+48);
		uart0_tx((s%0x10)+48);
		uart0_tx_string(" on ");
		dd=i2c_rd(0xD0,0x04);
		mm=i2c_rd(0xD0,0x05);
		yy=i2c_rd(0xD0,0x06);
		w=i2c_rd(0xD0,0x3);
		uart0_tx((dd/0x10)+48);
		uart0_tx((dd%0x10)+48);
		uart0_tx('/');
		uart0_tx((mm/0x10)+48);
		uart0_tx((mm%0x10)+48);
		uart0_tx('/');
		uart0_tx((yy/0x10)+48);
		uart0_tx((yy%0x10)+48);
		uart0_tx_string(" - ");
		uart0_tx_string(a[w]);
		uart0_tx_string("\r\n");
		os_dly_wait(100);
		os_tsk_pass();
	}
}
	
int main()
{
adc_init();
spi0_init();
i2c_init();
uart0_init(9600);
uart0_tx_string("~ ~ ~ ~ ~ Data Acquisition System ~ ~ ~ ~ ~\r\n");
i2c_wr(0xD0,0x0,0x00);
i2c_wr(0xD0,0x1,0x45);
i2c_wr(0xD0,0x2,0X08);
i2c_wr(0xD0,0x3,0x04);
i2c_wr(0xD0,0x4,0x28);
i2c_wr(0xD0,0x5,0x02);
i2c_wr(0xD0,0x6,0x24);
os_sys_init(task1);
}
