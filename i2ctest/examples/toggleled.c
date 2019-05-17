#include <stdio.h>
#include <string.h>
#include <sensehat.h>
#include <stdint.h>
#define EVER ;;

// The LED Array is handled by a dedicated microcontroller
// It must be updated in a single shot by writing
// 192 bytes starting at register 0
// The memory is laid out in each row like this:
// RRRRRRRRGGGGGGGGBBBBBBBB
// Each byte can have 64 unique levels (0-63)
//
#define Y 0xEFE0
#define B 0x0FFE

uint16_t pat1[64] = 
{//
Y,Y,Y,Y,Y,Y,Y,Y,//
B,B,B,B,B,B,B,B,//
Y,Y,Y,Y,Y,Y,Y,Y,//
B,B,B,B,B,B,B,B,//
Y,Y,Y,Y,Y,Y,Y,Y,//
B,B,B,B,B,B,B,B,//
Y,Y,Y,Y,Y,Y,Y,Y,//
B,B,B,B,B,B,B,B};
uint16_t pat2[64] = 
{//
Y,B,Y,B,Y,B,Y,B,//
B,Y,B,Y,B,Y,B,Y,//
Y,B,Y,B,Y,B,Y,B,//
B,Y,B,Y,B,Y,B,Y,//
Y,B,Y,B,Y,B,Y,B,//
B,Y,B,Y,B,Y,B,Y,//
Y,B,Y,B,Y,B,Y,B,//
B,Y,B,Y,B,Y,B,Y//
};

int main ()
{	
	//----- OPEN THE I2C BUS -----
	Init(1);
	SetPattern(pat2,63);	

}

