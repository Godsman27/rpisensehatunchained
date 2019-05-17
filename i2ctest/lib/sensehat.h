#ifndef RPISENSE_H
#define RPISENSE_H
#include <stdio.h>
#include <stdint.h>
int Init(int bus);
int SetPixel(int x, int y, uint16_t color, int update);
int SetPattern(uint16_t* pattern, int size);
/*
int ReadPressure(int* pres_out, int* ptemp_out);
int ReadTemp (int* temp_out, int* hum_out);
int ReadMagnetsensor(int* xout, int* yout, int *zout);
int ReadJoystick(char* keysout);
void Shutdown();
*/
#endif

