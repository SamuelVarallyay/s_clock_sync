/*
 * master.h
 *
 *  Created on: 2018. okt. 15.
 *      Author: Samu
 */

#ifndef MODEL_MASTER_H_
#define MODEL_MASTER_H_

#include "s_sync.h"
#include "tdma_params.h"

/* the time stamp of the reception of the slave messages
 * relative to the transmission of the SYNC message */
int32_t relative_slave_ts[MAX_SLAVE_NUMBER];

uint8_t followup_packet[64];
uint8_t sync_packet[64];

#endif /* MODEL_MASTER_H_ */
