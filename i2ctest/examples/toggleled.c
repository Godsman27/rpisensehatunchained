#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sensehat.h>
#include <stdint.h>
#include <sys/time.h>
#define EVER ;;
#define Y 0xF800
#define B 0xAA00
#define O 0xFFFF
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
Y,Y,O,O,O,O,Y,Y,//
Y,O,Y,O,O,Y,O,Y,//
Y,O,O,Y,Y,O,O,Y,//
Y,O,O,Y,Y,O,O,Y,//
Y,O,Y,O,O,Y,O,Y,//
Y,Y,O,O,O,O,Y,Y,//
Y,Y,Y,Y,Y,Y,Y,Y//
};

uint16_t pat4[64] = 
{//
Y,Y,Y,Y,Y,Y,Y,Y,//
Y,O,O,Y,Y,O,O,Y,//
Y,O,Y,O,O,Y,O,Y,//
Y,Y,O,Y,O,O,Y,Y,//
Y,Y,O,O,Y,O,Y,Y,//
Y,O,Y,O,O,Y,O,Y,//
Y,O,O,Y,Y,O,O,Y,//
Y,Y,Y,Y,Y,Y,Y,Y//
};

int main ()
{	
	//----- OPEN THE I2C BUS -----
	InitDisplay(1);
	int r = InitHTS(1);
	double temp =0, hum = 0;
	printf("HTS returned: %i\n",r);
	for(EVER)
	{
		sleep(1);
		SetPattern(pat2,63);	
		sleep(1);
		SetPattern(pat1,63);
		//sleep(2);
		//SetPattern(pat3,63);
		//sleep(2);
		//SetPattern(pat4,63);
		ReadTemp(&temp);
		ReadHumidity(&hum);
		printf("temperature is: %f, Huminity = %f\n",temp,hum);
	}
}

