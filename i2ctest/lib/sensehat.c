#include <stdio.h>			//Needed for debugging purpuses
#include <string.h>			//Needed for memcpy functions
#include <unistd.h>                     //Needed for I2C port
#include <fcntl.h>                      //Needed for I2C port
#include <sys/ioctl.h>                  //Needed for I2C port
#include <linux/i2c-dev.h>              //Needed for I2C port
#include "sensehat.h"			
#include "registers.h"			//register definitions for hardware of the rpi sensehat

static int OpenBus(char *filename);
static int OpenSlave(int addr, int file_i2c);
static int ReadSlave(int file_i2c, unsigned char regi, unsigned char* buffer, int length);
static int WriteSlave(int file_i2c, unsigned char regi, unsigned char* buffer, int length);

static unsigned char LEDmatrix[192] = {0}; 
static int file_joyled = -1; // led2472 via attiny
static int file_pressure = -1; //lps25h pressure sensor
static int file_humi=-1; // //hts221 temp/hum sensor
static int file_magnet = -1; // LSM9DS1 magnetometer
static int file_acc = -1; // LSM9DS1 gyro/accelerometer

// humidity/temp calibration values
static int H0_rH_x2, H1_rH_x2, T0_degC_x8;
static int T1_degC_x8, H0_T0_OUT;
static int H1_T0_OUT, T0_OUT, T1_OUT;

int Init(int bus)
{
	unsigned char buf[32] = {0}; //buffer for setting and reading settings of sensors
	char filename[32];
	sprintf(filename, "/dev/i2c-%d", bus);
	//led display
	file_joyled = OpenBus(filename);
	OpenSlave(ATTINY,file_joyled);
	//humi and temp sensor
	file_humi = OpenBus(filename);
	OpenSlave(HTS221,file_humi);
	//pressure sensor
	file_pressure = OpenBus(filename);
	OpenSlave(LPSH25H,file_pressure);
	//magnetometer
	file_magnet = OpenBus(filename);
	OpenSlave(LSM9DS1M,file_magnet);
	//gyro and accelerometer
	file_acc = OpenBus(filename);
	OpenSlave(LSM9DS1,file_acc);
	
	if(file_joyled <0|file_humi <0 | file_acc <0 | file_pressure <0 | file_magnet <0 )
	{
		return -1;
	}
	
	// activate huminity sensor.
	ReadSlave(file_humi,HT_AV_CONF,buf,1); // read the AV_CONF of the hum sensor so we can adjus tthe settings
	unsigned char AV_CONF_R = buf[0];
	AV_CONF_R &= 0xC0; // keep reserved bits
	AV_CONF_R |= 0x3F; // set AVGT to 256 samples and AVGH to 512 samples
	WriteSlave(file_humi,HT_AV_CONF,&AV_CONF_R,1);	
	
	
	return 1;
}
static int OpenBus(char *filename)
{
        int bus; 
        if ((bus = open(filename, O_RDWR)) < 0)
        {
                //ERROR HANDLING: you can check errno to see what went wrong
                printf("Failed to open the i2c bus");
                return -1;
        }
        else
        {
                return bus;
        }
}

static int OpenSlave(int addr, int file_i2c)
{
        int out = ioctl(file_i2c,I2C_SLAVE, addr);
        if (out < 0)
        {
                printf("Failed to acquire bus access and/or talk to slave.\n");
                //ERROR HANDLING; you can check errno to see what went wrong
                return out;
        }
        return out;
}

static int ReadSlave(int file_i2c, unsigned char regi, unsigned char* buffer,int length)
{	
	if(buffer =NULL)
	{
		return -1;
	}

	int rc = write(file_i2c, &regi, 1); // write the register adress that we want to read first.
	if(rc == 1)
	{
		rc =  read(file_i2c, buffer, length);
	}
        //----- READ BYTES -----
        return rc;
}

static int WriteSlave(int file_i2c, unsigned char regi ,unsigned char* buffer,int length)
{
        //----- WRITE BYTES -----
	unsigned char buf[512];
	int rc;
	if(length> 510 || length < 1 || buffer == NULL) // buf[0] place in the array is reserved for the register adress so only 511 chars can be send at the most. 
	{
		return -1;
	}
	buf[0] = regi; // first send the register to write to.
	memcpy(&buf[1],buffer,length);
        int out = write(file_i2c, buf, length+1);
        return out-1; //remove one from the written bytes cause of the adress that was added to the start of the data.
}

int SetPixel(int x, int y, uint16_t color, int bUpdate)
{
	int i;
	if (x >= 0 && x < 8 && y >= 0 && y < 8)
	{
		i = (y*24)+x; // offset into array
		LEDmatrix[i] = (uint8_t)((color>>10) & 0x3e); // Red
		LEDmatrix[i+8] = (uint8_t)((color>>5) & 0x3f); // Green
		LEDmatrix[i+16] = (uint8_t)((color<<1) & 0x3e); // Blue
		if (bUpdate)
		{
			WriteSlave(file_joyled, 0 ,LEDmatrix, 192); // have to send the whole array at once,starting from register 0
		}
		return 1;
	}
	return 0;
}

int SetPattern(uint16_t* pattern, int size)
{
	if(size != 63 && pattern != NULL)
	{
		return -1;
	}
	int x,y,i;
	
	for(y =0;y < 8; y++)
	{		
		for(x=0;x<8;x++)
		{
			i = (y*8) + x;
			SetPixel(x,y,pattern[i],0);
		}		
	}
	SetPixel(0,0,pattern[0],1);
}
