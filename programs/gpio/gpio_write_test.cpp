

#include "gpio.cpp"

using std::cout;
using std::endl;

int main(){
	const int pin = 17;
	const int wait = 500000;

	ExportPin(pin);
	pinMode(pin, 1);
	digitalWrite(pin, 1);


	while(1){
		for(int i=0; i < 7; i++){
			usleep(wait);
			digitalWrite(pin, 0);
			cout << "0   "<<std::flush;
			usleep(wait);
			digitalWrite(pin, 1);
			cout << "1   "<<std::flush;
		}
		cout << endl;
	}

	unexport(pin);

	return 0;
}