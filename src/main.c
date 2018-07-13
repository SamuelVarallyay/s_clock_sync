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
#include "s_sync_master.h"
#include "s_sync_slave.h"
#include "s_sync.h"

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
	if (master) {
		s_syncMasterFSMinit();
		while (1) {
			s_radioLoop();
			s_syncMasterFSMtask();
		}
	} else {
		s_syncSlaveFSMinit();
		while (1) {
			s_radioLoop();
			if (s_clockGetOvfCC()){
				printf("OvfCC");
			}
		}
	}
}
