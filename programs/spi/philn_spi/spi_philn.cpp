#include <stdint.h>
#include <stdio.h> // puts , printf
#include <stdlib.h> // used for alloca
#include <fcntl.h> // file controll
#include <sys/ioctl.h>
#include <linux/spi/spidev.h> // defines such as spi_ioc_transfer
#include <unistd.h> // for close().


namespace philn{
	namespace SpiFunctions{
		// Configurable stuff		
		const char *device = "/dev/spidev0.0";
		const uint8_t Default_mode = 0;
		const uint8_t Default_bits = 8;
		const uint16_t Default_delay = 0;
		const uint32_t Default_speed = 500000;
		
		bool Setup(int& FileHandleToSet , uint8_t mode, uint8_t bits, uint32_t speed, uint16_t delay);

		bool QuickSetup(int& FileHandle);
		
		bool GetValues(const int FileHandle , uint8_t& mode, uint8_t& bits, uint32_t& speed, uint16_t& delay);

		bool GetAndPrintValues(const int FileHandle);
		
		bool SpiTransfer(const int FileHandle,const uint8_t* SendBuffer ,const int MessageLength, uint8_t* RecieveBuffer);
		
		// Stand alone qick test
		void QuickTest();
		
	}
	
	class spi{
	public:
// After this, bytes can be read and sent
		bool Setup( uint8_t mode, uint8_t bits, uint32_t speed, uint16_t delay);
		// Setup without needing to specify anything
		bool DefaultSetup();
		bool SpiTransfer(const uint8_t* SendBuffer ,const int MessageLength, uint8_t* RecieveBuffer);
		// Returns the values of uint8_t mode, uint8_t bits, uint32_t speed, uint16_t delay
		bool GetValues(uint8_t& mode, uint8_t& bits, uint32_t& speed, uint16_t& delay);
		// Prints the values of uint8_t mode, uint8_t bits, uint32_t speed, uint16_t delay
		bool GetAndPrintValues();
		// Read in buffer is don't care
		bool SendOnly(const uint8_t* SendBuffer, const int MessageLength);
		// Send out buffer is a don't care
		bool ReadOnly(uint8_t* RecieveBuffer, const int MessageLength);
		
		~spi(){
			close(FileHandle);
		}
		
	private:
		int FileHandle;
	};
	
	bool spi::Setup( uint8_t mode, uint8_t bits, uint32_t speed, uint16_t delay){
		return SpiFunctions::Setup(FileHandle , mode , bits , speed , delay);
	}
	bool spi::DefaultSetup(){
		return SpiFunctions::Setup(FileHandle , SpiFunctions::Default_mode , SpiFunctions::Default_bits , SpiFunctions::Default_speed , SpiFunctions::Default_delay);
	}
	bool spi::GetValues(uint8_t& mode, uint8_t& bits, uint32_t& speed, uint16_t& delay){
		return SpiFunctions::GetValues(FileHandle , mode , bits , speed , delay);
	}
	bool spi::SpiTransfer(const uint8_t* SendBuffer ,const int MessageLength, uint8_t* RecieveBuffer){
		return SpiFunctions::SpiTransfer(FileHandle, SendBuffer,MessageLength,RecieveBuffer);
	}
	bool spi::GetAndPrintValues(){
		return SpiFunctions::GetAndPrintValues(FileHandle);
	}
	
	bool spi::SendOnly(const uint8_t* SendBuffer, const int MessageLength){
		uint8_t* RecieveBuffer = (uint8_t*)alloca(sizeof(uint8_t)*MessageLength); // Stack allocate
		return SpiTransfer( SendBuffer ,MessageLength, RecieveBuffer);
	}

	bool spi::ReadOnly(uint8_t* RecieveBuffer, const int MessageLength){
		uint8_t* SendBuffer = (uint8_t*)alloca(sizeof(uint8_t)*MessageLength); // Stack allocate
		return SpiTransfer( SendBuffer ,MessageLength, RecieveBuffer);
	}

	namespace SpiFunctions{
		
		bool Setup(int& FileHandleToSet , uint8_t mode, uint8_t bits, uint32_t speed, uint16_t delay){
			bool Error = 1;

			// Does something with device
			FileHandleToSet = open(device, O_RDWR);
			int& fd = FileHandleToSet;
			if(fd < 0)
			return Error;

			// Sets Mode
			if( ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0)
			return Error;

			// Sets bits per word
			if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0)
			return Error;

			// Sets Speed
			if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)
			return Error;

			return !Error;
		}

		bool QuickSetup(int& FileHandle){
			bool Error = 1;
			uint8_t mode,bits;
			uint16_t delay;
			uint32_t speed;
			mode=0;
			bits=8;
			speed=500000;
			delay=0;
			return (Setup(FileHandle, mode,  bits,  speed,  delay))? Error : !Error;
		}
		
		bool GetValues(const int FileHandle , uint8_t& mode, uint8_t& bits, uint32_t& speed, uint16_t& delay){
			bool Error = 1;

			// Gets mode
			if (ioctl(FileHandle, SPI_IOC_RD_MODE, &mode) < 0)
			return Error;
			
			// Gets bits per word
			if(ioctl(FileHandle, SPI_IOC_RD_BITS_PER_WORD, &bits)<0)
			return Error;
			
			// Gets speed
			if(ioctl(FileHandle, SPI_IOC_RD_MAX_SPEED_HZ, &speed)<0)
			return Error;

			return !Error;
		}

		bool GetAndPrintValues(const int FileHandle){
			bool Error = 1;

			uint8_t mode,bits;
			uint16_t delay;
			uint32_t speed;
			if(GetValues(FileHandle, mode, bits, speed, delay)){
				puts("An Error Has Occored in Getting the Values!");
				return Error;
			}
			printf("Mode: %d\nBits: %d\nDelay: %d\nMax Speed (kHz): %d",(int)mode,(int)bits,(int)delay,(int)speed / 1000);
			puts("");
			return !Error;
		}
		
		bool SpiTransfer(const int FileHandle,const uint8_t* SendBuffer ,const int MessageLength, uint8_t* RecieveBuffer){
			bool Error = 1;
			// spi_ioc_transfer tr = {	(unsigned long)&SendBuffer[0],	(unsigned long)&RecieveBuffer[0],	 MessageLength,	 delay,	 speed,	 bits,	};
			spi_ioc_transfer tr = {	(unsigned long)&SendBuffer[0],	(unsigned long)&RecieveBuffer[0],	 MessageLength,	};
			if( 1 > ioctl(FileHandle, SPI_IOC_MESSAGE(1), &tr))
			return Error;

			return !Error;
		}

		// Only used by void QuickTest()
		inline bool ScopeTest(const int FileHandle){
			bool Error = 1;
			// Some Test Messaging
			uint8_t SendBuffer[256];
			uint8_t RecieveBuffer[256];
			int MessageLength = 100;
			// Setup Of Test Message
			for(int i=0;i<255;i++){
				SendBuffer[i] = 0xaa;
				RecieveBuffer[i]=(uint8_t)(-i);
			}
			// Repedative Sending
			for(int i=0;i<20000;i++){
				if(SpiTransfer(FileHandle , SendBuffer , MessageLength , RecieveBuffer)){
					printf("Spi Transfer Error!\nLine %d\nFile %d", __LINE__ , __FILE__);
					return Error;
				}
				if(i%100 == 0){
					printf("%6d",i);puts("");
				}
			}
			puts("Done Testing Scope");
			return !Error;
		} 
		
		void QuickTest(){
			int FileHandle;
			if (QuickSetup(FileHandle)){
				puts("Error With Setup!");
				return;
			}
			if (GetAndPrintValues(FileHandle))
			return;
			ScopeTest(FileHandle);
		}
		
	}	
	
}