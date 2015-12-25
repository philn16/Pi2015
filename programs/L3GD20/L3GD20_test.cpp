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

int main(int argc, char** argv)
{
	// open Linux I2C device
	i2cOpen();

	i2cSetAddress(0x6a);

	// Register 0x0F should read 1101 0100
	
	// CTRL_REG1 (0x20)
	// { Data Rate [1:0] , Bandwidth Selection [1:0] , Power-Down Mode , Zen , Yen , Xen}
	// {XX , XX , 1 , 1 , 1 , 1}
	// Data Rate: 2'd0 := 95 , 2'd1 := 190 , 2'd2 := 380 , 2'd3 := 760 Hz
	// Band Width: ??? Affects "cuttoff"
	
	// Read address 0x28 : 0x2D
	// x = 0x29 << 8 | 0x28
	// y = 0x2B << 8 | 0x2A
	// z = 0x2D << 8 | 0x2C
	
	// Temperature Register (0x26). 1 LSB / deg
	
	// NOT NEEDED
	// FIFO_CTRL_REG (0x2E)
	// { FIFO MODE[2:0] , Watter Mark[4:0] } 
	// FIFO: 3'd0 := Bypass Mode , 3'd1 := FIFO mode , 3'd2 := stream mode , 3'd3 := Stream to FIFO ,3'd4 := Bypass to Stream ,
	
	// close Linux I2C device
	i2cClose();
	printf("Program is finisihed\n");
	return 0;
}