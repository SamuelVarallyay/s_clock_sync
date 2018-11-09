/*
 * slave.h
 *
 *  Created on: 2018. okt. 28.
 *      Author: Samu
 */

#ifndef MODEL_SLAVE_H_
#define MODEL_SLAVE_H_

typedef struct{
	uint64_t cycle_start_ms;
	int64_t sync_master;
	int64_t sync_slave;
	int32_t delay_req;
	int32_t delay_resp;
	int32_t delay;
	int64_t offset;
}sync_data_t;

void calculate_offset(sync_data_t* sync_data);
void calculate_delay(sync_data_t* sync_data);

#endif /* MODEL_SLAVE_H_ */
