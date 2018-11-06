#ifndef S_SYNC_H_
#define S_SYNC_H_

typedef struct{
	uint64_t cycle_start_ms;
	int64_t sync_master;
	int64_t sync_slave;
	int32_t delay_req;
	int32_t delay_resp;
	int32_t delay;
	int64_t offset;
}sync_data_t;


typedef struct __attribute__((__packed__)){
	uint8_t source:7;
	uint8_t type:1;
	union{
		uint64_t cycle_start_ms;
		uint64_t sync_master;
		uint8_t payload[63];
	};
}packet_t;

void calculate_offset(sync_data_t* sync_data);
void calculate_delay(sync_data_t* sync_data);

void setup_prs();

#endif /* S_SYNC_H_ */
