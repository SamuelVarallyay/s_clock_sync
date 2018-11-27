
#ifndef SLAVE_SC_H_
#define SLAVE_SC_H_

#include "sc_types.h"
#include <s_clock.h>
#include <controller.h>
#include "..\model\slave.h"
#include <s_sync.h>
#include <fixedptc.h>
#include <tdma_params.h>

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'slave_sc'.
*/

#ifndef SLAVE_SC_EVENTQUEUE_BUFFERSIZE
#define SLAVE_SC_EVENTQUEUE_BUFFERSIZE 20
#endif
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif
/*! Define dimension of the state configuration vector for orthogonal states. */
#define SLAVE_SC_MAX_ORTHOGONAL_STATES 4


/*! Define indices of states in the StateConfVector */
#define SCVI_SLAVE_SC_MAIN_REGION_INIT 0
#define SCVI_SLAVE_SC_MAIN_REGION_WAIT_FOR_FOLLOWUP 0
#define SCVI_SLAVE_SC_MAIN_REGION_CYCLE 0
#define SCVI_SLAVE_SC_MAIN_REGION_CYCLE_TBMA_ACTIVE 0
#define SCVI_SLAVE_SC_MAIN_REGION_CYCLE_RESPONSE_RESPONSE 1
#define SCVI_SLAVE_SC_MAIN_REGION_CYCLE_RESPONSE_TIMEDIFF 1
#define SCVI_SLAVE_SC_MAIN_REGION_CYCLE_SYNC_WAIT_FOR_SYNC 2
#define SCVI_SLAVE_SC_MAIN_REGION_CYCLE_FOLLOWUP_WAIT_FOR_2_FOLLOWUP 3
#define SCVI_SLAVE_SC_MAIN_REGION_CYCLE_FOLLOWUP_WAIT 3
#define SCVI_SLAVE_SC_MAIN_REGION_WAIT_FOR_SYNC 0


/*
 * Enum of event names in the statechart.
 */
typedef enum  {
	slave_sc_invalid_event = SC_INVALID_EVENT_VALUE,
	slave_scInternal_slave_slot,
	slave_scInternal_sync_slot,
	slave_scInternal_followup_slot
} slave_sc_event_name;

/*
 * Struct that represents a single event.
 */
typedef struct {
	slave_sc_event_name name;
} slave_sc_internal_event;

/*
 * Queue that holds the raised events.
 */
typedef struct slave_sc_eventqueue_s {
	slave_sc_internal_event events[SLAVE_SC_EVENTQUEUE_BUFFERSIZE];
	sc_integer pop_index;
	sc_integer push_index;
	sc_integer size;
} slave_sc_eventqueue;
/*! Enumeration of all states */ 
typedef enum
{
	Slave_sc_last_state,
	Slave_sc_main_region_init,
	Slave_sc_main_region_wait_for_followup,
	Slave_sc_main_region_cycle,
	Slave_sc_main_region_cycle_tbma_active,
	Slave_sc_main_region_cycle_response_response,
	Slave_sc_main_region_cycle_response_timediff,
	Slave_sc_main_region_cycle_sync_wait_for_sync,
	Slave_sc_main_region_cycle_followup_wait_for_2_followup,
	Slave_sc_main_region_cycle_followup_wait,
	Slave_sc_main_region_wait_for_sync
} Slave_scStates;













/*! Type definition of the data structure for the Slave_scIface interface scope. */
typedef struct
{
	sc_boolean packet_sent_raised;
	int64_t packet_sent_value;
	sc_boolean packet_received_raised;
	int64_t packet_received_value;
	sc_boolean tdma_slot_raised;
	uint8_t tdma_slot_value;
	sc_boolean tdma_slot_prepare_raised;
	uint8_t tdma_slot_prepare_value;
	uint8_t * rx_packet;
	uint8_t slave_index;
} Slave_scIface;



/*! Type definition of the data structure for the Slave_scInternal interface scope. */
typedef struct
{
	sc_boolean slave_slot_raised;
	sc_boolean sync_slot_raised;
	sc_boolean followup_slot_raised;
	int64_t sync_tx_ts;
	int64_t sync_rx_ts;
	int32_t slave_time_diff;
	int32_t master_time_diff;
	int64_t offset;
	int32_t delay;
	PIcontroller_t PIctrl;
	float drift;
} Slave_scInternal;




/*! 
 * Type definition of the data structure for the Slave_sc state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	Slave_scStates stateConfVector[SLAVE_SC_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	Slave_scIface iface;
	Slave_scInternal internal;
	slave_sc_eventqueue internal_event_queue;
} Slave_sc;



/*! Initializes the Slave_sc state machine data structures. Must be called before first usage.*/
extern void slave_sc_init(Slave_sc* handle);

/*! Activates the state machine */
extern void slave_sc_enter(Slave_sc* handle);

/*! Deactivates the state machine */
extern void slave_sc_exit(Slave_sc* handle);

/*! Performs a 'run to completion' step. */
extern void slave_sc_runCycle(Slave_sc* handle);


/*! Raises the in event 'packet_sent' that is defined in the default interface scope. */ 
extern void slave_scIface_raise_packet_sent(Slave_sc* handle, int64_t value);

/*! Raises the in event 'packet_received' that is defined in the default interface scope. */ 
extern void slave_scIface_raise_packet_received(Slave_sc* handle, int64_t value);

/*! Raises the in event 'tdma_slot' that is defined in the default interface scope. */ 
extern void slave_scIface_raise_tdma_slot(Slave_sc* handle, uint8_t value);

/*! Raises the in event 'tdma_slot_prepare' that is defined in the default interface scope. */ 
extern void slave_scIface_raise_tdma_slot_prepare(Slave_sc* handle, uint8_t value);

/*! Gets the value of the variable 'rx_packet' that is defined in the default interface scope. */ 
extern uint8_t * slave_scIface_get_rx_packet(const Slave_sc* handle);
/*! Sets the value of the variable 'rx_packet' that is defined in the default interface scope. */ 
extern void slave_scIface_set_rx_packet(Slave_sc* handle, uint8_t * value);
/*! Gets the value of the variable 'slave_index' that is defined in the default interface scope. */ 
extern uint8_t slave_scIface_get_slave_index(const Slave_sc* handle);
/*! Sets the value of the variable 'slave_index' that is defined in the default interface scope. */ 
extern void slave_scIface_set_slave_index(Slave_sc* handle, uint8_t value);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean slave_sc_isActive(const Slave_sc* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean slave_sc_isFinal(const Slave_sc* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean slave_sc_isStateActive(const Slave_sc* handle, Slave_scStates state);


#ifdef __cplusplus
}
#endif 

#endif /* SLAVE_SC_H_ */
