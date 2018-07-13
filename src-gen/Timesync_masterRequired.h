
#ifndef TIMESYNC_MASTERREQUIRED_H_
#define TIMESYNC_MASTERREQUIRED_H_

#include "..\src\sc_types.h"
#include "Timesync_master.h"

#ifdef __cplusplus
extern "C"
{
#endif 

/*! \file This header defines prototypes for all functions that are required by the state machine implementation.

This is a state machine uses time events which require access to a timing service. Thus the function prototypes:
	- timesync_master_setTimer and
	- timesync_master_unsetTimer
are defined.

This state machine makes use of operations declared in the state machines interface or internal scopes. Thus the function prototypes:
	- timesync_masterIface_sendSync
	- timesync_masterIface_sendFollowUp
	- timesync_masterIface_getPeriod
are defined.

These functions will be called during a 'run to completion step' (runCycle) of the statechart. 
There are some constraints that have to be considered for the implementation of these functions:
	- never call the statechart API functions from within these functions.
	- make sure that the execution time is as short as possible.
 
*/
extern sc_integer timesync_masterIface_sendSync(const Timesync_master* handle);
extern sc_integer timesync_masterIface_sendFollowUp(const Timesync_master* handle);
extern sc_integer timesync_masterIface_getPeriod(const Timesync_master* handle);


/*!
 * This is a timed state machine that requires timer services
 */ 

/*! This function has to set up timers for the time events that are required by the state machine. */
/*! 
	This function will be called for each time event that is relevant for a state when a state will be entered.
	\param evid An unique identifier of the event.
	\time_ms The time in milli seconds
	\periodic Indicates the the time event must be raised periodically until the timer is unset 
*/
extern void timesync_master_setTimer(Timesync_master* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic);

/*! This function has to unset timers for the time events that are required by the state machine. */
/*! 
	This function will be called for each time event taht is relevant for a state when a state will be left.
	\param evid An unique identifier of the event.
*/
extern void timesync_master_unsetTimer(Timesync_master* handle, const sc_eventid evid);



#ifdef __cplusplus
}
#endif 

#endif /* TIMESYNC_MASTERREQUIRED_H_ */
