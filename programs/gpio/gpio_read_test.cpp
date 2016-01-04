

#include "gpio.cpp"

using std::cout;
using std::endl;

int main(){
const int pin = 17;
const int wait = 250000;

ExportPin(pin);
pinMode(pin, 0);


while(1){
for(int i=0; i < 15; i++){
usleep(wait);
int value = digitalRead(pin);
cout << value << "  "<<std::flush;
}
cout << endl;
}

unexport(pin);

return 0;
}