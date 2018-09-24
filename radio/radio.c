#if 0
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ezradio_cmd.h"
#include "ezradio_api_lib.h"
#include "ezradio_prop.h"
#include "em_gpio.h"
#include "radio.h"
#include "radio-config-wds-gen.h"


/* Radio configuration data array. */
static const uint8_t Radio_Configuration_Data_Array[]  = \
  RADIO_CONFIGURATION_DATA_ARRAY;


void s_radioInit() {
	/* Initialize EZRadio device. */

	  /* Initialize radio GPIOs and SPI port */

	  ezradio_hal_GpioInit(NULL, false);
	  ezradio_hal_SpiInit();

	  /* Hardware reset the chip */
	  ezradio_reset();

	  /* Delay for preconfigured time */
	  USTIMER_Init();
	  USTIMER_Delay(10000u); //10 ms
	  USTIMER_DeInit();

	  /* Load radio configuration */
	  while (EZRADIO_CONFIG_SUCCESS != ezradio_configuration_init(Radio_Configuration_Data_Array)) {
	    /* Error hook */
	    printf("ERROR: Radio configuration failed!\n");

	    /* Delay for 10ms time */
	    USTIMER_Init();
	    USTIMER_Delay(10000u);
	    USTIMER_DeInit();

	    ezradio_reset();

	    /* Delay for 10ms time */
	    USTIMER_Init();
	    USTIMER_Delay(10000u);
	    USTIMER_DeInit();
	  }

	  /* Read ITs, clear pending ones */
	  ezradio_get_int_status(0u, 0u, 0u, NULL);
}

void radio_task(){
	/*NIRQ is active low*/
	if(0 == ezradio_hal_NirqLevel()){
		ezradio_cmd_reply_t interrupt_status;
		ezradio_get_int_status_fast_clear_read(&interrupt_status);
	}
}

Ecode_t s_radioSendPacket(uint8_t *pioRadioPacket){
	if (appTxActive){
		return ECODE_EMDRV_EZRADIODRV_TRANSMIT_FAILED;
	}
	appTxActive = true;

	ezradio_set_property(EZRADIO_PROP_GRP_ID_PKT, 2u,
	                         EZRADIO_PROP_GRP_INDEX_PKT_FIELD_1_LENGTH,
	                         0, pioRadioPacket[FIELD_LENGTH]
	                         );

	ezradio_write_tx_fifo(pioRadioPacket[FIELD_LENGTH], pioRadioPacket);

	ezradio_start_tx(0, 0x30, 0u);

	return ECODE_OK;

//	return ezradioStartTransmitBasic(appRadioHandle, pioRadioPacket[FIELD_LENGTH], pioRadioPacket);
}

#endif
