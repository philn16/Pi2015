
void Initialize_LSM303D(){
// Powers Down the device
// Disables axis and makes data selection rate 0
SingleByteWrite(0x20 , 0x00); 

// BOOT , FIFO_EN , FTH_EN , 0 , 0 , HP_Click , HPIS1 , HPIS2
SingleByteWrite(0x1f , 0x00);

// AODR3 , AODR2 , AODR1 , AODR0 , BDU , AZEN , AYEN , AXEN
// AODR [3:0] Acceleration data rate selection. Default value: 000 (0000: Power-down mode; Others: Refer to Table 36)
// BDU Block data update for acceleration and magnetic data. Default value: 0 (0: continuous update; 1: output registers not updated until MSB and LSB have been read)
SingleByteWrite(0x20 , 0x47); 

// ABW1 , ABW0 , AFS2 , AFS1 , AFS0 , 0 , AST , SIM
// AFS[2:0] determines sensitivity. 3'b0 = 2, 3'd1 = 4, ...3'd4 = 16
SingleByteWrite(0x21 , 0x00);

// INT1_BOOT , INT1_Click , INT1_IG1 , INT1_IG2 , INT1_IGM , INT1_DRDY_A , INT1_DRDY_M , INT1_EMPTY
SingleByteWrite(0x22 , 0x00);

// 0x23 is more interrupts

// TEMP_EN , M_RES1 , M_RES0 , M_ODR2 , M_ODR1 , M_ODR0 , LIR2 , LIR1
SingleByteWrite(0x24 , 0xf8);

// 0 , MFS1 , MFS0 , 0 , 0 , 0 , 0, 0
// MFS: 2'd0 = +- 2 gauss , 1 = +- 4 , 2 = +- 8 , 3 = +- 12
SingleByteWrite(0x25 , 0x60);

// AHPM1 , AHPM0 , AFDS , T_ONLY , 0 , MLP , MD1 , MD0
SingleByteWrite(0x26 , 0x00);

// FM2 , FM1 , FM0 , FTH4 , FTH3 , FTH2 , FTH1 , FTH0
SingleByteWrite(0x2E , 0x00);

// AZEN Acceleration Z-axis enable. Default value: 1 (0: Z-axis disabled; 1: 

// Enable Temperature 0x24
		// Temp_EN , M_RES1 , M_RES0 , M_ODR2 , M_ODR1 , M_ODR0 , LIR2 , LIR1
	// The LSM303D features an internal temperature sensor. Temperature data can be enabled by setting the TEMP_EN bit on the CTRL5 (24h) register to 1.
	// TEMP_EN Temperature sensor enable. Default value: 0 (0: temperature sensor disabled; 1: temperature sensor enabled)
// M_RES [1:0] Magnetic resolution selection. Default value: 00 (00: low resolution, 11: high resolution)
// M_ODR [2:0] Magnetic data rate selection. Default value: 110		Refer to Table 47
// LIR2 Latch interrupt request on INT2_SRC register, with INT2_SRC register cleared by
// reading INT2_SRC itself. Default value: 0. (0: interrupt request not latched; 1: interrupt request latched)
// LIR1 Latch interrupt request on INT1_SRC register, with INT1_SRC register cleared by
// reading INT1_SRC itself. Default value: 0. (0: interrupt request not latched; 1: interrupt request latched).
		// 1 [1 1] [1 1 0] [0] [0]
		// SingleByteWrite(0x24, 0xf8);

	
	// NOT NEEDED
	// FIFO_CTRL_REG (0x2E)
	// { FIFO MODE[2:0] , Watter Mark[4:0] } 
	// FIFO: 3'd0 := Bypass Mode , 3'd1 := FIFO mode , 3'd2 := stream mode , 3'd3 := Stream to FIFO ,3'd4 := Bypass to Stream ,
	
}

void Read_LSM303D_Accelerometer(int& x,int& y,int& z){
	// Read address 0x28 : 0x2D
	// x = 0x29 << 8 | 0x28
	// y = 0x2B << 8 | 0x2A
	// z = 0x2D << 8 | 0x2C

	uint8_t regs[6];
	MultiByteReadSingleBytes(0x28, &regs[0],6);
	x = (int16_t)(regs[0] | (regs[1] << 8));
	y = (int16_t)(regs[2] | (regs[3] << 8));
	z = (int16_t)(regs[4] | (regs[5] << 8));	
}

void Read_LSM303D_Magnetometer(int& x,int& y,int& z){
	uint8_t regs[6];
	MultiByteReadSingleBytes(0x08, &regs[0],6);
	x = (int16_t)(regs[0] | (regs[1] << 8));
	y = (int16_t)(regs[2] | (regs[3] << 8));
	z = (int16_t)(regs[4] | (regs[5] << 8));	
}

// 8 LSB per degree celscius
int Read_LSM303D_Temperature(){
	// The LSM303D features an internal temperature sensor. Temperature data can be enabled by setting the TEMP_EN bit on the CTRL5 (24h) register to 1.
	
	// The output data rate of the temperature sensor is set by M_ODR [2:0] in CTRL5 (24h) and is equal to the magnetic sensor output data rate
	
	// Temperature Register (0x05) | (0x06 << 8). 1 LSB / deg
	uint8_t reg[2];
	MultiByteReadSingleBytes(0x05, &reg[0],2);
	int temperature = (int16_t)(reg[0] | (reg[1] << 8));
	return temperature;
}