#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <poll.h>
#include <errno.h>

const char *filename = "/dev/i2c-1";
int DEBUG = 0;
int ADDRESS = 0x1c;
struct pollfd pfd;
int open_file(const char *filename)
{
    int fd;

    if ((fd = open(filename, O_RDWR)) == -1)
        printf("open_file | open");
    return fd;
}

int main(int argc, const char **argv)
{
   int file = open_file(filename);
    if (ioctl(file, I2C_SLAVE, ADDRESS) == -1)
	{
	int8_t buff[2];
	unsigned char * c = "18";	
	write(file,c, 1);
	read(file, buff, 2);
	int number = buff[1] | buff[0] << 8;
	printf("pitch = %i",number);
	}
    return EXIT_SUCCESS;
}
