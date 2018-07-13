#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_prs.h"
#include "s_clock.h"
#include "s_radio.h"
#include "s_sync.h"
#include "sc_timer_service.h"
#include "sc_types.h"
#include "Timesync_master.h"
#include <stdio.h>


#define MAX_TIMERS 8 //number of timers our timer service can use

static Timesync_master timesync_masterFSM;

static sc_timer_service_t timer_service;

static sc_timer_t timers[MAX_TIMERS];

void SyncTransmittedCallback ( ){
	timesync_masterIface_raise_syncSent(&timesync_masterFSM);
	s_radioSetTxCallback(NULL);
}

sc_integer timesync_masterIface_sendSync(const Timesync_master* handle){
	uint8_t packet[HEADER_LENGTH + sizeof(sync_period_multiplier)];
	setDestinationAddress(packet,0xFF);  //address: broadcast
	setSourceAddress(packet,0x00);
	setMessageType(packet,Sync);
	setPayload(packet,&sync_period_multiplier,sizeof(sync_period_multiplier));
	Ecode_t e = s_radioSendPacket(packet);
	if (0 == e){
		s_radioSetTxCallback(SyncTransmittedCallback);
		printf("Sync ");
	}
	return e;
}

sc_integer timesync_masterIface_sendFollowUp(const Timesync_master* handle){
	s_timeStamp a;
	a = s_clockGetTX_ts();
	int64_t tx = s_ts_to_int(a);
	uint8_t packet[HEADER_LENGTH + sizeof(tx)];
	setDestinationAddress(packet,0xFF);  //address: broadcast
	setSourceAddress(packet,0x00);
	setMessageType(packet,FollowUp);
	setPayload(packet,&tx,sizeof(tx));
	printf("FollowUp %u %u\n",(unsigned)(tx >> 32), (unsigned)(tx&UINT32_MAX));
	return s_radioSendPacket(packet);
}

sc_integer timesync_masterIface_getPeriod(const Timesync_master* handle){
	return (sc_integer)sync_period_multiplier*BASE_SYNC_PERIOD_MS;
}

//! callback implementation for the setting up time events
void timesync_master_setTimer(Timesync_master* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic){
	sc_timer_start(&timer_service, (void*) handle, evid, time_ms, periodic);
}

//! callback implementation for canceling time events.
void timesync_master_unsetTimer(Timesync_master* handle, const sc_eventid evid) {
	sc_timer_cancel(&timer_service, evid);
}

static uint64_t prev_ms;
void s_syncMasterFSMinit() {
	sc_timer_service_init(&timer_service, timers, MAX_TIMERS,
			(sc_raise_time_event_fp) &timesync_master_raiseTimeEvent);
	timesync_master_init(&timesync_masterFSM);
	timesync_master_enter(&timesync_masterFSM);
	prev_ms = s_clockGetMillisecs();
}

void s_syncMasterFSMtask() {
	uint64_t curr_ms = s_clockGetMillisecs();
	uint32_t elapsed = curr_ms - prev_ms;
	if (elapsed != 0){
		sc_timer_service_proceed(&timer_service,elapsed);
	}
	timesync_master_runCycle(&timesync_masterFSM);
	prev_ms = curr_ms;
}
