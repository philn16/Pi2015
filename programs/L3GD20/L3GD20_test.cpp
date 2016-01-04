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
#include "L3GD20.cpp"
using std::cout; using std::endl;
int main(int argc, char** argv)
{
	// open Linux I2C device
	i2cOpen();

	i2cSetAddress(0x6b);

	{	uint8_t WhoAmI = SingleByteRead(0x0f);
		if ( WhoAmI != 0xd4){
			printf("Incorrect Who am I value is 0x%02x Value should be 0xd4.",WhoAmI); cout << endl;}}
	
	std::cout << "Press any Key to Continue (initialiation)" << std::endl;
	std::cin.ignore();
	L3GD20_Initialize();

	
	std::cout << "Press any Key to Continue" << std::endl;
	std::cin.ignore();
	
	for(int i=0;i<555;i++){
	#define GetTemperature	0
	#define GetGyro			1
		int x,y,z,temperature;
		#if GetGyro
		L3GD20_GetGyroData(x,y,z);
		#endif
		#if GetTemperature
		temperature=L3GD20_GetTemperature();
#endif
#if GetGyro
		printf("Gyro data (angular velocity)\n");
		printf("X: %6d Y: %6d Z: %6d\n",x,y,z);
		printf("X: 0x%04x Y: 0x%04x Z: 0x%04x\n",x& 0xffff,y& 0xffff,z& 0xffff );
#endif
#if GetTemperature
		printf("Temperature\n");
		printf("%6d , 0x%02x\n", temperature , temperature & 0xFF);
#endif
		std::cout << "\nPress any Key to Continue" << std::endl;
		std::cin.ignore();
		usleep(100000); // 1/10 s
		
	}
	// close Linux I2C device
	i2cClose();
	printf("Program is finisihed\n");
	return 0;
}

