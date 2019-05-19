#include <stdio.h>
#include <string.h>
#include <sensehat.h>
#include <stdint.h>
#include <sys/time.h>
#define EVER ;;
#define Y 0xF800
#define B 0xAA00
#define O 0x0000
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

uint16_t pat3[64] = 
{//
Y,Y,Y,Y,Y,Y,Y,Y,//
Y,Y,O,O,O,O,O,Y,//
Y,O,Y,O,O,O,O,Y,//
Y,O,O,Y,O,O,O,Y,//
Y,O,O,O,Y,O,O,Y,//
Y,O,O,O,O,Y,O,Y,//
Y,O,O,O,O,O,Y,Y,//
Y,Y,Y,Y,Y,Y,Y,Y//
};
int main ()
{	
	//----- OPEN THE I2C BUS -----
	Init(1);
	for(EVER)
	{
		sleep(1);
		SetPattern(pat2,63);	
		sleep(1);
		SetPattern(pat1,63);
		sleep(1);
		SetPattern(pat3,63);
	}
}

