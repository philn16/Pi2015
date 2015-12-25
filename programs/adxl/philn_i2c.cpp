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
// Start , (SlaveAddress<<8) | Write (0), ACK , RegisterAddress , ACK , Data From Master , ACK , ... , Data From Master , ACK , Stop
	if (write(g_i2cFile, data, AdditionalAmmount + 1) != AdditionalAmmount + 1)
	perror("Write Failed MultiByteWrite");
	delete [] data;
}

void SingleByteWrite(const uint8_t RegisterAddress, const uint8_t value){
uint8_t data[2];
data[0]=RegisterAddress;
data[1]=value;
// Start , (SlaveAddress<<8) | Write (0), ACK , RegisterAddress , ACK , Data From Master, ACK , Stop
if (write(g_i2cFile, &data[0], 2) != 2);
	perror("Write Failed SingleByteWrite");
}

void MultiByteRead(const uint8_t RegisterAddress, uint8_t* ReadInData,const int ammount)	{
	for(int i=0; i < ammount; i++)
	ReadInData[i] = 0x2;
	//Start ,  (SlaveAddress<<8) | Write (0) , ACK , Register Address , ACK
	write(g_i2cFile, &RegisterAddress, 1);
// Start, (SlaveAddress<<8) |Read (1) , ACK , Data From Slave , ACK , ... , Data From Slave , ACK , NACK , STOP
	if(read(g_i2cFile, ReadInData, ammount) != ammount)	
	perror("Read Failed MultiByteRead");
}

