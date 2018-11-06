/*
 * master.c
 *
 *  Created on: 2018. okt. 8.
 *      Author: Samu
 */

#include <stdio.h>
#include <stdint.h>
#include "s_clock.h"
#include "s_radio.h"
#include "s_sync.h"
#include "tdma_params.h"

sync_data_t* sync_data;
void init_master(sync_data_t* syncdata){
	sync_data = syncdata;
}

void sendSync(){
	printf("Sync ");
	packet_t packet = (const packet_t){ 0 };
	packet.source = 0;
	packet.type = 0;
	packet.cycle_start_ms = sync_data->cycle_start_ms;
	ezradio_write_tx_fifo(64, (uint8_t*)&packet);

	ezradio_start_tx(0, 0x30, 0);
//	ezradio_start_tx_fast();

}
void sendFollowUp(){
	printf("FoUp ");
	s_timeStamp ts = s_clockGetTX_ts();
	ts.ms_whole -= sync_data->cycle_start_ms;

	int64_t tx = s_ts_to_int(ts);
	printf("%d ",(int)tx);

	packet_t packet = (const packet_t){ 0 };
	packet.source = 0;
	packet.type = 1;
	packet.sync_master = tx;	//source (master=0)

	ezradio_write_tx_fifo(64, (uint8_t*)&packet);

	ezradio_start_tx(0, 0x30, 0u);
}

