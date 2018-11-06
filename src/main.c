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

	/* Print header */
	printf("Clock Sync init\n");
	printf("UIDL: 0x%08x\n", (unsigned) DEVINFO->UNIQUEL);
	if (master) {
		printf("Master\n");
	} else {
		printf("Slave\n");
	}


	setup_prs();
	s_radioInit();
	s_clockInit();

	sync_data_t sync_data = (const sync_data_t){0};
	sync_data.delay = -1500;

	init_master(sync_data_t* sync_data);
	Master_sc master_sc;
	master_sc_init(&master_sc);
	master_sc_enter(&master_sc);

	uint32_t slot_num = 0;

	packet_t rx_packet;

	while(1){
		if(s_clockIntReadClear()){
			uint64_t ms = s_clockGetMillisecs();
			if (ms % SLOT_LENGTH == 0){
				slot_num = (ms / SLOT_LENGTH) % SLOT_NUMBER;
				if (slot_num == 0){
					sync_data.cycle_start_ms = ms;
				}
				master_scIface_raise_tdma_slot(&master_sc, slot_num);
			}
		}
		/*NIRQ is active low*/
		if(0 == ezradio_hal_NirqLevel()){
			ezradio_cmd_reply_t interrupt_status;
			ezradio_get_int_status_fast_clear_read(&interrupt_status);
			if(interrupt_status.GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT){
				printf("packet_sent\n");
				master_scIface_raise_packet_sent(&master_sc);
			}
			if(interrupt_status.GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT){
				ezradio_read_rx_fifo(64, (uint8_t*)&rx_packet);

				if(rx_packet.source == 0){
					if(rx_packet.type == 0){

					}else{

					}
				}
				master_scIface_raise_packet_rx(&master_sc);
			}
			if(interrupt_status.GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_CRC_ERROR_PEND_BIT){

			}
		}
	}
}
