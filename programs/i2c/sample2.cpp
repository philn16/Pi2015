#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>

int address;

// I2C Linux device handle
int g_i2cFile;

// open the Linux device
void i2cOpen(){
	g_i2cFile = open("/dev/i2c-1", O_RDWR);
	if (g_i2cFile < 0) {
		perror("i2cOpen");
		exit(1);
	}
}

// close the Linux device
void i2cClose(){
	close(g_i2cFile);
}

// set the I2C slave address for all subsequent I2C device transfers
void i2cSetAddress(int address){
	if (ioctl(g_i2cFile, I2C_SLAVE, address) < 0) {
		perror("i2cSetAddress");
		exit(1);
	}
}

void writeShit(uint8_t reg, uint16_t value)
{
	uint8_t data[3];
	data[0] = reg;
	data[1] = value & 0xff;
	data[2] = (value >> 8) & 0xff;
	if (write(g_i2cFile, data, 3) != 3) {
		perror("writeShit!");
	}
}

#define register 0xff
#define data 0x3333

int main(int argc, char** argv)
{
printf("This is a test of the emergency system!\n");
printf("1\n");
	// open Linux I2C device
	i2cOpen();
address = 0x33;
	for(int i=0; i < 55;i++){
std::cout << "input address: " << std::endl;
	std::cin >> address;
	
	printf("2\n");
	// set address of the PCA9555
	i2cSetAddress(address);

		printf("%d \n",i);
		writeShit(register, data);
				// wait 1000 ms for next animation step
		usleep(1000000);
}
	// close Linux I2C device
	i2cClose();
printf("Program is finisihed\n");
	return 0;
}
