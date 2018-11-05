/*
 * master.c
 *
 *  Created on: 2018. okt. 8.
 *      Author: Samu
 */


#include "s_clock.h"
#include "s_radio.h"

void sendSync(){
	printf("Sync ");
	uint8_t packet[2];
	packet[0]=2;	//length
	packet[1]=0;	//source (master=0)
	ezradio_set_property(EZRADIO_PROP_GRP_ID_PKT, 2u,
			EZRADIO_PROP_GRP_INDEX_PKT_FIELD_1_LENGTH, 0, 2);

	ezradio_write_tx_fifo(2, packet);

	ezradio_start_tx(0, 0x30, 0);
//	ezradio_start_tx_fast();

}
void sendFollowUp(){
	printf("FoUp ");
	int64_t tx = s_ts_to_int(s_clockGetTX_ts());
	uint8_t packet[11];
	packet[0]=11;	//length
	packet[1]=0;	//source (master=0)
	memcpy(packet+2,&tx,sizeof(tx));
	ezradio_set_property(EZRADIO_PROP_GRP_ID_PKT, 2u,
			EZRADIO_PROP_GRP_INDEX_PKT_FIELD_1_LENGTH, 0, 11);

	ezradio_write_tx_fifo(11, packet);

	ezradio_start_tx(0, 0x30, 0u);
}

