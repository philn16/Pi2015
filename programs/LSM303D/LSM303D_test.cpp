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
#include "LSM303D.cpp"

int main(int argc, char** argv)
{
	// open Linux I2C device
	i2cOpen();

	i2cSetAddress(0x1d);

	uint8_t byte = SingleByteRead(0x0f);
	// Register 0x0F should read 1101 0100
	if ( byte != (uint8_t)0x49){
	perror("Register 0x0F should read 0100 1001");
	printf("Value Read: 0x%2x\n\n",byte);
	}
std::cout << "Press any Key to Continue (setting values)" << std::endl;
std::cin.ignore();
	Initialize_LSM303D();
	
	for(int i=0; i < 5555; i++){
		int temperature , xa, ya , za , xm , ym , zm;
		Read_LSM303D_Accelerometer(xa,ya,za);
		Read_LSM303D_Magnetometer(xm,ym,zm);
		temperature = Read_LSM303D_Temperature();

		printf("Acceleration:\n");
		printf("X: %6d Y: %6d Z: %6d\n",xa,ya,za);
		printf("X: %6x Y: %6x Z: %6x\n",xa & 0xffff,ya & 0xffff,za & 0xffff);
		printf("Magnetometer\n");
		printf("X: %6d Y: %6d Z: %6d\n",xm,ym,zm);
		printf("X: %6x Y: %6x Z: %6x\n",xm & 0xffff,ym & 0xffff,zm & 0xffff);
		printf("Temperature\n");
		printf("%5d %5x\n",temperature,temperature & 0xffff);
		std::cout << std::flush;

	std::cout << "Press any Key to Continue" << std::endl;
std::cin.ignore();
		usleep(100000); // 1/10 s
	}
	
	// close Linux I2C device
	i2cClose();
	printf("Program is finisihed\n");
	return 0;
}

