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
#include "s_sync.h"
#include "tdma_params.h"

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
	RETARGET_SerialCrLf(1);

	bool master = DEVINFO->UNIQUEL == 0x790ab;

	Master_sc master_sc;
	Slave_sc slave_sc;
	uint8_t rx_packet[64];

	setup_prs();
	s_radioInit();
	s_clockInit();

	/* Print header */
	printf("Clock Sync init\n");
	printf("UIDL: 0x%08x\n", (unsigned) DEVINFO->UNIQUEL);
	if (master) {
		printf("Master\n");
		master_sc_init(&master_sc);
		master_scIface_set_rx_packet(&master_sc,rx_packet);
		master_sc_enter(&master_sc);
	} else {
		printf("Slave\n");
		slave_sc_init(&slave_sc);
		slave_scIface_set_rx_packet(&slave_sc,rx_packet);
		slave_scIface_set_slave_index(&slave_sc,0);
		slave_sc_enter(&slave_sc);
	}


	int32_t slot_num = 0;

	while(1){
		if(s_clockIntReadClear()){
			uint64_t ms = s_clockGetMillisecs();
			if (ms % SLOT_LENGTH == 0){
				slot_num = (ms / SLOT_LENGTH) % SLOT_NUMBER;
				if (master) {
					master_scIface_raise_tdma_slot(&master_sc, slot_num);
				}else{
					slave_scIface_raise_tdma_slot(&slave_sc, slot_num);
				}
			}
		}
		/*NIRQ is active low*/
		if(0 == ezradio_hal_NirqLevel()){
			ezradio_cmd_reply_t interrupt_status;
			ezradio_get_int_status_fast_clear_read(&interrupt_status);
			if(interrupt_status.GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT){
				printf("packet_sent\n");
				if (master) {
					master_scIface_raise_packet_sent(&master_sc,s_ts_to_int(s_clockGetTX_ts()));
				}else{
					slave_scIface_raise_packet_sent(&slave_sc,s_ts_to_int(s_clockGetTX_ts()));
				}
			}
			if(interrupt_status.GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT){
				ezradio_read_rx_fifo(64, rx_packet);
				if (master) {
					master_scIface_raise_packet_received(&master_sc,s_ts_to_int(s_clockGetTX_ts()));
				}else{
					slave_scIface_raise_packet_received(&slave_sc,s_ts_to_int(s_clockGetTX_ts()));
				}
			}
			if(interrupt_status.GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_CRC_ERROR_PEND_BIT){

			}
		}
	}
}
