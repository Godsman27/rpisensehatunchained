#ifndef RPISENSE_H
#define RPISENSE_H
#include <stdio.h>
#include <stdint.h>
int InitRpiSense(int bus);
int InitDisplay(int bus);
int InitHTS(int bus);
int InitLPSH(int bus);
int InitLSM(int bus);
int SetPixel(int x, int y, uint16_t color, int update);
int SetPattern(uint16_t* pattern, int size);
int ReadTemp (double* temp_out);
int ReadHumidity(double* hum_out);
int ReadPressure(double * press_out);
int ReadPtemp (double *temp_out); //read the temerature of the pressure sensor.
int ReadGyro(int* gyro_x, int* gyro_y, int* gyro_z);
int ReadAccel(int* accel_x, int* accel_y, int* accel_z);
int ReadMagnet(int* mag_x, int* mag_y, int *mag_z); //read the magnetic sensor
void Shutdown(void);

/*
int ReadJoystick(char* keysout); //read
*/
#endif

