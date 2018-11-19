#ifndef S_SYNC_H_
#define S_SYNC_H_

#define	SYNC 0
#define	FOLLOW_UP 1
#define	DATA 2

#include <stdint.h>

void setup_prs();

void sendPacket(uint8_t* packet);
void startRx();

void setSourceAddress(uint8_t* packet, uint8_t address);
void setPacketType(uint8_t* packet, uint8_t type);
void setSyncTimeStamp(uint8_t* packet, int64_t timestamp);

uint8_t getSourceAddress(uint8_t* packet);
uint8_t getPacketType(uint8_t* packet);
int64_t getSyncTimeStamp(uint8_t* packet);

void setDelayResp(uint8_t* packet, int32_t timestamp, uint8_t slave_index);
int32_t getDelayResp(uint8_t* packet, uint8_t slave_index);

#endif /* S_SYNC_H_ */
