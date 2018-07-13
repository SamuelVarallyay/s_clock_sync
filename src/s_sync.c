#include <stdint.h>
#include <stdlib.h>
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_prs.h"
#include "s_clock.h"
#include "s_radio.h"
#include "s_sync.h"

uint8_t sync_period_multiplier = 1;

void setup_prs(){
    /* Setup PRS */
	CMU_ClockEnable(cmuClock_PRS, true);

	/* Configure RF_GPIO0 and RF_GPIO1 to inputs. */
	GPIO_PinModeSet((GPIO_Port_TypeDef) RF_GPIO0_PORT, RF_GPIO0_PIN, gpioModeInput, 0);
	GPIO_PinModeSet((GPIO_Port_TypeDef) RF_GPIO1_PORT, RF_GPIO1_PIN, gpioModeInput, 0);

	/* Pin PA0 and PA1 output the GPIO0 and GPIO1 via PRS to breakout pad*/
	GPIO_PinModeSet(gpioPortA, 0, gpioModePushPull, 0);
	GPIO_PinModeSet(gpioPortA, 1, gpioModePushPull, 0);

	/* Disable INT for PRS channels */
	GPIO_IntConfig((GPIO_Port_TypeDef) RF_GPIO0_PORT, RF_GPIO0_PIN, false, false, false);
	GPIO_IntConfig((GPIO_Port_TypeDef) RF_GPIO1_PORT, RF_GPIO1_PIN, false, false, false);

	/* Setup PRS for RF GPIO pins  */
	PRS_SourceAsyncSignalSet(0, PRS_CH_CTRL_SOURCESEL_GPIOH, PRS_CH_CTRL_SIGSEL_GPIOPIN15);
	PRS_SourceAsyncSignalSet(1, PRS_CH_CTRL_SOURCESEL_GPIOH, PRS_CH_CTRL_SIGSEL_GPIOPIN14);
	PRS ->ROUTE = (PRS_ROUTE_CH0PEN | PRS_ROUTE_CH1PEN);

	/* Make sure PRS sensing is enabled (should be by default) */
	GPIO_InputSenseSet(GPIO_INSENSE_PRS, GPIO_INSENSE_PRS);
}

