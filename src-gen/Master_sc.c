
#include "Master_sc.h"
#include "sc_types.h"

#include <stdlib.h>
#include <string.h>
/*! \file Implementation of the state machine 'master_sc'
*/

/* prototypes of all internal functions */
static sc_boolean check_main_region_Sync_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_FollowUp_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_rx_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_init_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_sync_timestamp_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_slot_start_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_slot_start_tr1_tr1(const Master_sc* handle);
static sc_boolean check_main_region__choice_0_tr1_tr1(const Master_sc* handle);
static sc_boolean check_main_region__choice_0_tr0_tr0(const Master_sc* handle);
static void effect_main_region_Sync_tr0(Master_sc* handle);
static void effect_main_region_FollowUp_tr0(Master_sc* handle);
static void effect_main_region_rx_tr0(Master_sc* handle);
static void effect_main_region_init_tr0(Master_sc* handle);
static void effect_main_region_sync_timestamp_tr0(Master_sc* handle);
static void effect_main_region_slot_start_tr0(Master_sc* handle);
static void effect_main_region_slot_start_tr1(Master_sc* handle);
static void effect_main_region__choice_0_tr1(Master_sc* handle);
static void effect_main_region__choice_0_tr0(Master_sc* handle);
static void enact_main_region_Sync(Master_sc* handle);
static void enact_main_region_FollowUp(Master_sc* handle);
static void enact_main_region_rx(Master_sc* handle);
static void enact_main_region_init(Master_sc* handle);
static void enact_main_region_sync_timestamp(Master_sc* handle);
static void enact_main_region_slot_start(Master_sc* handle);
static void enseq_main_region_Sync_default(Master_sc* handle);
static void enseq_main_region_FollowUp_default(Master_sc* handle);
static void enseq_main_region_rx_default(Master_sc* handle);
static void enseq_main_region_init_default(Master_sc* handle);
static void enseq_main_region_sync_timestamp_default(Master_sc* handle);
static void enseq_main_region_slot_start_default(Master_sc* handle);
static void enseq_main_region_default(Master_sc* handle);
static void exseq_main_region_Sync(Master_sc* handle);
static void exseq_main_region_FollowUp(Master_sc* handle);
static void exseq_main_region_rx(Master_sc* handle);
static void exseq_main_region_init(Master_sc* handle);
static void exseq_main_region_sync_timestamp(Master_sc* handle);
static void exseq_main_region_slot_start(Master_sc* handle);
static void exseq_main_region(Master_sc* handle);
static void react_main_region_Sync(Master_sc* handle);
static void react_main_region_FollowUp(Master_sc* handle);
static void react_main_region_rx(Master_sc* handle);
static void react_main_region_init(Master_sc* handle);
static void react_main_region_sync_timestamp(Master_sc* handle);
static void react_main_region_slot_start(Master_sc* handle);
static void react_main_region__choice_0(Master_sc* handle);
static void react_main_region__entry_Default(Master_sc* handle);
static void clearInEvents(Master_sc* handle);
static void clearOutEvents(Master_sc* handle);


void master_sc_init(Master_sc* handle)
{
		sc_integer i;
	
		for (i = 0; i < MASTER_SC_MAX_ORTHOGONAL_STATES; ++i)
		{
			handle->stateConfVector[i] = Master_sc_last_state;
		}
		
		
		handle->stateConfVectorPosition = 0;
	
		clearInEvents(handle);
		clearOutEvents(handle);
	
		/* Default init sequence for statechart master_sc */
		handle->internal.sync_sent_ts = 0;
		handle->internal.slave_index = 0;
}

void master_sc_enter(Master_sc* handle)
{
	/* Default enter sequence for statechart master_sc */
	enseq_main_region_default(handle);
}

void master_sc_runCycle(Master_sc* handle)
{
	clearOutEvents(handle);
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < MASTER_SC_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case Master_sc_main_region_Sync:
		{
			react_main_region_Sync(handle);
			break;
		}
		case Master_sc_main_region_FollowUp:
		{
			react_main_region_FollowUp(handle);
			break;
		}
		case Master_sc_main_region_rx:
		{
			react_main_region_rx(handle);
			break;
		}
		case Master_sc_main_region_init:
		{
			react_main_region_init(handle);
			break;
		}
		case Master_sc_main_region_sync_timestamp:
		{
			react_main_region_sync_timestamp(handle);
			break;
		}
		case Master_sc_main_region_slot_start:
		{
			react_main_region_slot_start(handle);
			break;
		}
		default:
			break;
		}
	}
	
	clearInEvents(handle);
}

void master_sc_exit(Master_sc* handle)
{
	/* Default exit sequence for statechart master_sc */
	exseq_main_region(handle);
}

sc_boolean master_sc_isActive(const Master_sc* handle)
{
	sc_boolean result = bool_false;
	int i;
	
	for(i = 0; i < MASTER_SC_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Master_sc_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean master_sc_isFinal(const Master_sc* handle)
{
   return bool_false;
}

sc_boolean master_sc_isStateActive(const Master_sc* handle, Master_scStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Master_sc_main_region_Sync :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC] == Master_sc_main_region_Sync
			);
			break;
		case Master_sc_main_region_FollowUp :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_FOLLOWUP] == Master_sc_main_region_FollowUp
			);
			break;
		case Master_sc_main_region_rx :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_RX] == Master_sc_main_region_rx
			);
			break;
		case Master_sc_main_region_init :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_INIT] == Master_sc_main_region_init
			);
			break;
		case Master_sc_main_region_sync_timestamp :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC_TIMESTAMP] == Master_sc_main_region_sync_timestamp
			);
			break;
		case Master_sc_main_region_slot_start :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SLOT_START] == Master_sc_main_region_slot_start
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}

static void clearInEvents(Master_sc* handle)
{
	handle->iface.packet_sent_raised = bool_false;
	handle->iface.packet_received_raised = bool_false;
	handle->iface.tdma_slot_raised = bool_false;
}

static void clearOutEvents(Master_sc* handle)
{
}

void master_scIface_raise_packet_sent(Master_sc* handle, uint64_t value)
{
	handle->iface.packet_sent_value = value;
	handle->iface.packet_sent_raised = bool_true;
	
	master_sc_runCycle(handle);
}
void master_scIface_raise_packet_received(Master_sc* handle, uint64_t value)
{
	handle->iface.packet_received_value = value;
	handle->iface.packet_received_raised = bool_true;
	
	master_sc_runCycle(handle);
}
void master_scIface_raise_tdma_slot(Master_sc* handle, uint8_t value)
{
	handle->iface.tdma_slot_value = value;
	handle->iface.tdma_slot_raised = bool_true;
	
	master_sc_runCycle(handle);
}


uint8_t * master_scIface_get_rx_packet(const Master_sc* handle)
{
	return handle->iface.rx_packet;
}
void master_scIface_set_rx_packet(Master_sc* handle, uint8_t * value)
{
	handle->iface.rx_packet = value;
}

/* implementations of all internal functions */

static sc_boolean check_main_region_Sync_tr0_tr0(const Master_sc* handle)
{
	return handle->iface.packet_sent_raised;
}

static sc_boolean check_main_region_FollowUp_tr0_tr0(const Master_sc* handle)
{
	return handle->iface.tdma_slot_raised;
}

static sc_boolean check_main_region_rx_tr0_tr0(const Master_sc* handle)
{
	return handle->iface.tdma_slot_raised;
}

static sc_boolean check_main_region_init_tr0_tr0(const Master_sc* handle)
{
	return ((handle->iface.tdma_slot_raised) && (handle->iface.tdma_slot_value == 0)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_sync_timestamp_tr0_tr0(const Master_sc* handle)
{
	return ((handle->iface.tdma_slot_raised) && (handle->iface.tdma_slot_value == 1)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_slot_start_tr0_tr0(const Master_sc* handle)
{
	return handle->iface.packet_received_raised;
}

static sc_boolean check_main_region_slot_start_tr1_tr1(const Master_sc* handle)
{
	return handle->iface.tdma_slot_raised;
}

static sc_boolean check_main_region__choice_0_tr1_tr1(const Master_sc* handle)
{
	return (handle->iface.tdma_slot_value == 0) ? bool_true : bool_false;
}

static sc_boolean check_main_region__choice_0_tr0_tr0(const Master_sc* handle)
{
	return bool_true;
}

static void effect_main_region_Sync_tr0(Master_sc* handle)
{
	exseq_main_region_Sync(handle);
	enseq_main_region_sync_timestamp_default(handle);
}

static void effect_main_region_FollowUp_tr0(Master_sc* handle)
{
	exseq_main_region_FollowUp(handle);
	enseq_main_region_slot_start_default(handle);
}

static void effect_main_region_rx_tr0(Master_sc* handle)
{
	exseq_main_region_rx(handle);
	react_main_region__choice_0(handle);
}

static void effect_main_region_init_tr0(Master_sc* handle)
{
	exseq_main_region_init(handle);
	enseq_main_region_Sync_default(handle);
}

static void effect_main_region_sync_timestamp_tr0(Master_sc* handle)
{
	exseq_main_region_sync_timestamp(handle);
	enseq_main_region_FollowUp_default(handle);
}

static void effect_main_region_slot_start_tr0(Master_sc* handle)
{
	exseq_main_region_slot_start(handle);
	enseq_main_region_rx_default(handle);
}

static void effect_main_region_slot_start_tr1(Master_sc* handle)
{
	exseq_main_region_slot_start(handle);
	react_main_region__choice_0(handle);
}

static void effect_main_region__choice_0_tr1(Master_sc* handle)
{
	enseq_main_region_Sync_default(handle);
}

static void effect_main_region__choice_0_tr0(Master_sc* handle)
{
	enseq_main_region_slot_start_default(handle);
}

/* Entry action for state 'Sync'. */
static void enact_main_region_Sync(Master_sc* handle)
{
	/* Entry action for state 'Sync'. */
	sendPacket(sync_packet);
}

/* Entry action for state 'FollowUp'. */
static void enact_main_region_FollowUp(Master_sc* handle)
{
	/* Entry action for state 'FollowUp'. */
	sendPacket(followup_packet);
}

/* Entry action for state 'rx'. */
static void enact_main_region_rx(Master_sc* handle)
{
	/* Entry action for state 'rx'. */
	relative_slave_ts[handle->internal.slave_index] = ((uint32_t) (handle->iface.packet_received_value - handle->internal.sync_sent_ts));
	setDelayResp(sync_packet, relative_slave_ts[handle->internal.slave_index], handle->internal.slave_index);
}

/* Entry action for state 'init'. */
static void enact_main_region_init(Master_sc* handle)
{
	/* Entry action for state 'init'. */
	setSourceAddress(sync_packet, 0);
	setPacketType(sync_packet, SYNC);
	setSourceAddress(followup_packet, 0);
	setPacketType(followup_packet, FOLLOW_UP);
}

/* Entry action for state 'sync timestamp'. */
static void enact_main_region_sync_timestamp(Master_sc* handle)
{
	/* Entry action for state 'sync timestamp'. */
	handle->internal.sync_sent_ts = handle->iface.packet_sent_value;
	setSyncTimeStamp(followup_packet, handle->internal.sync_sent_ts);
}

/* Entry action for state 'slot start'. */
static void enact_main_region_slot_start(Master_sc* handle)
{
	/* Entry action for state 'slot start'. */
	handle->internal.slave_index = handle->iface.tdma_slot_value - 2;
	startRx();
	relative_slave_ts[handle->internal.slave_index] = 0;
	setDelayResp(sync_packet, 0, handle->internal.slave_index);
}

/* 'default' enter sequence for state Sync */
static void enseq_main_region_Sync_default(Master_sc* handle)
{
	/* 'default' enter sequence for state Sync */
	enact_main_region_Sync(handle);
	handle->stateConfVector[0] = Master_sc_main_region_Sync;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state FollowUp */
static void enseq_main_region_FollowUp_default(Master_sc* handle)
{
	/* 'default' enter sequence for state FollowUp */
	enact_main_region_FollowUp(handle);
	handle->stateConfVector[0] = Master_sc_main_region_FollowUp;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state rx */
static void enseq_main_region_rx_default(Master_sc* handle)
{
	/* 'default' enter sequence for state rx */
	enact_main_region_rx(handle);
	handle->stateConfVector[0] = Master_sc_main_region_rx;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state init */
static void enseq_main_region_init_default(Master_sc* handle)
{
	/* 'default' enter sequence for state init */
	enact_main_region_init(handle);
	handle->stateConfVector[0] = Master_sc_main_region_init;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state sync timestamp */
static void enseq_main_region_sync_timestamp_default(Master_sc* handle)
{
	/* 'default' enter sequence for state sync timestamp */
	enact_main_region_sync_timestamp(handle);
	handle->stateConfVector[0] = Master_sc_main_region_sync_timestamp;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state slot start */
static void enseq_main_region_slot_start_default(Master_sc* handle)
{
	/* 'default' enter sequence for state slot start */
	enact_main_region_slot_start(handle);
	handle->stateConfVector[0] = Master_sc_main_region_slot_start;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(Master_sc* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
}

/* Default exit sequence for state Sync */
static void exseq_main_region_Sync(Master_sc* handle)
{
	/* Default exit sequence for state Sync */
	handle->stateConfVector[0] = Master_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state FollowUp */
static void exseq_main_region_FollowUp(Master_sc* handle)
{
	/* Default exit sequence for state FollowUp */
	handle->stateConfVector[0] = Master_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state rx */
static void exseq_main_region_rx(Master_sc* handle)
{
	/* Default exit sequence for state rx */
	handle->stateConfVector[0] = Master_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state init */
static void exseq_main_region_init(Master_sc* handle)
{
	/* Default exit sequence for state init */
	handle->stateConfVector[0] = Master_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state sync timestamp */
static void exseq_main_region_sync_timestamp(Master_sc* handle)
{
	/* Default exit sequence for state sync timestamp */
	handle->stateConfVector[0] = Master_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state slot start */
static void exseq_main_region_slot_start(Master_sc* handle)
{
	/* Default exit sequence for state slot start */
	handle->stateConfVector[0] = Master_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
static void exseq_main_region(Master_sc* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of master_sc.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Master_sc_main_region_Sync :
		{
			exseq_main_region_Sync(handle);
			break;
		}
		case Master_sc_main_region_FollowUp :
		{
			exseq_main_region_FollowUp(handle);
			break;
		}
		case Master_sc_main_region_rx :
		{
			exseq_main_region_rx(handle);
			break;
		}
		case Master_sc_main_region_init :
		{
			exseq_main_region_init(handle);
			break;
		}
		case Master_sc_main_region_sync_timestamp :
		{
			exseq_main_region_sync_timestamp(handle);
			break;
		}
		case Master_sc_main_region_slot_start :
		{
			exseq_main_region_slot_start(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state Sync. */
static void react_main_region_Sync(Master_sc* handle)
{
	/* The reactions of state Sync. */
	if (check_main_region_Sync_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_Sync_tr0(handle);
	} 
}

/* The reactions of state FollowUp. */
static void react_main_region_FollowUp(Master_sc* handle)
{
	/* The reactions of state FollowUp. */
	if (check_main_region_FollowUp_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_FollowUp_tr0(handle);
	} 
}

/* The reactions of state rx. */
static void react_main_region_rx(Master_sc* handle)
{
	/* The reactions of state rx. */
	if (check_main_region_rx_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_rx_tr0(handle);
	} 
}

/* The reactions of state init. */
static void react_main_region_init(Master_sc* handle)
{
	/* The reactions of state init. */
	if (check_main_region_init_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_init_tr0(handle);
	} 
}

/* The reactions of state sync timestamp. */
static void react_main_region_sync_timestamp(Master_sc* handle)
{
	/* The reactions of state sync timestamp. */
	if (check_main_region_sync_timestamp_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_sync_timestamp_tr0(handle);
	} 
}

/* The reactions of state slot start. */
static void react_main_region_slot_start(Master_sc* handle)
{
	/* The reactions of state slot start. */
	if (check_main_region_slot_start_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_slot_start_tr0(handle);
	}  else
	{
		if (check_main_region_slot_start_tr1_tr1(handle) == bool_true)
		{ 
			effect_main_region_slot_start_tr1(handle);
		} 
	}
}

/* The reactions of state null. */
static void react_main_region__choice_0(Master_sc* handle)
{
	/* The reactions of state null. */
	if (check_main_region__choice_0_tr1_tr1(handle) == bool_true)
	{ 
		effect_main_region__choice_0_tr1(handle);
	}  else
	{
		effect_main_region__choice_0_tr0(handle);
	}
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(Master_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_init_default(handle);
}


