#include "em_timer.h"
#include "s_clock.h"
#include "em_cmu.h"
#include "em_core.h"


static volatile uint64_t millisecs = 0;
static volatile s_timeStamp rx_time_stamp;
static volatile s_timeStamp tx_time_stamp;
static volatile uint32_t div = CLOCK_FREQUENCY_KHZ;

static volatile fixedpt drift_per_milliseconds = 0;
static volatile fixedpt estimated_offset = 0;

__STATIC_INLINE uint32_t TIMER_CaptureBufGet(TIMER_TypeDef *timer,
		unsigned int ch) {
	return timer->CC[ch].CCVB;
}

volatile bool ovf_int = false;

void s_clockInit() {
	CMU_ClockEnable(cmuClock_S_CLOCK_TIMER, true);
	CMU_ClockEnable(cmuClock_GPIO, true);

	TIMER_InitCC_TypeDef initCC;

	initCC = S_CLOCK_TIMER_INITCC0;
	TIMER_InitCC(S_CLOCK_TIMER, 0, &initCC);

	initCC = S_CLOCK_TIMER_INITCC1;
	TIMER_InitCC(S_CLOCK_TIMER, 1, &initCC);

#ifdef S_CLOCK_TIMER_INITCC2
	initCC = S_CLOCK_TIMER_INITCC2;
	TIMER_InitCC(S_CLOCK_TIMER, 2, &initCC);
#endif
	TIMER_Init_TypeDef init;
	init = S_CLOCK_TIMER_INIT;
	TIMER_Init(S_CLOCK_TIMER, &init);

	TIMER_TopSet(S_CLOCK_TIMER, CLOCK_FREQUENCY_KHZ - 1);

	TIMER_IntEnable(S_CLOCK_TIMER,
	TIMER_IEN_OF | TIMER_IEN_CC0 | TIMER_IEN_CC1);

	NVIC_EnableIRQ(S_CLOCK_TIMER_IRQn);

}

void S_CLOCK_TIMER_IRQHandler(void) {

	uint16_t intFlags = TIMER_IntGet(S_CLOCK_TIMER);

	TIMER_IntClear(S_CLOCK_TIMER, TIMER_IFC_OF | TIMER_IFC_CC0 | TIMER_IFC_CC1);

	bool overflow = intFlags & TIMER_IF_OF;
	bool capture_rx = intFlags & TIMER_IF_CC0;
	bool capture_tx = intFlags & TIMER_IF_CC1;

	if (capture_rx) {
		rx_time_stamp.ms_whole = millisecs;
		rx_time_stamp.ms_numerator = TIMER_CaptureBufGet(S_CLOCK_TIMER, 0);
		rx_time_stamp.ms_denominator = div;
	}
	if (capture_tx) {
		tx_time_stamp.ms_whole = millisecs;
		tx_time_stamp.ms_numerator = TIMER_CaptureBufGet(S_CLOCK_TIMER, 1);
		tx_time_stamp.ms_denominator = div;
	}
	if (overflow) {
		ovf_int = true;
		millisecs = millisecs + 1;
		estimated_offset += drift_per_milliseconds;
		int32_t estimated_offset_floor = fixedpt_toint(estimated_offset);
		div = CLOCK_FREQUENCY_KHZ - estimated_offset_floor;
		estimated_offset = fixedpt_fracpart(estimated_offset);
		uint32_t top = div - 1;
		TIMER_TopSet(S_CLOCK_TIMER, top);
		if (capture_rx
				&& rx_time_stamp.ms_numerator < CLOCK_FREQUENCY_KHZ / 2) {
			rx_time_stamp.ms_whole = millisecs;
			rx_time_stamp.ms_denominator = div;
		}
		if (capture_tx
				&& tx_time_stamp.ms_numerator < CLOCK_FREQUENCY_KHZ / 2) {
			tx_time_stamp.ms_whole = millisecs;
			tx_time_stamp.ms_denominator = div;
		}

	}
}

/**
 * returns true if overflow happened
 */
bool s_clockIntReadClear() {
	bool ret;
	CORE_ATOMIC_SECTION(ret = ovf_int; ovf_int = false;)
	return ret;
}

void s_clockDriftCorrection(fixedpt drift_per_ms) {
	drift_per_milliseconds = drift_per_ms;
}

void s_clockDriftReset() {
	drift_per_milliseconds = 0;
	estimated_offset = 0;
	TIMER_TopSet(S_CLOCK_TIMER, CLOCK_FREQUENCY_KHZ - 1);

}

void s_clockSetMillisecs(uint64_t ms) {
	CORE_irqState_t irqState;
	irqState = CORE_EnterAtomic();
	millisecs = ms;
	CORE_ExitAtomic(irqState);
}

void s_clockAddMillisecs(int64_t ms) {
	CORE_irqState_t irqState;
	irqState = CORE_EnterAtomic();
	millisecs += ms;
	CORE_ExitAtomic(irqState);
}

void s_clockAddInt(int64_t clock_tick){
	int64_t ms = clock_tick/CLOCK_FREQUENCY_KHZ;
	int32_t tick = clock_tick % CLOCK_FREQUENCY_KHZ;
	estimated_offset += fixedpt_fromint(tick);
	millisecs += ms;


}

s_timeStamp s_clockGetRX_ts() {
	return rx_time_stamp;
}

s_timeStamp s_clockGetTX_ts() {
	return tx_time_stamp;
}



uint64_t s_clockGetMillisecs() {
uint64_t ms;
CORE_irqState_t irqState;
irqState = CORE_EnterAtomic();
ms = millisecs;
CORE_ExitAtomic(irqState);
return ms;
}
