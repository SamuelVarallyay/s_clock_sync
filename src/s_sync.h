#ifndef S_SYNC_H_
#define S_SYNC_H_

#define BASE_SYNC_PERIOD_MS 500

typedef enum{
	Sync,
	FollowUp,
}package_type;

extern uint8_t sync_period_multiplier;

void setup_prs();

#endif /* S_SYNC_H_ */
