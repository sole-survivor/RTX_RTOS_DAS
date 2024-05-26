#include<lpc21xx.h>
#include"header.h"
#define SI ((I2CONSET>>3)&1)

void i2c_init (void)
{
	PINSEL0|=0x50;
	I2SCLH=75;
	I2SCLL=75;
	I2CONSET=(1<<6);
}

void i2c_wr (u8 sa,u8 mr,u8 data)
{
	I2CONSET=(1<<5); //STA=1
	I2CONCLR=(1<<3); //SI=0
	while (SI==0);
	I2CONCLR=(1<<5); //STA=0
	if (I2STAT!=0X08)
	{
		uart0_tx_string("wr_Error in start condition!\n");
		goto exit;
	}
	I2DAT=sa; //Send SA+W
	I2CONCLR=(1<<3); //SI=0
	while (SI==0);
	if (I2STAT!=0X18)
	{
		uart0_tx_string("wr_Error in SA!\n");
		goto exit;
	}
	I2DAT=mr; // Send MA
	I2CONCLR=(1<<3); //SI=0
	while (SI==0);
	if (I2STAT!=0X28)
	{
		uart0_tx_string("wr_Error in MA!\n");
		goto exit;
	}
	I2DAT=data; //Send DATA
	I2CONCLR=(1<<3); //SI=0
	while (SI==0);
	if (I2STAT!=0X28)
	{
		uart0_tx_string("wr_Error in DATA!\n");
		goto exit;
	}
	exit:
	I2CONSET=(1<<4); //STO=1
	I2CONCLR=(1<<3); //SI=0
}

u8 i2c_rd (u8 sa, u8 mr)
{
	u8 temp=0;
	I2CONSET=(1<<5); //STA=1
	I2CONCLR=(1<<3); //SI=0
	while (SI==0);
	I2CONCLR=(1<<5); //STA=0
	if(I2STAT!=0x08){
		uart0_tx_string("rd_Error in start condition!\r\n");
		goto exit;
	}
	I2DAT=sa; //Send SA+W
	I2CONCLR=(1<<3); //SI=0
	while (SI==0);
	if(I2STAT!=0x18){
		uart0_tx_string("rd_Error in SA+W!\r\n");
		goto exit;
	}
	I2DAT=mr; //Send MA
	I2CONCLR=(1<<3); //SI=0
	while (SI==0);
	if(I2STAT!=0x28){
		uart0_tx_string("rd_Error in mr1!\r\n");
		goto exit;
	}
	I2CONSET=(1<<5); //RESTART - STA=1
	I2CONCLR=(1<<3); //SI=0
	while (SI==0);
	I2CONCLR=(1<<5); //STA=0
	if (I2STAT!=0X10)
	{
		uart0_tx_string("rd_Error in Restart Condition!\r\n");
		goto exit;
	}
	I2DAT=sa|1; //Send SA+R
	I2CONCLR=(1<<3); //SI=0
	while (SI==0);
	if(I2STAT!=0x40){
		uart0_tx_string("rd_Error in SA+R!\r\n");
		goto exit;
	}
	I2CONCLR=(1<<3); //SI=0
	while (SI==0);
	temp=I2DAT;
	exit:
	I2CONSET=(1<<4); //STO=0
	I2CONCLR=(1<<3); //SI=0
	return temp;
}

