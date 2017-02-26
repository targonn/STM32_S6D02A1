#include "stm32f1xx_hal.h"

#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160


#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//»??«0 3165 00110 001011 00101
#define GRAY1   0x8410      	//»??«1      00000 000000 00000
#define GRAY2   0x4208      	//»??«2  1111111111011111


void S6D02A1_SendCmd(uint8_t data);

void S6D02A1_SendData(uint8_t data);

void S6D02A1_SendData_16bit(uint16_t data);

void S6D02A1_CS(uint8_t data);
	
void S6D02A1_RST(uint8_t data);
	
void S6D02A1_DC(uint8_t data);

void S6D02A1_Init(void);

void S6D02A1_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);

void S6D02A1_SetXY(uint16_t x,uint16_t y);

void S6D02A1_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);

void S6D02A1_Clear(uint16_t Color);

uint16_t S6D02A1_color565(uint8_t r, uint8_t g, uint8_t b);
