#include <stdio.h>
#include <string.h>
#include <unistd.h>                     //Needed for I2C port
#include <fcntl.h>                      //Needed for I2C port
#include <sys/ioctl.h>                  //Needed for I2C port
#include <linux/i2c-dev.h>              //Needed for I2C port
#include "sensehat.h"

static int OpenBus(char *filename);
static int OpenSlave(int addr, int file_i2c);
static int ReadSlave(int file_i2c, unsigned char regi, unsigned char* buffer, int length);
static int WriteSlave(int file_i2c, unsigned char regi, unsigned char* buffer, int length);

static unsigned char LEDArray[192] = {0};
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
	char filename[32];
	sprintf(filename, "/dev/i2c-%d", bus);
	file_joyled = OpenBus(filename);
	if(file_joyled <0)
	{
		return -1;
	}
	OpenSlave(0x46,file_joyled);
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
		LEDArray[i] = (uint8_t)((color>>10) & 0x3e); // Red
		LEDArray[i+8] = (uint8_t)((color>>5) & 0x3f); // Green
		LEDArray[i+16] = (uint8_t)((color<<1) & 0x3e); // Blue
		if (bUpdate)
		{
			WriteSlave(file_joyled, 0 ,LEDArray, 192); // have to send the whole array at once,starting from register 0
		}
		return 1;
	}
	return 0;
}
int SetPattern(uint16_t* pattern, int size)
{
	if(size != 63)
	{
		return -1;
	}
	int x,y,i;
	
	for(y =0;y < 8; y++)
	{		
		for(x=0;x<8;x++)
		{
			i = (y*8) + x;
			printf("%i\n",i);
			SetPixel(x,y,pattern[i],1);
		}		
	}
}
