#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>


static unsigned char LEDArray[193];

int main() {
    char file[50] = "/dev/i2c-1";
    int file_led = 0;

    memset(LEDArray, 0x1F, sizeof(LEDArray));

    file_led = open(file, O_RDWR);

    ioctl(file_led, I2C_SLAVE, 0x46);

    LEDArray[0] = 0;    

    write(file_led, LEDArray, sizeof(LEDArray));

    return 0;
}
