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
void Shutdown(void);
/*
int ReadPressure(int* pres_out);
int ReadPtemp (int( temp_out) //read the temerature of the pressure sensor.
int ReadGyro(int* gyro_x, int* gyro_y, int* , gyro_z);
int ReadAccel(int* accel_x, int* accel_y, int* accel_z);
int ReadMagnetsensor(int* xout, int* yout, int *zout); //red the magnetic sensor
int ReadJoystick(char* keysout); //read

*/
#endif

