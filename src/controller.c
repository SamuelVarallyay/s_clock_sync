/*
 * controller.c
 *
 *  Created on: 2018. okt. 29.
 *      Author: Samu
 */

#include "controller.h"

float PIcontroller(PIcontroller_t* ctrl,float input){
	float P  = ctrl->Kp * input;
	ctrl->I += ctrl->Ki * input;

	return  P + ctrl->I;
}
