void ADXL345_accelInit() {
	  	//0x31: DATA_FORMAT register (e.g., set to FULL_RES, ±2 g)
	//D7 - Self test. D6 - SPI. D5 - INT_INVERT. D4 -0. D3 - FULL_RES. D2- Justify. D1 && D0 - Range
SingleByteWrite(0x31,0b00001000);

	//Register 0x2C?BW_RATE (Read/Write). D3:D0 is Rate. D4 is low power. 6.25 = 0110. 12.5 = 0111. 25 = 1000.
	SingleByteWrite(0x2C,0b0110+1);

	//0x2D: POWER_CTL register
	//D5 - link. D4 - AutoSleep. D3- measure. D2 - Sleep. D0 && D1 - "wakeup"
	SingleByteWrite(0x2D , 0b1000);
	}

void accelGetData(int& x, int& y, int& z) {
	 // used as temporary memory location to stor new values red in duing multibyte read
    uint8_t StoreTo[6];
    // Reads in registers 0x32 to 0x37 and stores values sequentally in StoreTo[0] to StoreTo[5]
    MultiByteRead(0x32, &StoreTo[0],6);		 
	 
    // unsigned int x = 0, y = 0, z = 0;
    x = (int16_t) (StoreTo[0] | (StoreTo[1] << 8));
    y = (int16_t)(StoreTo[2] | (StoreTo[3] << 8));
    z = (int16_t)(StoreTo[4] | (StoreTo[5] << 8));
}




