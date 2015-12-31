#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>

#include <sys/stat.h>
#include <sys/types.h>
#include <linux/i2c-dev.h>

#include "philn_i2c.cpp"
#include "philn_adxl.cpp"


using std::cout;
using std::cin;
using std::endl;

int main(int argc, char** argv)
{
	// open Linux I2C device
	i2cOpen();

	i2cSetAddress(0x53);

	cout << "initializing. Press any key to continue" << endl;
std::cin.ignore();
	ADXL345_accelInit();

	for(int i=0; i < 5555; i++){
		int x,y,z;
		x=-2;y=-2;z=-2;
		accelGetData(x,y,z);
	
		printf("X: %4d Y: %4d Z: %4d\n", x,y,z);
		printf("X: %4x Y: %4x Z: %4x\n\n", x & 0xffff,y & 0xffff,z & 0xffff);
		cout << std::flush;
		usleep(500000);
	}
	
	// close Linux I2C device
	i2cClose();
	printf("Program is finisihed\n");
	return 0;
}

