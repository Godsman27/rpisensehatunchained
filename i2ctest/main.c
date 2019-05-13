#include <stdio.h>
#include "include/sensehat.h"

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
	unsigned char in[] = {0,0,0,0};
	writeslave(4,in,file_i2c); 

}
/*
		self.i2cbus.write_byte_data(self.ctrl_address, x*24+y, color[0])
		self.i2cbus.write_byte_data(self.ctrl_address, x*24+y+8, color[1])
		self.i2cbus.write_byte_data(self.ctrl_address, x*24+y+16, color[2])
*/
