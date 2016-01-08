#include "spi_philn.cpp"

#include <unistd.h>

int main(){
	philn::spi spi1;
	// philn::SpiFunctions::QuickTest();

	spi1.DefaultSetup();
	
	int choice = 2;
	
	switch (choice){
	case 1:{
		uint8_t RecieveBuffer[256];
			int MessageLength = 20;
			for(int i=0; i < 10000; i++){
				spi1.ReadOnly(RecieveBuffer, MessageLength);
				for(int i=0 ; i < MessageLength; i++){
					printf("%02x  ",(int)RecieveBuffer[i]);
				}
				puts("");
				usleep(500000);
			}
		}
	case 2:{
			uint8_t SendBuffer[256];
			int MessageLength = 20;
			for(int i=0; i < 256; i++)
			SendBuffer[i]=(uint8_t)(-i);
			for(int i=0; i < 10000;i++){
				spi1.SendOnly(SendBuffer,MessageLength);
				if(i%5==0){
					printf("%7d",i);puts("");
				}
				usleep(500000);
			}
		}
	}
	return 0;
}
