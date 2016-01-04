#include <iostream>
#include <fstream>
// #include <cstring>
#include <string>
#include <sstream>
// #include <stdio.h>
// #include <stdlib.h>

//Converting a number to string
std::string numberToString(int num){
	std::ostringstream strout;
	std::string str;

	strout << num;
	str = strout.str();

	return str;
}

//Converting string to number
int stringToNumber(std::string str){
	std::stringstream  strin;
	int var;

	strin << str;
	strin >> var;
	
	return var;
}

int ExportPin(int pin){
	std::string pin_str = numberToString(pin);
	std::string dir = "/sys/class/gpio/export";
	std::ofstream file (dir.c_str());
	if (file < 0) {
perror("File not found");
	return -1;
	}
	file << pin;
	file.close();
}

/** @~english 
* @brief Removes the GPIO. 
*
* Removes the GPIO from the filesystem, after that, you cannot access the pin.
* @return bool error_flag
*
* @~german 
* @brief Entferne GPIO
*
* Entfernt den GPIO aus dem Filesystem, es kann kein Zugriff mehr auf diesen erfolgen.
* @return bool error_flag
*/
int unexport(int pin){
	std::string pin_str = numberToString(pin);
	std::string dir = "/sys/class/gpio/unexport";
	std::ofstream file (dir.c_str());
	if (file < 0) {
perror("error");
		return -1;
	}
	file << pin_str;
	file.close();
	return 1;
}

// 1 is output, 0 is input

/** @~english 
* @brief Change the PinMode.
*
* With this function you can set the pin as input or output. <br>
* This must be done before all other operations. <br><br>
* Hint: GPIO 4 can only be used as input.
* @param pin Pin number to change the mode
* @param direction direction of the pin (OUTPUT, INPUT)
* @return success: 1, failure: -1
*/
int pinMode(int pin, int direction){
	std::string pin_str = numberToString(pin);
	std::string dir;
	std::ofstream file;

	dir = "/sys/class/gpio/gpio" + pin_str + "/direction";

	file.open(dir.c_str());
	if (file < 0) {
	perror("error");
		return -1;
	}
	file << (direction)? "out" : "in";
	file.close();
	return 1;
}

/** @~english 
* @brief Write Pin.
*
* Set the Pin to the given value. 
* @param pin Pin number to change the mode
* @param value Value of the Pin (LOW, HIGH)
* @return success: 1, failure: -1
*
* @~german 
* @brief Pin schreiben.
*
* Den GPIO-Pin auf einen bestimmten Wert setzen. 
* @param pin Nummer des entsprechenden GPIO-Pins
* @param value Wert auf den der Pin gesetzt werden soll (LOW, HIGH) 
* @return Erfolg: 1, Fehler: -1
*/
int digitalWrite(int pin, int value){
value = (value != 0)? 1 : 0;

	std::string value_str = numberToString(value);
	std::string pin_str = numberToString(pin);
	std::string dir = "/sys/class/gpio/gpio" + pin_str + "/value";

	std::ofstream file (dir.c_str());
	if (file < 0) {
		perror("error");
		return -1;
	}
	file << value_str;
	file.close();
	return 1;
}

/** @~english 
* @brief Read Pin.
*
* Reads the value of the given pin. 
* @param pin Pin number to read
* @return Value of the GPIO-Pin (0,1), -1 in case of failure 
*
* @~german 
* @brief Pin lesen.
*
* Abfragen des GPIO-Wertes. 
* @param pin Nummer des entsprechenden GPIO-Pins
* @return Wert des GPIO-Pins (0,1), -1 im Fehlerfall 
*/
int digitalRead(int pin) {
	std::string value;
	std::string pin_str = numberToString(pin);
	std::string device = "/sys/class/gpio/gpio" + pin_str + "/value";
	std::ifstream file(device.c_str());
	if (file < 0){
perror("error");
		return -1;
	}
	file >> value;
	file.close();
	return stringToNumber(value);
}












