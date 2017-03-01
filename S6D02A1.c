#include "stm32f1xx_hal.h"
#include "S6D02A1.h"
#include "Font.h"
#include <string.h>

extern SPI_HandleTypeDef hspi1;

#define FONT_H 16
#define FONT_W 8



void S6D02A1_SendCmd(uint8_t data){
	
	S6D02A1_CS(0);
	S6D02A1_DC(0);
	HAL_SPI_Transmit(&hspi1, &data, 1, 0x1);
	//HAL_Delay(1);
	S6D02A1_CS(1);

	
}

void S6D02A1_SendData(uint8_t data){
	S6D02A1_CS(0);
	S6D02A1_DC(1);
	HAL_SPI_Transmit(&hspi1, &data, 1, 0x1);
	//HAL_Delay(1);
	S6D02A1_CS(1);
}

void S6D02A1_SendData_16bit(uint16_t data){
	
	S6D02A1_CS(0);
	S6D02A1_DC(1);
	unsigned char hi = data >> 8;
	unsigned char lo = data & 0xFF;
	HAL_SPI_Transmit(&hspi1, &hi, 1, 0x1);
	HAL_SPI_Transmit(&hspi1, &lo, 1, 0x1);
	S6D02A1_CS(1);
	//HAL_Delay(1);
	
}

void S6D02A1_CS(uint8_t data){
	
	if(data==0)
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	
}

void S6D02A1_RST(uint8_t data){
	
	if(data==0)
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	
}

void S6D02A1_DC(uint8_t data){
	
	if(data==0)
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	
}

void S6D02A1_Init(){
	// Reset display
	
	S6D02A1_RST(1);
	HAL_Delay(1);
	S6D02A1_CS(0);
	S6D02A1_RST(0);
	
	HAL_Delay(1);
	
	S6D02A1_RST(1);
	
	HAL_Delay(1);
	
	S6D02A1_CS(1);
	S6D02A1_DC(0);
	
	//Init sequence
	

	
	S6D02A1_SendCmd(0xf0);
	S6D02A1_SendData(0x5a);
	S6D02A1_SendData(0x5a);

	S6D02A1_SendCmd(0xfc);
	S6D02A1_SendData(0x5a);
	S6D02A1_SendData(0x5a);


// Gamma Control
	S6D02A1_SendCmd(0x26);
	S6D02A1_SendData(0x01);

	S6D02A1_SendCmd(0xfa);
	S6D02A1_SendData(0x02);
	S6D02A1_SendData(0x1f);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x10);
	S6D02A1_SendData(0x22);
	S6D02A1_SendData(0x30);
	S6D02A1_SendData(0x38);
	S6D02A1_SendData(0x3A);
	S6D02A1_SendData(0x3A);
	S6D02A1_SendData(0x3A);
	S6D02A1_SendData(0x3A);
	S6D02A1_SendData(0x3A);
	S6D02A1_SendData(0x3d);
	S6D02A1_SendData(0x02);
	S6D02A1_SendData(0x01);

	S6D02A1_SendCmd(0xfb);
	S6D02A1_SendData(0x21);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x02);
	S6D02A1_SendData(0x04);
	S6D02A1_SendData(0x07);
	S6D02A1_SendData(0x0a);
	S6D02A1_SendData(0x0b);
	S6D02A1_SendData(0x0c);
	S6D02A1_SendData(0x0c);
	S6D02A1_SendData(0x16);
	S6D02A1_SendData(0x1e);
	S6D02A1_SendData(0x30);
	S6D02A1_SendData(0x3f);
	S6D02A1_SendData(0x01);
	S6D02A1_SendData(0x02);

	//////////////power setting sequence//////////
//	Analog  Test
	S6D02A1_SendCmd(0xfd);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x17);
	S6D02A1_SendData(0x10);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x01);
	S6D02A1_SendData(0x01);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x1f);
	S6D02A1_SendData(0x1f);

	S6D02A1_SendCmd(0xf4);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x3f);
	S6D02A1_SendData(0x3f);
	S6D02A1_SendData(0x07);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x3C);
	S6D02A1_SendData(0x36);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x3C);
	S6D02A1_SendData(0x36);
	S6D02A1_SendData(0x00);
	HAL_Delay(80);			   //????

	S6D02A1_SendCmd(0xf5);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x70);//39
	S6D02A1_SendData(0x66);//3a
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x6d);//38
	S6D02A1_SendData(0x66);//38
	S6D02A1_SendData(0x06);

	S6D02A1_SendCmd(0xf6);
	S6D02A1_SendData(0x02);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x3f);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x02);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x06);
	S6D02A1_SendData(0x01);
	S6D02A1_SendData(0x00);

	S6D02A1_SendCmd(0xf2);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x01);//04
	S6D02A1_SendData(0x03);
	S6D02A1_SendData(0x08);
	S6D02A1_SendData(0x08);
	S6D02A1_SendData(0x04);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x01);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x04);
	S6D02A1_SendData(0x08);
	S6D02A1_SendData(0x08);
	
	// gate control
	S6D02A1_SendCmd(0xf8);
	S6D02A1_SendData(0x11);//66
	
	// interface control
	S6D02A1_SendCmd(0xf7);
	S6D02A1_SendData(0xc8);
	S6D02A1_SendData(0x20);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);

	
	S6D02A1_SendCmd(0xf3);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);

	S6D02A1_SendCmd(0x11);
	HAL_Delay(50);

	S6D02A1_SendCmd(0xf3);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x01);
	HAL_Delay(50);
	S6D02A1_SendCmd(0xf3);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x03);
	HAL_Delay(50);
	S6D02A1_SendCmd(0xf3);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x07);
	HAL_Delay(50);
	S6D02A1_SendCmd(0xf3);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x0f);
	HAL_Delay(50);

	S6D02A1_SendCmd(0xf4);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x04);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x3f);
	S6D02A1_SendData(0x3f);
	S6D02A1_SendData(0x07);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x3C);
	S6D02A1_SendData(0x36);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x3C);
	S6D02A1_SendData(0x36);
	S6D02A1_SendData(0x00);
	HAL_Delay(50);

	S6D02A1_SendCmd(0xf3);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x1f);
	HAL_Delay(50);
	S6D02A1_SendCmd(0xf3);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x7f);
	HAL_Delay(50);

	S6D02A1_SendCmd(0xf3);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0xff);
	HAL_Delay(50);

	S6D02A1_SendCmd(0xfd);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x17);
	S6D02A1_SendData(0x10);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x01);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x16);
	S6D02A1_SendData(0x16);

	S6D02A1_SendCmd(0xf4);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x09);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x3f);
	S6D02A1_SendData(0x3f);
	S6D02A1_SendData(0x07);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x3C);
	S6D02A1_SendData(0x36);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(0x3C);
	S6D02A1_SendData(0x36);
	S6D02A1_SendData(0x00);

	/////////////initializing sequence/////////////

	S6D02A1_SendCmd( 0x36);   
	S6D02A1_SendData(0xC8); //!!!!!!!!!!!!!!!!!!!!!!!

	S6D02A1_SendCmd(0x35);
	S6D02A1_SendData(0x00);
	
	S6D02A1_SendCmd(0x3a);
	S6D02A1_SendData(0x05);


	/////////////////enable display/////////
	HAL_Delay(150);	
	S6D02A1_SendCmd(0x29);
	S6D02A1_SendCmd(0x2c);
	
}


void S6D02A1_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)
{		
	S6D02A1_SendCmd(0x2a);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(x_start);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(x_end);

	S6D02A1_SendCmd(0x2b);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(y_start);
	S6D02A1_SendData(0x00);
	S6D02A1_SendData(y_end);

	S6D02A1_SendCmd(0x2c);

}

void S6D02A1_SetXY(uint16_t x,uint16_t y)
{
  	S6D02A1_SetRegion(x,y,x,y);
}

void S6D02A1_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	S6D02A1_SetRegion(x,y,x+1,y+1);
	S6D02A1_SendData_16bit(Data);

}   


void S6D02A1_Clear(uint16_t Color)               
{	
   unsigned int i,m;
   S6D02A1_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   S6D02A1_SendCmd(0x2C);
   for(i=0;i<128;i++)
    for(m=0;m<160;m++)
    {	
	  	S6D02A1_SendData_16bit(Color);
    }   
}

// convert 8bit separate to 16 bit color
uint16_t S6D02A1_color565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

// Fill rectangle with coordinates
void S6D02A1_FillRect(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t Color)               
{	
   unsigned int x,y;
   S6D02A1_SetRegion(x_start, y_start, x_end-1, y_end-1);
   S6D02A1_SendCmd(0x2C);
   for(x=x_start;x<x_end;x++)
    for(y=y_start;y<y_end;y++)
    {	
	  	S6D02A1_SendData_16bit(Color);
    }   
}

void S6D02A1_drawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg, uint8_t size){
	
	uint8_t chi;
	S6D02A1_SetRegion(x, y, x+FONT_W-1, y+FONT_H-1);
	for(uint8_t r=0;r<16;r++)
	{
		chi = asc16[(c-32)*16+r];
		for(uint8_t c=8;c>0;c--)
		{		
			if( (chi>>c)&0x01 )
				S6D02A1_SendData_16bit(color);
			else
				S6D02A1_SendData_16bit(bg);
		}
	}
			
	
}

void S6D02A1_drawText(uint16_t x, uint16_t y, char *string, uint16_t color, uint16_t bg, uint8_t size){
	
	uint8_t textLen = strlen(string); //get text length
	uint8_t offset;
	
	for(offset = 0; offset < textLen; offset++)	//flip throug characters
	{
			S6D02A1_drawChar(x+offset*FONT_W, y, string[offset], color, bg, size);
		
	}
	
		
	
	
}
