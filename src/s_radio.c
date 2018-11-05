#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "em_gpio.h"
#include "s_radio.h"
#include "radio-config-wds-gen.h"
#include "ustimer.h"


/* Radio configuration data array. */
static const uint8_t Radio_Configuration_Data_Array[]  = \
  RADIO_CONFIGURATION_DATA_ARRAY;

void s_radioInit() {
	/* Initialize EZRadio device. */

	/* Initialize radio GPIOs and SPI port */

	ezradio_hal_GpioInit(NULL, false);
	ezradio_hal_SpiInit();

	do {
		/* Hardware reset the chip */
		ezradio_reset();

		/* Delay for preconfigured time */
		USTIMER_Init();
		USTIMER_Delay(10000u); //10 ms
		USTIMER_DeInit();

		/* Load radio configuration */
	} while (ezradio_configuration_init(Radio_Configuration_Data_Array)
			!= EZRADIO_CONFIG_SUCCESS);

	/* Read ITs, clear pending ones */
	ezradio_get_int_status_fast_clear_read(NULL);
}
