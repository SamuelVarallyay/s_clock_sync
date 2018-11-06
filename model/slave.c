/*
 * slave.c
 *
 *  Created on: 2018. okt. 28.
 *      Author: Samu
 */

#include <stdio.h>
#include <stdint.h>
#include "s_clock.h"
#include "s_radio.h"
#include "s_sync.h"
#include "tdma_params.h"

sync_data_t* sync_data;
void init_slave(sync_data_t* syncdata){
	sync_data = syncdata;
}

