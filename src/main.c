#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spidrv.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "gpiointerrupt.h"

#include "s_clock.h"
#include "s_radio.h"
#include "Master_sc.h"
#include "Slave_sc.h"

#include "tdma_params.h"
#include "debug_wire.h"

#include "retargetserial.h"

#if !defined(__CROSSWORKS_ARM) && defined(__GNUC__)
/* sniprintf does not process floats, but occupy less flash memory ! */
#define snprintf    sniprintf
#endif


/**************************************************************************//**
 * @brief  Main function of the example.
 *****************************************************************************/
int main(void) {

	/* Chip errata */
	CHIP_Init();

	/* HFXO 48MHz, divided by 1 */
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);

	CMU_ClockEnable(cmuClock_GPIO, true);
	GPIOINT_Init();

	/* Initialize LEUART/USART and map LF to CRLF */
	RETARGET_SerialInit();
	RETARGET_SerialCrLf(0);

	uint32_t uniqueID = DEVINFO->UNIQUEL;
	bool master = uniqueID == 0x790ab;

	//0x79105, 0x79384, 0x78fb0


	Master_sc master_sc;
	Slave_sc slave_sc;
	uint8_t rx_packet[64];

	setup_prs();
	s_radioInit();
	s_clockInit();
	debugWireInit();

	/* Print header */
	printf("Clock Sync init\r\n");
	printf("UIDL: 0x%08x\r\n", (unsigned) uniqueID);
	if (master) {
		printf("Master\r\n");
		master_sc_init(&master_sc);
		master_scIface_set_rx_packet(&master_sc,rx_packet);
		master_sc_enter(&master_sc);
	} else {
		printf("Slave\r\n");
		uint8_t slot_id;
		switch(uniqueID){
		case 0x79105:
			slot_id = 2;
			break;
		case 0x78fb0:
			slot_id = 3;
			break;
		case 0x79384:
			slot_id = 15;
			break;
		default:
			break;
		}
		slave_sc_init(&slave_sc);
		slave_scIface_set_rx_packet(&slave_sc,rx_packet);
		slave_scIface_set_own_id(&slave_sc,slot_id);
		slave_scIface_set_own_slot(&slave_sc,slot_id);
		slave_sc_enter(&slave_sc);
	}


	int32_t slot_num = 0;

	while(1){
		if(s_clockIntReadClear()){

			int64_t ms = s_clockGetMillisecs();
			if (ms % SLOT_LENGTH == 0){
				debugWireSet();
				slot_num = (ms / SLOT_LENGTH) % SLOT_NUMBER;
				if (master){
					switch (slot_num){
					case 0:
						debugWireClear();
						debugWireSet();
						master_scIface_raise_sync_slot(&master_sc);
						break;
					case 1:
						master_scIface_raise_followup_slot(&master_sc);
						break;
					default:
						master_scIface_raise_slave_slot(&master_sc,slot_num);
						break;
					}
				}else{
					switch (slot_num) {
					case 0:
						debugWireClear();
						debugWireSet();
						slave_scIface_set_sensor_ts(&slave_sc, s_ts_to_int(s_clockGetSensor_ts()));
						slave_scIface_raise_sync_slot(&slave_sc);
						break;
					case 1:
						slave_scIface_raise_followup_slot(&slave_sc);
						break;
					default:
						slave_scIface_raise_slave_slot(&slave_sc,slot_num);
						break;
					}
				}
				debugWireClear();
			}

		}
		/*NIRQ is active low*/
		if(0 == ezradio_hal_NirqLevel()){
			ezradio_cmd_reply_t interrupt_status;
			ezradio_get_int_status_fast_clear_read(&interrupt_status);
			if(interrupt_status.GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT){
				if (master) {
					master_scIface_raise_packet_sent(&master_sc,s_ts_to_int(s_clockGetTX_ts()));
				}else{
					slave_scIface_raise_packet_sent(&slave_sc,s_ts_to_int(s_clockGetTX_ts()));
				}
			}
			if(interrupt_status.GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT){
				debugWireSet();
				debugWireClear();
				debugWireSet();
				ezradio_read_rx_fifo(64, rx_packet);
				debugWireClear();
				debugWireSet();
				if (master) {
					master_scIface_raise_packet_received(&master_sc,s_ts_to_int(s_clockGetRX_ts()));
				}else{
					slave_scIface_raise_packet_received(&slave_sc,s_ts_to_int(s_clockGetRX_ts()));
				}
				debugWireClear();
			}
			if(interrupt_status.GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_CRC_ERROR_PEND_BIT){

			}
		}

	}
}
