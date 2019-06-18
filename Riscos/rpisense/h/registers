#ifndef HARDWARE_H
#define HARDWARE_H

#define CONTIRW		0x80 // add this together with register adress to read (n) following registers after the first adressed register
				     //	example: read(i2c_file ,0x28 + CONTIRW, buffer, n) will result in reading n bytes starting from register 0x28. 

/*
	ATTINY- MICROCONTROLLER
*/
#define ATTINY			0x46
#define LED0			0x00
#define JOYSTICK		0xF2 // to read the status of the gnotsknots

/*
	LSM9DS1 GYROSCOPE AND ACCELEROMETER
*/
#define LSM9DS1			0x6A
	// output registers gyroscope
#define GYRO_OUT_X_L		0x18	
#define GYRO_OUT_X_H		0x19
#define GYRO_OUT_Y_L		0x1A
#define GYRO_OUT_Y_H		0x1B
#define GYRO_OUT_Z_L		0x1C
#define GYRO_OUT_Z_H		0x1D
	// output registers accelerometer
#define ACCEL_OUT_X_L		0x28
#define ACCEL_OUT_X_H		0x29
#define ACCEL_OUT_Y_L		0x2A
#define ACCEL_OUT_Y_H		0x2B
#define ACCEL_OUT_Z_L		0x2C
#define ACCEL_OUT_Z_H		0x2D

	//CTRL registers for gyro and accelerometer
#define GYROACC_FIFO_CTRL	0x2E
#define LSMGA_CTRL_1_G		0x10
#define LSMGA_CTRL_2_G		0x11
#define LSMGA_CTRL_3_G		0x12

#define LSMGA_CTRL_4		0x1E
#define LSMGA_CTRL_5_XL		0x1F
#define LSMGA_CTRL_6_XL		0x20
#define LSMGA_CTRL_7_XL		0x21
#define LSMGA_CTRL_8		0x22
#define LSMGA_CTRL_9		0x23
#define LSMGA_CTRL_10		0x24

/*	
	LSM9DS1 MAGNETOMETER
*/
#define LSM9DS1M		0x1C
	// output registers magnetometer
#define MAG_OUT_X_L		0x28
#define MAG_OUT_X_H		0x29
#define MAG_OUT_Y_L		0x2A
#define MAG_OUT_Y_H		0x2B
#define MAG_OUT_Z_L		0x2C
#define MAG_OUT_Z_H		0x2D

	// ctrl rtegisters
#define MAG_CTRL_1		0x20
#define MAG_CTRL_2		0x21
#define MAG_CTRL_3		0x22
#define MAG_CTRL_4		0x23
#define MAG_CTRL_5		0x24
/*
	LPSH25H druksensor
*/
#define LPSH25H			0x5c
	// reference registers
#define PRESS_REF_XL		0x08
#define PRESS_REF_L		0x09
#define PRESS_REF_H		0x0A
	// Output registers druksensor
#define PRESS_OUT_P_XL		0x28
#define PRESS_OUT_P_L		0x29
#define PRESS_OUT_P_H		0x2A
#define PRESS_OUT_T_L		0x2B
#define PRESS_OUT_T_H		0x2C
	// control registers druksensor
#define PRESS_CTRL_1		0x20
#define PRESS_CTRL_2		0x21
#define PRESS_CTRL_3		0x22
#define PRESS_CTRL_4		0x23

	//FIFO control registers druksensor
#define PRESS_FIFO_CTRL		0x2E
#define PRESS_FIFO_STATUS	0x2F

/*
	HTS221 HUMINITY TEMPARATURE SENSOR
*/
#define HTS221			0x5f
	// calibration registers	
#define HT_H0_rH_x2		0x30
#define HT_H1_rH_x2		0x31
#define HT_T0_degC_x8		0x32
#define HT_T1_degC_x8		0x33
#define HT_T1T0MSB		0x35 // bit 7 to bit4 are reserved bit 3 and bit 2 are for T1 and bit 1 and 0 are for T0
#define HT_HO_TO_OUT_L		0x36
#define HT_HO_TO_OUT_H		0x37
#define HT_H1_T0_OUT_L		0x3A
#define HT_H1_T0_OUT_H		0x3B	
#define HT_T0_OUT_L		0x3C
#define HT_T0_OUT_H		0x3D
#define HT_T1_OUT_L		0x3E
#define HT_T1_OUT_H		0x3F
	// output registers huminity
#define HT_HUMI_OUT_L		0x28
#define HT_HUMI_OUT_H		0x29
	// output registers temperature
#define HT_TEMP_OUT_L		0x2A
#define HT_TEMP_OUT_H		0x2B
	// control registers HTS221

#define HT_AV_CONF		0x10
#define HT_CTRL_REG1		0x20	
#define HT_CTRL_REG2		0x21
#define HT_CTRL_REG3		0x22
#define HT_STATUS		0x27
#endif

