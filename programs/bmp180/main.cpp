// sudo i2cdetect -r -y 1
// sudo i2cdump -y 1 address (0x77 , 0x69)

#include <iostream>

#include "BMP180.h"

using std::cout;
using std::endl;

int main() {
char NotRun = 1;
		BMP_Presure_Temp bmp(1, 0x77);
		bmp.StartBMP();
	while (1) {

		cout << "Temperature is " << (float) bmp.GetTemp() / 10 << " degrees Celsius" << endl;
		cout << "Pressure is " << bmp.GetPressure() << " Pa" << endl;
		

// */
		cout << "\n" << endl;
		usleep(500000);

	}
	bmp.CloseBMP();
	return 0;
}
