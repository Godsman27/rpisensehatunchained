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
	unsigned char stop = 0;
	InitDisplay(1);
	int r = InitHTS(1);
	double temp =0, hum = 0;
	printf("HTS init returned: %i\n",r);
	r = InitLPSH(1);
	printf("LPSH init returned: %i\n",r);
	double pressure=0,ptemp =0;
	int mx=0,my=0,mz=0,gx=0,gy=0,gz=0,ax=0,ay=0,az=0;
	r = InitLSM(1);
	printf("LSM init returned: %i\n",r);
	while(stop == 0)
	{
		sleep(1);
		SetPattern(pat2,63);
		ReadTemp(&temp);
		ReadHumidity(&hum);
		ReadPressure(&pressure);
		ReadPtemp(&ptemp);
		ReadGyro(&gx,&gy,&gz);
		ReadMagnet(&mx,&my,&mz);
		ReadAccel(&ax,&ay,&az);
		stop = ReadJoystick();
		printf("Key = %02x\n", stop);
		printf("Temperature is: %6.6f, Huminity = %6.6f\n",temp,hum);
		printf("Pressure is: %6.6f, Pressure temperature = %6.6f\n",pressure,ptemp);
		printf("Gyros_X = %6.1i, Gyros_Y = %6.1i, Gyros_Z = %6.1i\n",gx,gy,gz);
		printf("Accel_X = %6.1i, Accel_Y = %6.1i, Accel_Z = %6.1i\n",ax,ay,az);
		printf("Magne_X = %6.1i, Magne_Y = %6.1i, Magne_Z = %6.1i\n",mx,my,mz);
		sleep(1);
		SetPattern(pat1,63);
}

=======
	}		
}
