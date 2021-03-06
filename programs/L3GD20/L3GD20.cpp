void L3GD20_Initialize(){
// 0x20 CTRL1 important
SingleByteWrite(0x20, 0xff);

// 0x21 CTRL2 not important
SingleByteWrite(0x21, 0x00);

// 0x22 CTRL3 not important
SingleByteWrite(0x22, 0x00);

// 0x23 CTRL4 not too important
SingleByteWrite(0x23, 0x00);

// 0x24 CTRL 5 not too important
SingleByteWrite(0x24, 0x00);
}

// -1 cecius / LSB
int L3GD20_GetTemperature(){
return 48-(int)(int8_t)SingleByteRead(0x26);
}

void L3GD20_GetGyroData(int& x, int& y, int& z){
uint8_t ReadInData[6];
MultiByteReadSingleBytes(0x28, &ReadInData[0],6);

x = (int16_t)(ReadInData[0] | (ReadInData[1]<<8));
y = (int16_t)(ReadInData[2] | (ReadInData[3]<<8));
z = (int16_t)(ReadInData[4] | (ReadInData[5]<<8));
}

