/*
 * debug_wire.h
 *
 *  Created on: 2018. nov. 27.
 *      Author: Samu
 */

#ifndef SRC_DEBUG_WIRE_H_
#define SRC_DEBUG_WIRE_H_

#include "em_gpio.h"

// P37
#define DBG_WIRE_PORT gpioPortF
#define DBG_WIRE_PIN  8

#define debugWireInit() GPIO_PinModeSet(DBG_WIRE_PORT,DBG_WIRE_PIN,gpioModePushPull,0u)
#define debugWireSet() GPIO_PinOutSet(DBG_WIRE_PORT,DBG_WIRE_PIN)
#define debugWireGet() GPIO_PinOutGet(DBG_WIRE_PORT,DBG_WIRE_PIN)
#define debugWireClear() GPIO_PinOutClear(DBG_WIRE_PORT,DBG_WIRE_PIN)
#define debugWireToggle() GPIO_PinOutToggle(DBG_WIRE_PORT,DBG_WIRE_PIN)

#endif /* SRC_DEBUG_WIRE_H_ */
