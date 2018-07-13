
#ifndef TIMESYNC_SLAVE_H_
#define TIMESYNC_SLAVE_H_

#include "..\src\sc_types.h"
		
#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'timesync_slave'.
*/


/*! Enumeration of all states */ 
typedef enum
{
	Timesync_slave_last_state,
	Timesync_slave_sync_a
} Timesync_slaveStates;


/*! Define dimension of the state configuration vector for orthogonal states. */
#define TIMESYNC_SLAVE_MAX_ORTHOGONAL_STATES 1


/*! Define indices of states in the StateConfVector */
#define SCVI_TIMESYNC_SLAVE_SYNC_A 0

/*! 
 * Type definition of the data structure for the Timesync_slave state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	Timesync_slaveStates stateConfVector[TIMESYNC_SLAVE_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
} Timesync_slave;


/*! Initializes the Timesync_slave state machine data structures. Must be called before first usage.*/
extern void timesync_slave_init(Timesync_slave* handle);

/*! Activates the state machine */
extern void timesync_slave_enter(Timesync_slave* handle);

/*! Deactivates the state machine */
extern void timesync_slave_exit(Timesync_slave* handle);

/*! Performs a 'run to completion' step. */
extern void timesync_slave_runCycle(Timesync_slave* handle);



/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean timesync_slave_isActive(const Timesync_slave* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean timesync_slave_isFinal(const Timesync_slave* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean timesync_slave_isStateActive(const Timesync_slave* handle, Timesync_slaveStates state);



#ifdef __cplusplus
}
#endif 

#endif /* TIMESYNC_SLAVE_H_ */
