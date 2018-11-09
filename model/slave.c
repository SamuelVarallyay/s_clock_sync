/*
 * slave.c
 *
 *  Created on: 2018. okt. 28.
 *      Author: Samu
 */

#include <stdio.h>
#include <stdint.h>
#include "s_clock.h"
#include "s_radio.h"
#include "s_sync.h"
#include "tdma_params.h"


packet_t* packet;
void init_slave(sync_data_t* syncdata, packet_t* packet_){
	sync_data = syncdata;
	packet = packet_;
}

void saveSyncTime(){
	sync_data->cycle_start_ms = packet->cycle_start_ms;
	sync_data->sync_slave = s_ts_to_int(s_clockGetRX_ts());
}

void saveFollowUp(){
	sync_data->sync_master = packet->sync_master + (sync_data->cycle_start_ms * CLOCK_FREQUENCY_KHZ);
}

void directCompensateOffset(){
	calculate_offset(sync_data);
	s_clockAddInt(sync_data->offset);
}

void directCompensateDrift(){
	calculate_offset(sync_data);
	s_clockAddInt(sync_data->offset);
}

void calculate_offset(sync_data_t* sync_data){
	sync_data->offset = sync_data->sync_slave - sync_data->sync_master - sync_data->delay;
}

void calculate_delay(sync_data_t* sync_data){
	sync_data->delay = sync_data->delay_req - sync_data->sync_slave;
}
