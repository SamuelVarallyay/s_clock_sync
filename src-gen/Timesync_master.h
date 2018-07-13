
#ifndef TIMESYNC_MASTER_H_
#define TIMESYNC_MASTER_H_

#include "..\src\sc_types.h"
		
#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'timesync_master'.
*/


/*! Enumeration of all states */ 
typedef enum
{
	Timesync_master_last_state,
	Timesync_master_sync_SendSync,
	Timesync_master_sync_S2,
	Timesync_master_sync_S2_r1_wait,
	Timesync_master_sync_S2_r1_ready,
	Timesync_master_sync_S2_r1_SendFollowUp,
	Timesync_master_sync_S2_r2_wait,
	Timesync_master_sync_S2_r2_ready
} Timesync_masterStates;

/*! Type definition of the data structure for the Timesync_masterIface interface scope. */
typedef struct
{
	sc_boolean syncSent_raised;
	sc_integer t;
	sc_integer errorCode;
} Timesync_masterIface;

/*! Type definition of the data structure for the Timesync_masterTimeEvents interface scope. */
typedef struct
{
	sc_boolean timesync_master_sync_S2_r2_wait_tev0_raised;
} Timesync_masterTimeEvents;


/*! Define dimension of the state configuration vector for orthogonal states. */
#define TIMESYNC_MASTER_MAX_ORTHOGONAL_STATES 2

/*! Define maximum number of time events that can be active at once */
#define TIMESYNC_MASTER_MAX_PARALLEL_TIME_EVENTS 1

/*! Define indices of states in the StateConfVector */
#define SCVI_TIMESYNC_MASTER_SYNC_SENDSYNC 0
#define SCVI_TIMESYNC_MASTER_SYNC_S2 0
#define SCVI_TIMESYNC_MASTER_SYNC_S2_R1_WAIT 0
#define SCVI_TIMESYNC_MASTER_SYNC_S2_R1_READY 0
#define SCVI_TIMESYNC_MASTER_SYNC_S2_R1_SENDFOLLOWUP 0
#define SCVI_TIMESYNC_MASTER_SYNC_S2_R2_WAIT 1
#define SCVI_TIMESYNC_MASTER_SYNC_S2_R2_READY 1

/*! 
 * Type definition of the data structure for the Timesync_master state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	Timesync_masterStates stateConfVector[TIMESYNC_MASTER_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	Timesync_masterIface iface;
	Timesync_masterTimeEvents timeEvents;
} Timesync_master;


/*! Initializes the Timesync_master state machine data structures. Must be called before first usage.*/
extern void timesync_master_init(Timesync_master* handle);

/*! Activates the state machine */
extern void timesync_master_enter(Timesync_master* handle);

/*! Deactivates the state machine */
extern void timesync_master_exit(Timesync_master* handle);

/*! Performs a 'run to completion' step. */
extern void timesync_master_runCycle(Timesync_master* handle);

/*! Raises a time event. */
extern void timesync_master_raiseTimeEvent(const Timesync_master* handle, sc_eventid evid);

/*! Raises the in event 'syncSent' that is defined in the default interface scope. */ 
extern void timesync_masterIface_raise_syncSent(Timesync_master* handle);

/*! Gets the value of the variable 't' that is defined in the default interface scope. */ 
extern sc_integer timesync_masterIface_get_t(const Timesync_master* handle);
/*! Sets the value of the variable 't' that is defined in the default interface scope. */ 
extern void timesync_masterIface_set_t(Timesync_master* handle, sc_integer value);
/*! Gets the value of the variable 'errorCode' that is defined in the default interface scope. */ 
extern sc_integer timesync_masterIface_get_errorCode(const Timesync_master* handle);
/*! Sets the value of the variable 'errorCode' that is defined in the default interface scope. */ 
extern void timesync_masterIface_set_errorCode(Timesync_master* handle, sc_integer value);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean timesync_master_isActive(const Timesync_master* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean timesync_master_isFinal(const Timesync_master* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean timesync_master_isStateActive(const Timesync_master* handle, Timesync_masterStates state);



#ifdef __cplusplus
}
#endif 

#endif /* TIMESYNC_MASTER_H_ */
