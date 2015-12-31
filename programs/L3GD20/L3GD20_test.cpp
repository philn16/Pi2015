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
	cout << "Incorrect Who am I value is "; printf("%2x",WhoAmI); cout << " Value should be 0xd4." << endl;}
	}
	
		std::cout << "Press any Key to Continue (initialiation)" << std::endl;
std::cin.ignore();
L3GD20_Initialize();

	
	std::cout << "Press any Key to Continue" << std::endl;
std::cin.ignore();
	
	for(int i=0;i<555;i++){
	int x,y,z,temperature;
	L3GD20_GetGyroData(x,y,z);
	temperature=L3GD20_GetTemperature() & 0xffff;

printf("Gyro data (angular velocity)\n");
		printf("X: %6d Y: %6d Z: %6d\n",x,y,z);
		printf("X: %6x Y: %6x Z: %6x\n",x& 0xffff,y& 0xffff,z& 0xffff );
cout << '\n';
printf("Temperature\n");
printf("%6d , 0x%6x", temperature , temperature);
		cout << endl;
std::cout << "Press any Key to Continue" << std::endl;
std::cin.ignore();
		usleep(100000); // 1/10 s
	
	}
	// close Linux I2C device
	i2cClose();
	printf("Program is finisihed\n");
	return 0;
}

