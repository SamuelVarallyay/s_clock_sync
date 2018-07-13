#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ezradio_cmd.h"
#include "ezradio_api_lib.h"
#include "ezradio_prop.h"
#include "ezradio_plugin_manager.h"
#include "ezradio_receive_plugin.h"
#include "ezradio_transmit_plugin.h"
#include "s_radio.h"
#include "em_gpio.h"

uint8_t own_address = 0;

/* EZRadio driver init data and handler */
EZRADIODRV_HandleData_t appRadioInitData = EZRADIODRV_INIT_DEFAULT;
EZRADIODRV_Handle_t appRadioHandle = &appRadioInitData;

/* EZRadio response structure union */
ezradio_cmd_reply_t ezradioReply;

/* Rx packet data array */
static uint8_t radioRxPkt[EZRADIO_FIFO_SIZE];
static rx_Callback_t rxCallbacks[128] = {NULL};
static void_Callback_t txCallback = NULL;

bool appTxActive = false;

void s_radioSetTxCallback(void_Callback_t callback){
	txCallback = callback;
}

void s_radioSetRxCallback(uint8_t msg_type, rx_Callback_t callback){
	rxCallbacks[msg_type] = callback;
}

static void appPacketTransmittedCallback(EZRADIODRV_Handle_t handle, Ecode_t status) {
	appTxActive = false;
	ezradioStartRx(handle);
	if (txCallback != NULL ) {
		txCallback();
	}
}

static void appPacketReceivedCallback(EZRADIODRV_Handle_t handle, Ecode_t status) {
	if (getDestinationAddress(radioRxPkt) == 0xFF
			|| getDestinationAddress(radioRxPkt) == own_address) {
		rx_Callback_t rxCallback = rxCallbacks[getMessageType(radioRxPkt)];
		if (rxCallback != NULL) {
			rxCallback(radioRxPkt);
		}
	}
}

void s_radioInit() {
	/* Initialize EZRadio device. */
	appRadioInitData.packetRx.pktBuf = radioRxPkt;
	appRadioInitData.packetTx.userCallback = appPacketTransmittedCallback;
	appRadioInitData.packetRx.userCallback = appPacketReceivedCallback;
	ezradioInit(appRadioHandle);
	/* Reset radio fifos and start reception. */
	ezradioResetTRxFifo();
	ezradioStartRx(appRadioHandle);
	GPIO_PinModeSet(gpioPortF, 8, gpioModePushPull, 0);
}
void s_radioLoop(){
	ezradioPluginManager(appRadioHandle);
}
Ecode_t s_radioSendPacket(uint8_t *pioRadioPacket){
	if (appTxActive){
		return ECODE_EMDRV_EZRADIODRV_TRANSMIT_FAILED;
	}
	appTxActive = true;
	GPIO_PinOutSet(gpioPortF, 8);
	GPIO_PinOutClear(gpioPortF, 8);
	GPIO_PinOutSet(gpioPortF, 8);
	GPIO_PinOutClear(gpioPortF, 8);
	GPIO_PinOutSet(gpioPortF, 8);
	GPIO_PinOutClear(gpioPortF, 8);
	ezradio_set_property(EZRADIO_PROP_GRP_ID_PKT, 2u,
	                         EZRADIO_PROP_GRP_INDEX_PKT_FIELD_1_LENGTH,
	                         0, pioRadioPacket[FIELD_LENGTH]
	                         );
	GPIO_PinOutSet(gpioPortF, 8);
	GPIO_PinOutClear(gpioPortF, 8);
	GPIO_PinOutSet(gpioPortF, 8);
	GPIO_PinOutClear(gpioPortF, 8);
	ezradio_write_tx_fifo(pioRadioPacket[FIELD_LENGTH], pioRadioPacket);
	GPIO_PinOutSet(gpioPortF, 8);
	ezradio_start_tx(0, 0x30, 0u);
	GPIO_PinOutClear(gpioPortF, 8);
	return ECODE_OK;

//	return ezradioStartTransmitBasic(appRadioHandle, pioRadioPacket[FIELD_LENGTH], pioRadioPacket);
}
