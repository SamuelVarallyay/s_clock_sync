#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_prs.h"
#include "s_clock.h"
#include "s_radio.h"
#include "s_sync.h"
#include <stdio.h>

volatile int64_t sync_received = 0;
volatile int64_t sync_sent = 0;

void SyncReceivedCallback(uint8_t* packet){
	s_timeStamp a;
	a = s_clockGetRX_ts();
	sync_received = s_ts_to_int(a);
	sync_period_multiplier = *getPayload(packet);
	printf("SyncRX: %u %u ",(unsigned)(sync_received >> 32), (unsigned)(sync_received&UINT32_MAX));
}
void controller();
void FollowUpReceivedCallback(uint8_t* packet){
	memcpy(&sync_sent,getPayload(packet),sizeof(sync_sent));
	printf("SyncTX: %u %u\n",(unsigned)(sync_sent >> 32), (unsigned)(sync_sent&UINT32_MAX));
	s_clockDriftReset();
	controller();
}

int64_t transfer_delay = -1500;
#define MAX_CLOCK_DIFF (3*CLOCK_FREQUENCY_KHZ)
void controller(){
	static volatile int64_t prev_offset = 0;
	volatile int64_t offset = sync_sent - sync_received + transfer_delay;
	static int64_t I = 0;

	printf("o:%d ",(int)offset);
	printf("po:%d",(int)prev_offset);
 	if (abs(offset) > MAX_CLOCK_DIFF){
		s_clockDriftReset();
		int64_t ms = offset / CLOCK_FREQUENCY_KHZ;
		s_clockAddMillisecs(ms);
		offset = offset - (ms * CLOCK_FREQUENCY_KHZ);
		prev_offset = offset;
		printf(" n:%d",(int)offset);
		I = 0;
	}
	printf("\n");
	int64_t P = (offset << 16) / (BASE_SYNC_PERIOD_MS * sync_period_multiplier);
	int64_t D = ((offset - prev_offset) << 16) / (BASE_SYNC_PERIOD_MS * sync_period_multiplier);
	I = (I + offset);
	fixedpt W = (P >> 1) + (D >> 3) + (I>>4);
	s_clockDriftCorrection(W);

/*
	float sampling_interval = (BASE_SYNC_PERIOD_MS * sync_period_multiplier);
	float KP = 1.0 / (float) 4;
	float KD = 1.0 / (float) 8;

	float P = KP * offset / sampling_interval;
	float D = KD * (offset - prev_offset) / sampling_interval;
	fixedpt W = (fixedpt)((P+D)*(1<<16));

	s_clockDriftCorrection(W);

*/
	prev_offset = offset;
}

void s_syncSlaveFSMinit(){
	uint8_t typ = Sync;
	s_radioSetRxCallback(typ, SyncReceivedCallback);
	typ = FollowUp;
	s_radioSetRxCallback(typ, FollowUpReceivedCallback);

}

void s_syncSlaveFSMtask(){

}
