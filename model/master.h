/*
 * master.h
 *
 *  Created on: 2018. okt. 15.
 *      Author: Samu
 */

#ifndef MODEL_MASTER_H_
#define MODEL_MASTER_H_

#include "s_sync.h"

void init_master(sync_data_t* syncdata);
void sendSync();
void sendFollowUp();

#endif /* MODEL_MASTER_H_ */
