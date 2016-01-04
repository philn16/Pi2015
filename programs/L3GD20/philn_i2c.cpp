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

/* 
RegisterAddress[0] gets values[0]
RegisterAddress[1] gets values[1]
... 
*/
void MultiByteWrite(const uint8_t RegisterAddress, const uint8_t* values,const int BytesToWrite)	
{
#if 1
for (int i=0; i < BytesToWrite; i+=2){
#if 1
uint16_t writevalue = (values[i+1] << 8) | values[i];
#else // some serious stuff
uint16_t& writevalue = *(uint16_t*)&values[i];
#endif
i2c_smbus_write_word_data(g_i2cFile , i+RegisterAddress , writevalue);
}
if(BytesToWrite % 2 == 1)// signle byte writes remainder
i2c_smbus_write_byte(g_i2cFile , values[BytesToWrite-1]);
#else
	uint8_t* data = new uint8_t[BytesToWrite + 2];
	data[0] = RegisterAddress;
	for(int i=0; i< BytesToWrite; i++)
	data[i+1] = values[i];
	// Start , (SlaveAddress<<8) | Write (0), ACK , RegisterAddress , ACK , Data From Master , ACK , ... , Data From Master , ACK , Stop
	if (write(g_i2cFile, data, BytesToWrite + 1) != BytesToWrite + 1)
	perror("Write Failed MultiByteWrite");
	delete [] data;
	#endif
}

void SingleByteWrite(const uint8_t RegisterAddress, const uint8_t value){
	uint8_t data[2];
	data[0]=RegisterAddress;
	data[1]=value;
	// Start , (SlaveAddress<<8) | Write (0), ACK , RegisterAddress , ACK , Data From Master, ACK , Stop
	if (write(g_i2cFile, &data[0], 2) != 2)
	perror("Write Failed SingleByteWrite");
}



uint8_t SingleByteRead(const uint8_t RegisterAddress)	{
	return i2c_smbus_read_byte_data(g_i2cFile, RegisterAddress);
}


/*
ReadInData[0] gets Reg[RegisterAddress]
ReadInData[1] gets Reg[RegisterAddress+1]
...
Same as MultiByteRead, except usese single byte reads instead
*/
void MultiByteReadSingleBytes(const uint8_t RegisterAddress, uint8_t* ReadInData,const int ammount)	{
	for(int i=0; i < ammount;i++)
	ReadInData[i] = i2c_smbus_read_byte_data(g_i2cFile, RegisterAddress+i);//same as SingleByteRead(RegisterAddress+(uint8_t)i);
}

/*
ReadInData[0] gets Reg[RegisterAddress]
ReadInData[1] gets Reg[RegisterAddress+1]
...
*/
void MultiByteRead(const uint8_t RegisterAddress, uint8_t* ReadInData,const int ammount)	{
	for(int i=0; i < ammount ; i += 2)
	{
uint16_t stuff = i2c_smbus_read_word_data(g_i2cFile, RegisterAddress+i);	
	#if 1 // uses some sweet bit manipulation
	*(uint16_t*)&ReadInData[i] = stuff;
	#else // not bit manipulation
			ReadInData[i] = stuff & 0x00ff;
		ReadInData[i+1]  = (stuff & 0xff00) >> 8;
	#endif
	}
	if (ammount % 2 == 1)
	ReadInData[ammount-1] = SingleByteRead(RegisterAddress+(uint8_t)(ammount-1));
}