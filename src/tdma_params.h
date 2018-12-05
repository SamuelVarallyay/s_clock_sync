/*
 * protocol_params.h
 *
 *  Created on: 2018. okt. 7.
 *      Author: Samu
 */

#ifndef MODEL_TDMA_PARAMS_H_
#define MODEL_TDMA_PARAMS_H_

#define SLOT_NUMBER 16
#define SLOT_LENGTH 16 //ms
#define FRAME_LENGTH (SLOT_NUMBER * SLOT_LENGTH)
#define MAX_SLAVE_NUMBER (SLOT_NUMBER-2)

#endif /* MODEL_TDMA_PARAMS_H_ */
