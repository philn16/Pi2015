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

void MultiByteWrite(const uint8_t RegisterAddress, const uint8_t* values,const int AdditionalAmmount)	
{
	uint8_t* data = new uint8_t[AdditionalAmmount + 2];
	data[0] = RegisterAddress;
	for(int i=0; i< AdditionalAmmount; i++)
	data[i+1] = values[i];
	if (write(g_i2cFile, data, AdditionalAmmount + 1) != AdditionalAmmount + 1)
	perror("Write Failed SingleBitWrite");
	delete [] data;
}

void MultiByteRead(const uint8_t RegisterAddress, const uint8_t* ReadInData,const int ammount)	{
	
	MultiByteWrite(RegisterAddress, (uint8_t*)0,0);
	if(read(g_i2cFile, ReadInData, ammount) != ammount)	
	perror("Read Failed MultiByteRead");
}