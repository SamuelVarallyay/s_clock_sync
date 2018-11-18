
#ifndef MASTER_SC_H_
#define MASTER_SC_H_

#include "sc_types.h"
#include <s_sync.h>
#include "..\model\master.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'master_sc'.
*/

#ifndef MASTER_SC_EVENTQUEUE_BUFFERSIZE
#define MASTER_SC_EVENTQUEUE_BUFFERSIZE 20
#endif
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif
/*! Define dimension of the state configuration vector for orthogonal states. */
#define MASTER_SC_MAX_ORTHOGONAL_STATES 1


/*! Define indices of states in the StateConfVector */
#define SCVI_MASTER_SC_MAIN_REGION_SYNC 0
#define SCVI_MASTER_SC_MAIN_REGION_FOLLOWUP 0
#define SCVI_MASTER_SC_MAIN_REGION_RX 0
#define SCVI_MASTER_SC_MAIN_REGION_INIT 0
#define SCVI_MASTER_SC_MAIN_REGION_SYNC_TIMESTAMP 0
#define SCVI_MASTER_SC_MAIN_REGION_SLOT_START 0


/*! Enumeration of all states */ 
typedef enum
{
	Master_sc_last_state,
	Master_sc_main_region_Sync,
	Master_sc_main_region_FollowUp,
	Master_sc_main_region_rx,
	Master_sc_main_region_init,
	Master_sc_main_region_sync_timestamp,
	Master_sc_main_region_slot_start
} Master_scStates;







/*! Type definition of the data structure for the Master_scIface interface scope. */
typedef struct
{
	sc_boolean packet_sent_raised;
	uint64_t packet_sent_value;
	sc_boolean packet_received_raised;
	uint64_t packet_received_value;
	sc_boolean tdma_slot_raised;
	uint8_t tdma_slot_value;
	uint8_t * rx_packet;
} Master_scIface;



/*! Type definition of the data structure for the Master_scInternal interface scope. */
typedef struct
{
	uint64_t sync_sent_ts;
	uint8_t slave_index;
} Master_scInternal;




/*! 
 * Type definition of the data structure for the Master_sc state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	Master_scStates stateConfVector[MASTER_SC_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	Master_scIface iface;
	Master_scInternal internal;
} Master_sc;



/*! Initializes the Master_sc state machine data structures. Must be called before first usage.*/
extern void master_sc_init(Master_sc* handle);

/*! Activates the state machine */
extern void master_sc_enter(Master_sc* handle);

/*! Deactivates the state machine */
extern void master_sc_exit(Master_sc* handle);

/*! Performs a 'run to completion' step. */
extern void master_sc_runCycle(Master_sc* handle);


/*! Raises the in event 'packet_sent' that is defined in the default interface scope. */ 
extern void master_scIface_raise_packet_sent(Master_sc* handle, uint64_t value);

/*! Raises the in event 'packet_received' that is defined in the default interface scope. */ 
extern void master_scIface_raise_packet_received(Master_sc* handle, uint64_t value);

/*! Raises the in event 'tdma_slot' that is defined in the default interface scope. */ 
extern void master_scIface_raise_tdma_slot(Master_sc* handle, uint8_t value);

/*! Gets the value of the variable 'rx_packet' that is defined in the default interface scope. */ 
extern uint8_t * master_scIface_get_rx_packet(const Master_sc* handle);
/*! Sets the value of the variable 'rx_packet' that is defined in the default interface scope. */ 
extern void master_scIface_set_rx_packet(Master_sc* handle, uint8_t * value);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean master_sc_isActive(const Master_sc* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean master_sc_isFinal(const Master_sc* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean master_sc_isStateActive(const Master_sc* handle, Master_scStates state);


#ifdef __cplusplus
}
#endif 

#endif /* MASTER_SC_H_ */
