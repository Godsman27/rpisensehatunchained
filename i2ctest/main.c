#include<stdio.h>
#include <string.h>
#include "include/sensehat.h"
#include <stdint.h>
#define EVER ;;
typedef struct color
{
	uint8_t R;
	uint8_t G;
	uint8_t B;	
}color_t;

// The LED Array is handled by a dedicated microcontroller
// It must be updated in a single shot by writing
// 192 bytes starting at register 0
// The memory is laid out in each row like this:
// RRRRRRRRGGGGGGGGBBBBBBBB
// Each byte can have 64 unique levels (0-63)
// 
static unsigned char LEDArray[192] = {0};
static int file_i2c;
int shSetPixel(int x, int y, color_t color, int bUpdate)
{
	int i;
	if (x >= 0 && x < 8 && y >= 0 && y < 8)
	{
		i = (y*24)+x; // offset into array
		LEDArray[i] = color.R & 0x3e; // Red
		LEDArray[i+8] = color.G & 0x3f; // Green
		LEDArray[i+16] = color.B & 0x3e; // Blue
		if (bUpdate)
		{
		//	writeslave(1,buffer,file_i2c);
			writeslave(192, LEDArray, file_i2c); // have to send the whole array at once
		}
		return 1;
	}
	return 0;
} /* shSetPixel() */


int main ()
{	
	//----- OPEN THE I2C BUS -----
	char *filename = (char*)"/dev/i2c-1";
	file_i2c = openbus(filename);
	if(file_i2c <0)
	{
		return -1;
	}
	color_t setcolor = {255,0,0};	
	color_t empty = {0,0,0};
	int addr = 0x46;
	openslave(addr,file_i2c);
	shSetPixel(1,0,empty,1);
	shSetPixel(1,1,empty,1);
	shSetPixel(1,2,empty,1);
	shSetPixel(1,3,empty,1);
	shSetPixel(1,4,empty,1);
	shSetPixel(1,5,empty,1);
	shSetPixel(1,6,empty,1);
	shSetPixel(1,7,empty,1);
		
}

