#ifndef S_SYNC_H_
#define S_SYNC_H_

typedef struct{
	int64_t sync_master;
	int64_t sync_slave;
	int32_t delay_req;
	int32_t delay_resp;
	int32_t delay;
	int64_t offset;
}sync_data_t;

void calculate_offset(sync_data_t* sync_data);
void calculate_delay(sync_data_t* sync_data);

void setup_prs();

#endif /* S_SYNC_H_ */
