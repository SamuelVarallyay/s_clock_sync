/*
 * controller.h
 *
 *  Created on: 2018. okt. 29.
 *      Author: Samu
 */

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

typedef struct{
	float Kp;
	float Ki;
	float I;
}PIcontroller_t;

void PIcontroller(PIcontroller_t* ctrl, float input);

#endif /* SRC_CONTROLLER_H_ */
