#ifndef S_SYNC_H_
#define S_SYNC_H_


typedef struct __attribute__((__packed__)){
	uint8_t source:7;
	uint8_t type:1;
	union{
		uint64_t cycle_start_ms;
		uint64_t sync_master;
		uint8_t payload[63];
	};
}packet_t;

void setup_prs();

#endif /* S_SYNC_H_ */
