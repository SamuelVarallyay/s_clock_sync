#ifndef S_CLOCK_H_
#define S_CLOCK_H_

#include <stdint.h>
#include "s_clock_config.h"
#include "fixedptc.h"


typedef struct{
	uint64_t ms_whole;
	uint16_t ms_numerator;
	uint16_t ms_denominator;
}s_timeStamp;

void s_clockInit();
void s_clockDriftCorrection(fixedpt drift_per_ms);
void s_clockDriftReset();
bool s_clockIntReadClear();

void s_clockSetMillisecs(uint64_t ms);
void s_clockAddMillisecs(int64_t ms);
void s_clockAddInt(int64_t tick);
uint64_t s_clockGetMillisecs();
s_timeStamp s_clockGetTX_ts();
s_timeStamp s_clockGetRX_ts();

static inline int64_t s_ts_to_int(s_timeStamp a){
	int64_t int_a = (int64_t)(((uint64_t)a.ms_numerator * CLOCK_FREQUENCY_KHZ)/a.ms_denominator);
	int_a += a.ms_whole*CLOCK_FREQUENCY_KHZ;
	return int_a;
}

#endif /* S_CLOCK_H_ */
