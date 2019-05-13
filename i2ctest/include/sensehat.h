#ifndef RPISENSE_H
#define RPISENSE_H
#include <unistd.h>                             //Needed for I2C port
#include <fcntl.h>                              //Needed for I2C port
#include <sys/ioctl.h>                  //Needed for I2C port
#include <linux/i2c-dev.h>              //Needed for I2C port
#include <stdio.h>
int openbus(char *filename);
int openslave(int addr, int file_i2c);
int readslave(int length, char* buffer, int file_i2c);
int writeslave(int length, char* buffer, int file_i2c);
#endif

