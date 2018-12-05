#include <stdint.h>
#include <stdlib.h>
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_prs.h"
#include "s_clock.h"
#include "s_radio.h"
#include "s_sync.h"
#include "retargetserial.h"
#include <stdio.h>

void setup_prs(){
    /* Setup PRS */
	CMU_ClockEnable(cmuClock_PRS, true);

	/* Configure RF_GPIO0 and RF_GPIO1 to inputs. */
	GPIO_PinModeSet((GPIO_Port_TypeDef) RF_GPIO0_PORT, RF_GPIO0_PIN, gpioModeInput, 0);
	GPIO_PinModeSet((GPIO_Port_TypeDef) RF_GPIO1_PORT, RF_GPIO1_PIN, gpioModeInput, 0);

	/* Pin PA0 and PA1 output the GPIO0 and GPIO1 via PRS to breakout pad*/
	GPIO_PinModeSet(gpioPortA, 0, gpioModePushPull, 0);
	GPIO_PinModeSet(gpioPortA, 1, gpioModePushPull, 0);

	/* Disable INT for PRS channels */
	GPIO_IntConfig((GPIO_Port_TypeDef) RF_GPIO0_PORT, RF_GPIO0_PIN, false, false, false);
	GPIO_IntConfig((GPIO_Port_TypeDef) RF_GPIO1_PORT, RF_GPIO1_PIN, false, false, false);

	/* Setup PRS for RF GPIO pins  */
	PRS_SourceAsyncSignalSet(0, PRS_CH_CTRL_SOURCESEL_GPIOH, PRS_CH_CTRL_SIGSEL_GPIOPIN15);
	PRS_SourceAsyncSignalSet(1, PRS_CH_CTRL_SOURCESEL_GPIOH, PRS_CH_CTRL_SIGSEL_GPIOPIN14);
	PRS ->ROUTE = (PRS_ROUTE_CH0PEN | PRS_ROUTE_CH1PEN);

	/* Make sure PRS sensing is enabled (should be by default) */
	GPIO_InputSenseSet(GPIO_INSENSE_PRS, GPIO_INSENSE_PRS);
}

void dbgPrintStr(const char* string){
	printf("%s\r\n",string);
}
void dbgPrintInt(const char* string,int64_t integer){
	if(integer> INT32_MAX){
		printf("%s+++\r\n",string);
	}else if(integer< INT32_MIN){
		printf("%s---\r\n",string);
	}else{
		printf("%s%d\r\n",string,(int)integer);
	}
}

void logPrint(int offset,int delay,int integral){
	printf("%d, %d, %d     \r",offset,delay,integral);
}

void sendPacket(uint8_t* packet)
{
	ezradio_write_tx_fifo(64, packet);
	ezradio_start_tx(0, 0x30, 0u);
	//ezradio_start_tx_fast();
}

void startRx(){
	ezradio_start_rx_fast();
}


void setSourceAddress(uint8_t* packet, uint8_t address){
	packet[0] = address;
}

uint8_t getSourceAddress(uint8_t* packet){
	return packet[0];
}

void setPacketType(uint8_t* packet, uint8_t type){
	packet[1] = type;
}

uint8_t getPacketType(uint8_t* packet){
	return packet[1];
}

void setSyncTimeStamp(uint8_t* packet, int64_t timestamp){
	packet[2+0] = (timestamp >> 8*7) & 0xFF;
	packet[2+1] = (timestamp >> 8*6) & 0xFF;
	packet[2+2] = (timestamp >> 8*5) & 0xFF;
	packet[2+3] = (timestamp >> 8*4) & 0xFF;
	packet[2+4] = (timestamp >> 8*3) & 0xFF;
	packet[2+5] = (timestamp >> 8*2) & 0xFF;
	packet[2+6] = (timestamp >> 8*1) & 0xFF;
	packet[2+7] = (timestamp >> 8*0) & 0xFF;

}

int64_t getSyncTimeStamp(uint8_t* packet){
	int64_t timestamp;
	timestamp  = (uint64_t)packet[2+0] << 8*7;
	timestamp |= (uint64_t)packet[2+1] << 8*6;
	timestamp |= (uint64_t)packet[2+2] << 8*5;
	timestamp |= (uint64_t)packet[2+3] << 8*4;
	timestamp |= (uint64_t)packet[2+4] << 8*3;
	timestamp |= (uint64_t)packet[2+5] << 8*2;
	timestamp |= (uint64_t)packet[2+6] << 8*1;
	timestamp |= (uint64_t)packet[2+7] << 8*0;
	return timestamp;
}

void setDelayResp(uint8_t* packet, int32_t timestamp, int32_t slave_slot){
	uint8_t index = 2 + (slave_slot-2) * 4;
	packet[index+0] = (timestamp >> 8*3) & 0xFF;
	packet[index+1] = (timestamp >> 8*2) & 0xFF;
	packet[index+2] = (timestamp >> 8*1) & 0xFF;
	packet[index+3] = (timestamp >> 8*0) & 0xFF;
}

int32_t getDelayResp(uint8_t* packet, int32_t slave_slot){
	uint8_t index = 2 + (slave_slot-2) * 4;
	int32_t timestamp;
	timestamp  = (uint32_t)packet[index+0] << 8*3;
	timestamp |= (uint32_t)packet[index+1] << 8*2;
	timestamp |= (uint32_t)packet[index+2] << 8*1;
	timestamp |= (uint32_t)packet[index+3] << 8*0;
	return timestamp;
}

void setMeasurement(uint8_t* packet, int32_t measurement){
	packet[2+0] = (measurement >> 8*3) & 0xFF;
	packet[2+1] = (measurement >> 8*2) & 0xFF;
	packet[2+2] = (measurement >> 8*1) & 0xFF;
	packet[2+3] = (measurement >> 8*0) & 0xFF;
}

int32_t getMeasurement(uint8_t* packet){
	int32_t measurement;
	measurement  = (uint32_t)packet[2+0] << 8*3;
	measurement |= (uint32_t)packet[2+1] << 8*2;
	measurement |= (uint32_t)packet[2+2] << 8*1;
	measurement |= (uint32_t)packet[2+3] << 8*0;
	return measurement;
}
