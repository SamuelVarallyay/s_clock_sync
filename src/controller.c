/*
 * controller.c
 *
 *  Created on: 2018. okt. 29.
 *      Author: Samu
 */
	float Kp = 1/4;
	float Ki = 1/16;

#include "controller.h"

void PIcontroller(PIcontroller_t* ctrl,float input){
	float P = input;
	ctrl->I = ctrl->I + input;

	float output = ctrl->Kp * P + ctrl->Ki * ctrl->I;
}
