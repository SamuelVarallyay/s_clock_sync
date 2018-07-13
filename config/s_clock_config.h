#ifndef S_CLOCK_CONFIG_H_
#define S_CLOCK_CONFIG_H_

#include "em_timer.h"

#define CLOCK_FREQUENCY_KHZ 48000

#define S_CLOCK_TIMER TIMER0
#define cmuClock_S_CLOCK_TIMER  cmuClock_TIMER0
#define S_CLOCK_TIMER_IRQn TIMER0_IRQn
#define S_CLOCK_TIMER_IRQHandler TIMER0_IRQHandler

#define S_CLOCK_TIMER_INITCC0            \
(TIMER_InitCC_TypeDef){                  \
  .eventCtrl = timerEventFalling,        \
  .edge      = timerEdgeFalling,         \
  .prsSel    = timerPRSSELCh0,           \
  .cufoa     = timerOutputActionNone,    \
  .cofoa     = timerOutputActionNone,    \
  .cmoa      = timerOutputActionNone,    \
  .mode      = timerCCModeCapture,       \
  .filter    = false,                    \
  .prsInput  = true,                     \
  .coist     = false,                    \
  .outInvert = false                     \
}

#define S_CLOCK_TIMER_INITCC1            \
(TIMER_InitCC_TypeDef){                  \
  .eventCtrl = timerEventFalling,        \
  .edge      = timerEdgeFalling,         \
  .prsSel    = timerPRSSELCh1,           \
  .cufoa     = timerOutputActionNone,    \
  .cofoa     = timerOutputActionNone,    \
  .cmoa      = timerOutputActionNone,    \
  .mode      = timerCCModeCapture,       \
  .filter    = false,                    \
  .prsInput  = true,                     \
  .coist     = false,                    \
  .outInvert = false                     \
}
/*
#define S_CLOCK_TIMER_INITCC2            \
(TIMER_InitCC_TypeDef){                  \
  .eventCtrl = timerEventEveryEdge,      \
  .edge      = timerEdgeNone,            \
  .prsSel    = timerPRSSELCh0,           \
  .cufoa     = timerOutputActionNone,    \
  .cofoa     = timerOutputActionNone,    \
  .cmoa      = timerOutputActionNone,    \
  .mode      = timerCCModeOff,           \
  .filter    = false,                    \
  .prsInput  = false,                    \
  .coist     = false,                    \
  .outInvert = false                     \
}
*/
#define S_CLOCK_TIMER_INIT              \
(TIMER_Init_TypeDef){                   \
  .enable     = 1,                      \
  .debugRun   = 0,                      \
  .prescale   = timerPrescale1,         \
  .clkSel     = timerClkSelHFPerClk,    \
  .count2x    = 0,                      \
  .ati        = 0,                      \
  .fallAction = timerInputActionNone,   \
  .riseAction = timerInputActionNone,   \
  .mode       = timerModeUp,            \
  .dmaClrAct  = 0,                      \
  .quadModeX4 = 0,                      \
  .oneShot    = 0,                      \
  .sync       = 0                       \
}

#endif /* S_CLOCK_CONFIG_H_ */
