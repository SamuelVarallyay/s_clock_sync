
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
static void effect_main_region_Sync_tr0(Master_sc* handle);
static void effect_main_region_FollowUp_tr0(Master_sc* handle);
static void effect_main_region_rx_tr0(Master_sc* handle);
static void enact_main_region_Sync(Master_sc* handle);
static void enact_main_region_FollowUp(Master_sc* handle);
static void enseq_main_region_Sync_default(Master_sc* handle);
static void enseq_main_region_FollowUp_default(Master_sc* handle);
static void enseq_main_region_rx_default(Master_sc* handle);
static void enseq_main_region_default(Master_sc* handle);
static void exseq_main_region_Sync(Master_sc* handle);
static void exseq_main_region_FollowUp(Master_sc* handle);
static void exseq_main_region_rx(Master_sc* handle);
static void exseq_main_region(Master_sc* handle);
static void react_main_region_Sync(Master_sc* handle);
static void react_main_region_FollowUp(Master_sc* handle);
static void react_main_region_rx(Master_sc* handle);
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
		handle->iface.i = 0;
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
		default:
			result = bool_false;
			break;
	}
	return result;
}

static void clearInEvents(Master_sc* handle)
{
	handle->iface.packet_sent_raised = bool_false;
	handle->iface.packet_rx_raised = bool_false;
	handle->iface.tdma_slot_raised = bool_false;
}

static void clearOutEvents(Master_sc* handle)
{
}

void master_scIface_raise_packet_sent(Master_sc* handle)
{
	handle->iface.packet_sent_raised = bool_true;
	
	master_sc_runCycle(handle);
}
void master_scIface_raise_packet_rx(Master_sc* handle)
{
	handle->iface.packet_rx_raised = bool_true;
	
	master_sc_runCycle(handle);
}
void master_scIface_raise_tdma_slot(Master_sc* handle, uint8_t value)
{
	handle->iface.tdma_slot_value = value;
	handle->iface.tdma_slot_raised = bool_true;
	
	master_sc_runCycle(handle);
}


uint8_t master_scIface_get_i(const Master_sc* handle)
{
	return handle->iface.i;
}
void master_scIface_set_i(Master_sc* handle, uint8_t value)
{
	handle->iface.i = value;
}

/* implementations of all internal functions */

static sc_boolean check_main_region_Sync_tr0_tr0(const Master_sc* handle)
{
	return ((handle->iface.tdma_slot_raised) && (handle->iface.tdma_slot_value == 1)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_FollowUp_tr0_tr0(const Master_sc* handle)
{
	return handle->iface.packet_sent_raised;
}

static sc_boolean check_main_region_rx_tr0_tr0(const Master_sc* handle)
{
	return ((handle->iface.tdma_slot_raised) && (handle->iface.tdma_slot_value == 0)) ? bool_true : bool_false;
}

static void effect_main_region_Sync_tr0(Master_sc* handle)
{
	exseq_main_region_Sync(handle);
	enseq_main_region_FollowUp_default(handle);
}

static void effect_main_region_FollowUp_tr0(Master_sc* handle)
{
	exseq_main_region_FollowUp(handle);
	enseq_main_region_rx_default(handle);
}

static void effect_main_region_rx_tr0(Master_sc* handle)
{
	exseq_main_region_rx(handle);
	enseq_main_region_Sync_default(handle);
}

/* Entry action for state 'Sync'. */
static void enact_main_region_Sync(Master_sc* handle)
{
	/* Entry action for state 'Sync'. */
	sendSync();
}

/* Entry action for state 'FollowUp'. */
static void enact_main_region_FollowUp(Master_sc* handle)
{
	/* Entry action for state 'FollowUp'. */
	sendFollowUp();
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
	handle->stateConfVector[0] = Master_sc_main_region_rx;
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

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(Master_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_rx_default(handle);
}


