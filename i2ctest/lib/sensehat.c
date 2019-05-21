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
	if(buffer == NULL)
	{
//		printf("empty buffer u fool\n");
		return -1;
	}

	int rc = write(file_i2c, &regi, 1); // write the register adress that we want to read first.
	//printf("write %i bytes from register %x\n",rc, regi);
	if(rc == 1)
	{
		rc =  read(file_i2c, buffer, length);
		//printf("Read %i bytes from register ox%x\n",rc,regi);
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

int InitRpiSense(int bus)
{
	int rt = InitDisplay(bus);
	rt = InitHTS(bus);
	rt = InitLPSH(bus);
	rt = InitLSM(bus);
	return rt;
}

int InitDisplay(int bus)
{
	unsigned char buf[32] = {0}; //buffer for setting and reading settings of sensors
	char filename[32];
	sprintf(filename, "/dev/i2c-%d", bus);
	//led display
	file_joyled = OpenBus(filename);
	OpenSlave(ATTINY,file_joyled);


	
	if(file_joyled <0)
	{
		return -1;
	}		
	return 1;
}
int InitHTS(int bus)
{	
	unsigned char buf[32] = {0}; //buffer for setting and reading settings of sensors
	char filename[32];
	int rc =0;
	sprintf(filename, "/dev/i2c-%d", bus);
	file_humi = OpenBus(filename);
	OpenSlave(HTS221,file_humi);
	if(file_humi <0)
	{
		return -1;
	}
	// activate huminity sensor.
	rc = ReadSlave(file_humi,HT_AV_CONF,buf,1); // read the AV_CONF of the hum sensor so we can adjust the settings
	//printf("Recieved bytes from AV_CONF_READ: %i\n",rc);
	if(rc == 1)
	{
		unsigned char AV_CONF_R = buf[0];
		AV_CONF_R &= 0xC0; // keep reserved bits
		AV_CONF_R |= 0x38; //
		WriteSlave(file_humi,HT_AV_CONF,&AV_CONF_R,1);
	}
	else
	{
		return -2;
	}
	buf[0] =0x0; // clear the used buffer place to be sure that its empty.
	//read control registers all at once.
	rc = ReadSlave(file_humi,HT_CTRL_REG1+CONTIRW,buf,3); //read control register 1 and 2.
	if(rc==3)
	{
		unsigned char CTRL_REG1_R = buf[0];
		CTRL_REG1_R &= 0x78; // keep the reserved bits that must stay the same
		CTRL_REG1_R |= 0x87; // power-on sensor, continues conversion and set output rate to 7 Hz	
		unsigned char CTRL_REG2_R = buf[1];
		CTRL_REG2_R &= 0x7C; // reload calibration values, just incase something went wrong above.
		//write the changed registers back to sensor.
		buf[0] = CTRL_REG1_R;
		buf[1] = CTRL_REG2_R;
		WriteSlave(file_humi,HT_CTRL_REG1+CONTIRW,buf,3);
	}
	else
	{
		return -3;
	}
	//Now to calibrate the sensor
	// read all calibration values in one go. 
	rc = ReadSlave(file_humi,HT_H0_rH_x2+CONTIRW, buf, 16); // buf[4], buf[8], buf[9] are reserved registers and containt no calibration values.
	if(rc == 16) 
	
	{
		H0_rH_x2 = buf[0];
		//printf("H0_rH_2x = 0x%x\n",H0_rH_x2);
		H1_rH_x2 = buf[1];

		//printf("H1_rH_2x = 0x%x\n",H1_rH_x2);
		T0_degC_x8 = buf[2];
		//printf("T0_degC_8x = 0x%x\n",T0_degC_x8);
		T1_degC_x8 = buf[3];
		//printf("T1_degc_8x = 0x%x\n",T1_degC_x8);
		
		T0_degC_x8 |= ((buf[5] & 0x3) << 8); // 2 msb bits
		//printf("T0_degC_8x = 0x%x\n",T0_degC_x8);
		T1_degC_x8 |= ((buf[5] & 0xc) << 6); // 2 msb bits rest of the bits are reserved and shoudl not be used.
		//printf("T1_degC_8x = 0x%x\n",T1_degC_x8);
		H0_T0_OUT = buf[6] | (buf[7] << 8);
		//printf("H0_T0_OUT = 0x%x\n",H0_T0_OUT);
		H1_T0_OUT = buf[10] | (buf[11] << 8);
		//printf("H1_T0_OUT = 0x%x\n",H1_T0_OUT);
		T0_OUT = buf[12] | (buf[13] << 8);
		T1_OUT = buf[14] | (buf[15] << 8);
		//printf("T0_OUT = 0x%x\n",T0_OUT);
		//printf("T1_OUT = 0x%x\n",T1_OUT);
	}
	else
	{
		return -4;
	}
	if (H0_T0_OUT > 32767) H0_T0_OUT -= 65536; // check if value is signed or not if so adjust it.
	if (H1_T0_OUT > 32767) H1_T0_OUT -= 65536; 
	if (T0_OUT > 32767) T0_OUT -= 65536;
	if (T1_OUT > 32767) T1_OUT -= 65536;
	return 1;
}


int InitLPSH(int bus)
{
	char filename[32];
	unsigned char buf[4] = {0};
	buf[0] = 0xC4; // Turn on and set 25Hz update, wait with update till LSB and MSB are read form registers.
	buf[1] = 0x50; // Activate FIFO registers and use MEAN_MODE_DEC 
	
	buf[2] = 0xDF; // Set MEAN_MODE for the FIFO registers and set sample rate to 32.	
	
	sprintf(filename, "/dev/i2c-%d", bus);
	//pressure sensor
	file_pressure = OpenBus(filename);
	OpenSlave(LPSH25H,file_pressure);
	if(file_pressure <0)
	{
		return -1;
	}
	
	WriteSlave(file_pressure, PRESS_CTRL_1 + CONTIRW , buf, 2); //Write to ctrl register 1 and 2.
	WriteSlave(file_pressure, PRESS_FIFO_CTRL, &buf[2],1); // write the fifo register.
 	return 1;
}

int InitLSM(int bus)
{
	unsigned char buf[32] = {0}; //buffer for setting and reading settings of the sensor
	char filename[32];
	sprintf(filename, "/dev/i2c-%d", bus);
	//magnetometer
	file_magnet = OpenBus(filename);
	OpenSlave(LSM9DS1M,file_magnet);
	//gyro and accelerometer
	file_acc = OpenBus(filename);
	OpenSlave(LSM9DS1,file_acc);
	if(file_magnet < 0 | file_acc < 0)
	{
		return -1;
	}
	// Init magnetometer
	buf[0] = 0x48; // output data rate/power mode
	buf[1] = 0x00; // default scale
	buf[2] = 0x00; // continuous conversion
	buf[3] = 0x08; // high performance mode
	WriteSlave(file_magnet, 0x20+0x80, buf, 4);

	// Init accelerometer	
	buf[0] = 0x60; // 119hz accel
	WriteSlave(file_acc, 0x20, buf, 1);
	buf[0] = 0x38; // enable gyro on all axes
	WriteSlave(file_acc, 0x1e, buf, 1);
        buf[0] = 0x28; // data rate + full scale + bw selection
        WriteSlave(file_acc, 0x10, buf, 1); // gyro ctrl_reg1

	return 1;
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
int ReadTemp(double *temp_out)
{
	unsigned char buf[2];
	int rc;
	int T_out;
	double T0_degC, T1_degC;
	double tmp;
	 //read both output registrs for the temperature;
	rc = ReadSlave(file_humi, HT_TEMP_OUT_L + CONTIRW, buf, 2);
	if (rc == 2)
	{
		T_out = buf[0] + (buf[1] << 8); //create the 10 bit output value
		if (T_out > 32767) T_out -= 65536; // check if value must be signed or not.
		T0_degC = T0_degC_x8 / 8.0; // T0/T1_deg_C_x8 is calibation value that need to be devided by 8 cause the original value is a multiplied by 8.
		//printf("T0_degC = %i\n",T0_degC);
		T1_degC = T1_degC_x8 / 8.0;
		//printf("T1_degC = %i\n",T1_degC); 
		//printf("t1 calculated\n");
		tmp = (T_out - T0_OUT) * (T1_degC - T0_degC);
		//printf("tmp = %i\n",tmp);
		*temp_out = tmp / (T1_OUT - T0_OUT) + T0_degC;

		//printf("temp_out =%i\n", *temp_out);
		return 1;
	}
	return 0; // not ready	
}

int ReadHumidity(double* hum_out)
{
	unsigned char buf[2];
	int rc;
	int H_T_out;
	double H0_rh, H1_rh;
	double tmp;
	if(file_humi!= -1 && hum_out != NULL)
	{
		rc = ReadSlave(file_humi,HT_HUMI_OUT_L, buf, 2);
		if (rc == 2)
		{
			H_T_out = buf[0] + (buf[1] << 8);
			if (H_T_out > 32767) 
			{
				H_T_out -=65536;
			}
			H0_rh = H0_rH_x2 / 2.0;
			H1_rh = H1_rH_x2 / 2.0;
			tmp = (H_T_out - H0_T0_OUT) * (H1_rh - H0_rh);
			*hum_out = tmp / (H1_T0_OUT - H0_T0_OUT) + H0_rh;
			return 1;
		}
	}
	return 0; // not ready
}
int ReadPressure(double * press_out)
{
	unsigned char buffer[5];
	int rc, P;
	if (file_pressure != -1 && press_out != NULL)
	{
		rc = ReadSlave(file_pressure, PRESS_OUT_P_XL + CONTIRW, buffer, 3); // Read the lowest part, middle part and highest part of the pressure output registers.
		if (rc == 3)
		{
			P = buffer[0] + (buffer[1]<<8) + (buffer[2]<<16); 
			*press_out = P / 4096.0; //hPa
		}
		return 1;	
	}
	return 0;
}
int ReadPtemp (double *temp_out)
{
	unsigned char buffer[3];
	int rc, T;
	//printf("Reading temp\n");

	if (file_pressure != -1 && temp_out != NULL)
	{
		rc = ReadSlave(file_pressure, PRESS_OUT_T_L+ CONTIRW, buffer, 2);
		//printf("Read %i bytes from pressure sensor\n",rc);
		if (rc == 2)
		{
			//printf("MSB = 0x%x, LSB = 0x%x\n",buffer[0],buffer[1]);
			T = buffer[0] + (buffer[1] << 8); //combine LSB and MSB
			if (T > 32767) T -= 65536; // twos compliment
			*temp_out = 42.5 + (T / 480.0); // 42.5 + T value/480
		}
		return 1;	
	}
	return 0;
}

int ReadAccel(int* accel_x, int* accel_y, int* accel_z)
{
	unsigned char buffer[8];
	int rc;

	rc = ReadSlave(file_acc, ACCEL_OUT_X_L+CONTIRW, buffer, 6);
	printf("RC read Accel is: %i\n",rc);
	if (rc == 6)
	{
		int x, y, z;

		x = buffer[0] + (buffer[1] << 8);
		y = buffer[2] + (buffer[3] << 8);
		z = buffer[4] + (buffer[5] << 8);
		// fix the signed values
		if (x > 32767) x -= 65536;
		if (y > 32767) y -= 65536;
		if (z > 32767) z -= 65536;
		*accel_x = x; *accel_y = y; *accel_z = z;
		return 1;
	}
	return 0;
}

int ReadGyro(int* gyro_x, int* gyro_y, int* gyro_z)
{
	unsigned char buffer[8];
	int rc;
	rc = ReadSlave(file_acc, GYRO_OUT_X_L+CONTIRW, buffer, 6);
	printf("RC read gyro is: %i\n",rc);
	if (rc == 6)
	{
		*gyro_x = buffer[0] + (buffer[1] << 8);
		*gyro_y = buffer[2] + (buffer[3] << 8);
		*gyro_z = buffer[4] + (buffer[5] << 8);
		return 1;
	}
	return 0;
}

int ReadMagnet(int* mag_x, int* mag_y, int *mag_z)
{
	unsigned char buffer[8];
	int rc;
	rc = ReadSlave(file_magnet,MAG_OUT_X_L + CONTIRW, buffer, 6);
	printf("RC read magnet is: %i\n",rc);
	if (rc == 6)
	{
		int x, y, z;
		x = buffer[0] + (buffer[1] << 8);
		y = buffer[2] + (buffer[3] << 8);
		z = buffer[4] + (buffer[5] << 8);
		// fix signed values
		if (x > 32767) x -= 65536;
		if (y > 32767) y -= 65536;
		if (z > 32767) z -= 65536;
		*mag_x = x; *mag_y = y; *mag_z = z;
		return 1;
	}
	return 0;
} /* shGetMagneto() */

//
// Returns the air pressure in hPa and temp in C * 10 (18.1 = 181)
//
// 1 = pressure successfully read
// 0 = failed to read pressure
//

void Shutdown(void)
{
	uint16_t ledbuf[64] = {0x0};
	SetPattern(ledbuf, 63);
	// Close all I2C file handles
	if (file_joyled != -1) close(file_joyled);
	if (file_humi != -1) close(file_humi);
	if (file_pressure != -1) close(file_pressure);
	if (file_acc != -1) close(file_acc);
	if (file_magnet != -1) close(file_magnet);
	file_joyled = file_humi = file_pressure = file_acc = file_magnet = -1;
	printf("Clean exit achieved\n");
}
