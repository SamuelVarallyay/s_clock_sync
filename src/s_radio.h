#ifndef S_RADIO_H_
#define S_RADIO_H_

#include <stdint.h>
#include <string.h>
#include "ezradio_cmd.h"
#include "ezradio_plugin_manager.h"

#define FIELD_LENGTH 0
#define FIELD_SOURCE_ADDR 1
#define FIELD_DEST_ADDR 2
#define FIELD_MSG_TYPE 3
#define FIELD_PAYLOAD 4
#define HEADER_LENGTH 4

static inline void setSourceAddress(uint8_t* packet, uint8_t address){
	packet[FIELD_SOURCE_ADDR] = address;
}
static inline void setDestinationAddress(uint8_t* packet, uint8_t address){
	packet[FIELD_DEST_ADDR] = address;
}
static inline void setMessageType(uint8_t* packet, uint8_t type){
	packet[FIELD_MSG_TYPE] = type;
}

static inline void setPayload(uint8_t* packet, void* data, size_t size){
	packet[FIELD_LENGTH] = HEADER_LENGTH + size;
	uint8_t* payload = &packet[FIELD_PAYLOAD];
	memcpy(payload, data, size);
}

static inline uint8_t getPayloadLength(uint8_t* packet){
	return packet[FIELD_LENGTH] - HEADER_LENGTH;
}
static inline uint8_t getSourceAddress(uint8_t* packet){
	return packet[FIELD_SOURCE_ADDR];
}
static inline uint8_t getDestinationAddress(uint8_t* packet){
	return packet[FIELD_DEST_ADDR];
}
static inline uint8_t getMessageType(uint8_t* packet){
	return packet[FIELD_MSG_TYPE];
}
static inline uint8_t* getPayload(uint8_t* packet){
	return packet + FIELD_PAYLOAD;
}


typedef void (*void_Callback_t)( void );
typedef void (*rx_Callback_t)( uint8_t* );

Ecode_t s_radioSendPacket(uint8_t *pioRadioPacket);
void s_radioLoop();
void s_radioInit();
void s_radioSetTxCallback(void_Callback_t callback);
void s_radioSetRxCallback(uint8_t msg_type, rx_Callback_t callback);
uint8_t s_radioGetOwnAddress();
void s_radioSetOwnAddress(uint8_t address);

#endif /* S_RADIO_H_ */
