#ifndef S_SYNC_H_
#define S_SYNC_H_

#define	SYNC (0)
#define	FOLLOW_UP (1)
#define	SLAVE (2)

#include <stdint.h>

void setup_prs();

void dbgPrintStr(const char* string);
void dbgPrintInt(const char* string,int64_t integer);
void logPrint(int offset,int delay,int integral);
void sensorPrint(int source, int64_t timestamp);

void sendPacket(uint8_t* packet);
void startRx();

void setSourceAddress(uint8_t* packet, uint8_t address);
uint8_t getSourceAddress(uint8_t* packet);

void setPacketType(uint8_t* packet, uint8_t type);
uint8_t getPacketType(uint8_t* packet);

void setSyncTimeStamp(uint8_t* packet, int64_t timestamp);
int64_t getSyncTimeStamp(uint8_t* packet);

void setDelayResp(uint8_t* packet, int32_t timestamp, int32_t slave_index);
int32_t getDelayResp(uint8_t* packet, int32_t slave_slot);

#define setMeasurement(packet, ts) setSyncTimeStamp(packet, ts)
#define getMeasurement(packet) getSyncTimeStamp(packet)



#endif /* S_SYNC_H_ */
