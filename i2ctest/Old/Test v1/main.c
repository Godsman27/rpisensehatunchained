#include <unistd.h>                             //Needed for I2C port
#include <fcntl.h>                              //Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <stdio.h>
int openbus(char *filename)
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

int openslave(int addr, int file_i2c)
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

int readslave(int length, char* buffer, int file_i2c)	
{
	//----- READ BYTES -----
	int out =  read(file_i2c, buffer, length);
	if (out != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
	}
	else
	{
		printf("Date read: ");
		for(int i =0; i < length;i++)
		{
			printf("%x",(int)buffer[i]);
			
		}
		printf("\n");
	}
	return out;
}

int writeslave(int length, char* buffer, int file_i2c)
{	
	//----- WRITE BYTES -----
	
	int out = write(file_i2c, buffer, length);
	if(out != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
		return out;
	}
	return out;
}

int main(char* argv, int argc)
{
	int file_i2c;
	int length;
	unsigned char buffer[60] = {0};
	//----- OPEN THE I2C BUS -----
	char *filename = (char*)"/dev/i2c-1";
	file_i2c = openbus(filename);
	if(file_i2c <0)
	{
		return -1;
	}
/*
	int adrr = 0x5f;
	openslave(adrr, file_i2c);
	unsigned char out[2]= {0};
	unsigned char in[1] = {0x28};
	writeslave(1,in,file_i2c);
	readslave(1,out,file_i2c);
	printf("Low register (28h): %x\n",out[0]);
	in[0] = 0x29;
	writeslave(1,in,file_i2c);
	readslave(1,out,file_i2c);
	printf("High register(29h): %x\n",out[0]);
*/

	int addr = 0x46;
	openslave(addr,file_i2c);
	unsigned char in[] = {2,0,255,0};
	writeslave(4,in,file_i2c); 

}
/*
		self.i2cbus.write_byte_data(self.ctrl_address, x*24+y, color[0])
		self.i2cbus.write_byte_data(self.ctrl_address, x*24+y+8, color[1])
		self.i2cbus.write_byte_data(self.ctrl_address, x*24+y+16, color[2])
*/
