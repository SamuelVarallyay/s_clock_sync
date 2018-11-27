
#include "Master_sc.h"
#include "sc_types.h"

#include <stdlib.h>
#include <string.h>
/*! \file Implementation of the state machine 'master_sc'
*/

/* prototypes of all internal functions */
static sc_boolean check_main_region_init_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_sync_tdma_active_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_sync_Sync_slot_Sync_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_sync_Sync_slot_wait_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_sync_Follow_up_slot_Follow_Up_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_sync_Follow_up_slot_wait_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_sync_slave_wait_slave_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_sync_slave_start_lave_slot_tr0_tr0(const Master_sc* handle);
static sc_boolean check_main_region_sync_slave_start_lave_slot_tr1_tr1(const Master_sc* handle);
static sc_boolean check_main_region_sync_slave_start_lave_slot_tr2_tr2(const Master_sc* handle);
static sc_boolean check_main_region_sync_tdma__choice_0_tr1_tr1(const Master_sc* handle);
static sc_boolean check_main_region_sync_tdma__choice_0_tr2_tr2(const Master_sc* handle);
static sc_boolean check_main_region_sync_tdma__choice_0_tr0_tr0(const Master_sc* handle);
static void effect_main_region_init_tr0(Master_sc* handle);
static void effect_main_region_sync_tdma_active_tr0(Master_sc* handle);
static void effect_main_region_sync_Sync_slot_Sync_tr0(Master_sc* handle);
static void effect_main_region_sync_Sync_slot_wait_tr0(Master_sc* handle);
static void effect_main_region_sync_Follow_up_slot_Follow_Up_tr0(Master_sc* handle);
static void effect_main_region_sync_Follow_up_slot_wait_tr0(Master_sc* handle);
static void effect_main_region_sync_slave_wait_slave_tr0(Master_sc* handle);
static void effect_main_region_sync_slave_start_lave_slot_tr0(Master_sc* handle);
static void effect_main_region_sync_slave_start_lave_slot_tr1(Master_sc* handle);
static void effect_main_region_sync_slave_start_lave_slot_tr2(Master_sc* handle);
static void effect_main_region_sync_tdma__choice_0_tr1(Master_sc* handle);
static void effect_main_region_sync_tdma__choice_0_tr2(Master_sc* handle);
static void effect_main_region_sync_tdma__choice_0_tr0(Master_sc* handle);
static void enact_main_region_init(Master_sc* handle);
static void enact_main_region_sync_slave_start_lave_slot(Master_sc* handle);
static void enseq_main_region_init_default(Master_sc* handle);
static void enseq_main_region_sync_default(Master_sc* handle);
static void enseq_main_region_sync_tdma_active_default(Master_sc* handle);
static void enseq_main_region_sync_Sync_slot_Sync_default(Master_sc* handle);
static void enseq_main_region_sync_Sync_slot_wait_default(Master_sc* handle);
static void enseq_main_region_sync_Follow_up_slot_Follow_Up_default(Master_sc* handle);
static void enseq_main_region_sync_Follow_up_slot_wait_default(Master_sc* handle);
static void enseq_main_region_sync_slave_wait_slave_default(Master_sc* handle);
static void enseq_main_region_sync_slave_start_lave_slot_default(Master_sc* handle);
static void enseq_main_region_default(Master_sc* handle);
static void enseq_main_region_sync_tdma_default(Master_sc* handle);
static void enseq_main_region_sync_Sync_slot_default(Master_sc* handle);
static void enseq_main_region_sync_Follow_up_slot_default(Master_sc* handle);
static void enseq_main_region_sync_slave_default(Master_sc* handle);
static void exseq_main_region_init(Master_sc* handle);
static void exseq_main_region_sync_tdma_active(Master_sc* handle);
static void exseq_main_region_sync_Sync_slot_Sync(Master_sc* handle);
static void exseq_main_region_sync_Sync_slot_wait(Master_sc* handle);
static void exseq_main_region_sync_Follow_up_slot_Follow_Up(Master_sc* handle);
static void exseq_main_region_sync_Follow_up_slot_wait(Master_sc* handle);
static void exseq_main_region_sync_slave_wait_slave(Master_sc* handle);
static void exseq_main_region_sync_slave_start_lave_slot(Master_sc* handle);
static void exseq_main_region(Master_sc* handle);
static void exseq_main_region_sync_tdma(Master_sc* handle);
static void exseq_main_region_sync_Sync_slot(Master_sc* handle);
static void exseq_main_region_sync_Follow_up_slot(Master_sc* handle);
static void exseq_main_region_sync_slave(Master_sc* handle);
static void react_main_region_init(Master_sc* handle);
static void react_main_region_sync_tdma_active(Master_sc* handle);
static void react_main_region_sync_Sync_slot_Sync(Master_sc* handle);
static void react_main_region_sync_Sync_slot_wait(Master_sc* handle);
static void react_main_region_sync_Follow_up_slot_Follow_Up(Master_sc* handle);
static void react_main_region_sync_Follow_up_slot_wait(Master_sc* handle);
static void react_main_region_sync_slave_wait_slave(Master_sc* handle);
static void react_main_region_sync_slave_start_lave_slot(Master_sc* handle);
static void react_main_region_sync_tdma__choice_0(Master_sc* handle);
static void react_main_region__entry_Default(Master_sc* handle);
static void react_main_region_sync_tdma__entry_Default(Master_sc* handle);
static void react_main_region_sync_Sync_slot__entry_Default(Master_sc* handle);
static void react_main_region_sync_Follow_up_slot__entry_Default(Master_sc* handle);
static void react_main_region_sync_slave__entry_Default(Master_sc* handle);
static void clearInEvents(Master_sc* handle);
static void clearOutEvents(Master_sc* handle);
static void master_sc_eventqueue_init(master_sc_eventqueue * eq);
static sc_integer master_sc_eventqueue_size(master_sc_eventqueue * eq);
static master_sc_internal_event master_sc_eventqueue_pop(master_sc_eventqueue * eq);
static sc_boolean master_sc_eventqueue_push(master_sc_eventqueue * eq, master_sc_internal_event ev);

static void master_sc_dispatch_event(Master_sc* handle, const master_sc_internal_event * event);

static void master_sc_internal_event_init(master_sc_internal_event * ev, master_sc_event_name name);
static void master_sc_add_event_to_queue(Master_sc* handle, master_sc_event_name name);


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
		handle->internal.sync_tx_ts = 0;
		handle->internal.slave_index = 0;
	master_sc_eventqueue_init(&(handle->internal_event_queue));
}

void master_sc_enter(Master_sc* handle)
{
	/* Default enter sequence for statechart master_sc */
	enseq_main_region_default(handle);
}

void master_sc_runCycle(Master_sc* handle)
{
	clearOutEvents(handle);
	
	master_sc_internal_event currentEvent = master_sc_eventqueue_pop(&(handle->internal_event_queue));
	
	do {
		master_sc_dispatch_event(handle, &currentEvent);
		for (handle->stateConfVectorPosition = 0;
			handle->stateConfVectorPosition < MASTER_SC_MAX_ORTHOGONAL_STATES;
			handle->stateConfVectorPosition++)
			{
				
			switch (handle->stateConfVector[handle->stateConfVectorPosition])
			{
			case Master_sc_main_region_init:
			{
				react_main_region_init(handle);
				break;
			}
			case Master_sc_main_region_sync_tdma_active:
			{
				react_main_region_sync_tdma_active(handle);
				break;
			}
			case Master_sc_main_region_sync_Sync_slot_Sync:
			{
				react_main_region_sync_Sync_slot_Sync(handle);
				break;
			}
			case Master_sc_main_region_sync_Sync_slot_wait:
			{
				react_main_region_sync_Sync_slot_wait(handle);
				break;
			}
			case Master_sc_main_region_sync_Follow_up_slot_Follow_Up:
			{
				react_main_region_sync_Follow_up_slot_Follow_Up(handle);
				break;
			}
			case Master_sc_main_region_sync_Follow_up_slot_wait:
			{
				react_main_region_sync_Follow_up_slot_wait(handle);
				break;
			}
			case Master_sc_main_region_sync_slave_wait_slave:
			{
				react_main_region_sync_slave_wait_slave(handle);
				break;
			}
			case Master_sc_main_region_sync_slave_start_lave_slot:
			{
				react_main_region_sync_slave_start_lave_slot(handle);
				break;
			}
			default:
				break;
			}
		}
		
		clearInEvents(handle);
	} while((currentEvent = master_sc_eventqueue_pop(&(handle->internal_event_queue))).name != master_sc_invalid_event);
	
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
		case Master_sc_main_region_init :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_INIT] == Master_sc_main_region_init
			);
			break;
		case Master_sc_main_region_sync :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC] >= Master_sc_main_region_sync
				&& handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC] <= Master_sc_main_region_sync_slave_start_lave_slot);
			break;
		case Master_sc_main_region_sync_tdma_active :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC_TDMA_ACTIVE] == Master_sc_main_region_sync_tdma_active
			);
			break;
		case Master_sc_main_region_sync_Sync_slot_Sync :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC_SYNC_SLOT_SYNC] == Master_sc_main_region_sync_Sync_slot_Sync
			);
			break;
		case Master_sc_main_region_sync_Sync_slot_wait :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC_SYNC_SLOT_WAIT] == Master_sc_main_region_sync_Sync_slot_wait
			);
			break;
		case Master_sc_main_region_sync_Follow_up_slot_Follow_Up :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC_FOLLOW_UP_SLOT_FOLLOW_UP] == Master_sc_main_region_sync_Follow_up_slot_Follow_Up
			);
			break;
		case Master_sc_main_region_sync_Follow_up_slot_wait :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC_FOLLOW_UP_SLOT_WAIT] == Master_sc_main_region_sync_Follow_up_slot_wait
			);
			break;
		case Master_sc_main_region_sync_slave_wait_slave :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC_SLAVE_WAIT_SLAVE] == Master_sc_main_region_sync_slave_wait_slave
			);
			break;
		case Master_sc_main_region_sync_slave_start_lave_slot :
			result = (sc_boolean) (handle->stateConfVector[SCVI_MASTER_SC_MAIN_REGION_SYNC_SLAVE_START_LAVE_SLOT] == Master_sc_main_region_sync_slave_start_lave_slot
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
	handle->internal.slave_slot_raised = bool_false;
	handle->internal.sync_slot_raised = bool_false;
	handle->internal.followup_slot_raised = bool_false;
}

static void clearOutEvents(Master_sc* handle)
{
}

void master_scIface_raise_packet_sent(Master_sc* handle, int64_t value)
{
	handle->iface.packet_sent_value = value;
	handle->iface.packet_sent_raised = bool_true;
	
	master_sc_runCycle(handle);
}
void master_scIface_raise_packet_received(Master_sc* handle, int64_t value)
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

static sc_boolean check_main_region_init_tr0_tr0(const Master_sc* handle)
{
	return bool_true;
}

static sc_boolean check_main_region_sync_tdma_active_tr0_tr0(const Master_sc* handle)
{
	return handle->iface.tdma_slot_raised;
}

static sc_boolean check_main_region_sync_Sync_slot_Sync_tr0_tr0(const Master_sc* handle)
{
	return handle->iface.packet_sent_raised;
}

static sc_boolean check_main_region_sync_Sync_slot_wait_tr0_tr0(const Master_sc* handle)
{
	return handle->internal.sync_slot_raised;
}

static sc_boolean check_main_region_sync_Follow_up_slot_Follow_Up_tr0_tr0(const Master_sc* handle)
{
	return handle->iface.packet_sent_raised;
}

static sc_boolean check_main_region_sync_Follow_up_slot_wait_tr0_tr0(const Master_sc* handle)
{
	return handle->internal.followup_slot_raised;
}

static sc_boolean check_main_region_sync_slave_wait_slave_tr0_tr0(const Master_sc* handle)
{
	return handle->internal.slave_slot_raised;
}

static sc_boolean check_main_region_sync_slave_start_lave_slot_tr0_tr0(const Master_sc* handle)
{
	return handle->iface.packet_received_raised;
}

static sc_boolean check_main_region_sync_slave_start_lave_slot_tr1_tr1(const Master_sc* handle)
{
	return handle->internal.slave_slot_raised;
}

static sc_boolean check_main_region_sync_slave_start_lave_slot_tr2_tr2(const Master_sc* handle)
{
	return handle->internal.followup_slot_raised;
}

static sc_boolean check_main_region_sync_tdma__choice_0_tr1_tr1(const Master_sc* handle)
{
	return (handle->iface.tdma_slot_value == 0) ? bool_true : bool_false;
}

static sc_boolean check_main_region_sync_tdma__choice_0_tr2_tr2(const Master_sc* handle)
{
	return (handle->iface.tdma_slot_value == 1) ? bool_true : bool_false;
}

static sc_boolean check_main_region_sync_tdma__choice_0_tr0_tr0(const Master_sc* handle)
{
	return bool_true;
}

static void effect_main_region_init_tr0(Master_sc* handle)
{
	exseq_main_region_init(handle);
	enseq_main_region_sync_default(handle);
}

static void effect_main_region_sync_tdma_active_tr0(Master_sc* handle)
{
	exseq_main_region_sync_tdma_active(handle);
	react_main_region_sync_tdma__choice_0(handle);
}

static void effect_main_region_sync_Sync_slot_Sync_tr0(Master_sc* handle)
{
	exseq_main_region_sync_Sync_slot_Sync(handle);
	handle->internal.sync_tx_ts = handle->iface.packet_sent_value;
	setSyncTimeStamp(followup_packet, handle->internal.sync_tx_ts);
	enseq_main_region_sync_Sync_slot_wait_default(handle);
}

static void effect_main_region_sync_Sync_slot_wait_tr0(Master_sc* handle)
{
	exseq_main_region_sync_Sync_slot_wait(handle);
	sendPacket(sync_packet);
	enseq_main_region_sync_Sync_slot_Sync_default(handle);
}

static void effect_main_region_sync_Follow_up_slot_Follow_Up_tr0(Master_sc* handle)
{
	exseq_main_region_sync_Follow_up_slot_Follow_Up(handle);
	enseq_main_region_sync_Follow_up_slot_wait_default(handle);
}

static void effect_main_region_sync_Follow_up_slot_wait_tr0(Master_sc* handle)
{
	exseq_main_region_sync_Follow_up_slot_wait(handle);
	sendPacket(followup_packet);
	enseq_main_region_sync_Follow_up_slot_Follow_Up_default(handle);
}

static void effect_main_region_sync_slave_wait_slave_tr0(Master_sc* handle)
{
	exseq_main_region_sync_slave_wait_slave(handle);
	enseq_main_region_sync_slave_start_lave_slot_default(handle);
}

static void effect_main_region_sync_slave_start_lave_slot_tr0(Master_sc* handle)
{
	exseq_main_region_sync_slave_start_lave_slot(handle);
	relative_slave_ts[handle->internal.slave_index] = ((int32_t) (handle->iface.packet_received_value - handle->internal.sync_tx_ts));
	setDelayResp(sync_packet, relative_slave_ts[handle->internal.slave_index], handle->internal.slave_index);
	enseq_main_region_sync_slave_wait_slave_default(handle);
}

static void effect_main_region_sync_slave_start_lave_slot_tr1(Master_sc* handle)
{
	exseq_main_region_sync_slave_start_lave_slot(handle);
	enseq_main_region_sync_slave_start_lave_slot_default(handle);
}

static void effect_main_region_sync_slave_start_lave_slot_tr2(Master_sc* handle)
{
	exseq_main_region_sync_slave_start_lave_slot(handle);
	enseq_main_region_sync_slave_wait_slave_default(handle);
}

static void effect_main_region_sync_tdma__choice_0_tr1(Master_sc* handle)
{
	master_sc_add_event_to_queue(handle, master_scInternal_sync_slot);
	enseq_main_region_sync_tdma_active_default(handle);
}

static void effect_main_region_sync_tdma__choice_0_tr2(Master_sc* handle)
{
	master_sc_add_event_to_queue(handle, master_scInternal_followup_slot);
	enseq_main_region_sync_tdma_active_default(handle);
}

static void effect_main_region_sync_tdma__choice_0_tr0(Master_sc* handle)
{
	handle->internal.slave_index = handle->iface.tdma_slot_value - 2;
	master_sc_add_event_to_queue(handle, master_scInternal_slave_slot);
	enseq_main_region_sync_tdma_active_default(handle);
}

/* Entry action for state 'init'. */
static void enact_main_region_init(Master_sc* handle)
{
	/* Entry action for state 'init'. */
	setSourceAddress(sync_packet, 0);
	setPacketType(sync_packet, SYNC);
	setSourceAddress(followup_packet, 0);
	setPacketType(followup_packet, FOLLOW_UP);
	handle->internal.slave_index = 0;
}

/* Entry action for state 'start lave slot'. */
static void enact_main_region_sync_slave_start_lave_slot(Master_sc* handle)
{
	/* Entry action for state 'start lave slot'. */
	startRx();
	relative_slave_ts[handle->internal.slave_index] = 0;
	setDelayResp(sync_packet, 0, handle->internal.slave_index);
}

/* 'default' enter sequence for state init */
static void enseq_main_region_init_default(Master_sc* handle)
{
	/* 'default' enter sequence for state init */
	enact_main_region_init(handle);
	handle->stateConfVector[0] = Master_sc_main_region_init;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state sync */
static void enseq_main_region_sync_default(Master_sc* handle)
{
	/* 'default' enter sequence for state sync */
	enseq_main_region_sync_tdma_default(handle);
	enseq_main_region_sync_Sync_slot_default(handle);
	enseq_main_region_sync_Follow_up_slot_default(handle);
	enseq_main_region_sync_slave_default(handle);
}

/* 'default' enter sequence for state active */
static void enseq_main_region_sync_tdma_active_default(Master_sc* handle)
{
	/* 'default' enter sequence for state active */
	handle->stateConfVector[0] = Master_sc_main_region_sync_tdma_active;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Sync */
static void enseq_main_region_sync_Sync_slot_Sync_default(Master_sc* handle)
{
	/* 'default' enter sequence for state Sync */
	handle->stateConfVector[1] = Master_sc_main_region_sync_Sync_slot_Sync;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state wait */
static void enseq_main_region_sync_Sync_slot_wait_default(Master_sc* handle)
{
	/* 'default' enter sequence for state wait */
	handle->stateConfVector[1] = Master_sc_main_region_sync_Sync_slot_wait;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state Follow Up */
static void enseq_main_region_sync_Follow_up_slot_Follow_Up_default(Master_sc* handle)
{
	/* 'default' enter sequence for state Follow Up */
	handle->stateConfVector[2] = Master_sc_main_region_sync_Follow_up_slot_Follow_Up;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state wait */
static void enseq_main_region_sync_Follow_up_slot_wait_default(Master_sc* handle)
{
	/* 'default' enter sequence for state wait */
	handle->stateConfVector[2] = Master_sc_main_region_sync_Follow_up_slot_wait;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state wait slave */
static void enseq_main_region_sync_slave_wait_slave_default(Master_sc* handle)
{
	/* 'default' enter sequence for state wait slave */
	handle->stateConfVector[3] = Master_sc_main_region_sync_slave_wait_slave;
	handle->stateConfVectorPosition = 3;
}

/* 'default' enter sequence for state start lave slot */
static void enseq_main_region_sync_slave_start_lave_slot_default(Master_sc* handle)
{
	/* 'default' enter sequence for state start lave slot */
	enact_main_region_sync_slave_start_lave_slot(handle);
	handle->stateConfVector[3] = Master_sc_main_region_sync_slave_start_lave_slot;
	handle->stateConfVectorPosition = 3;
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(Master_sc* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
}

/* 'default' enter sequence for region tdma */
static void enseq_main_region_sync_tdma_default(Master_sc* handle)
{
	/* 'default' enter sequence for region tdma */
	react_main_region_sync_tdma__entry_Default(handle);
}

/* 'default' enter sequence for region Sync slot */
static void enseq_main_region_sync_Sync_slot_default(Master_sc* handle)
{
	/* 'default' enter sequence for region Sync slot */
	react_main_region_sync_Sync_slot__entry_Default(handle);
}

/* 'default' enter sequence for region Follow up slot */
static void enseq_main_region_sync_Follow_up_slot_default(Master_sc* handle)
{
	/* 'default' enter sequence for region Follow up slot */
	react_main_region_sync_Follow_up_slot__entry_Default(handle);
}

/* 'default' enter sequence for region slave */
static void enseq_main_region_sync_slave_default(Master_sc* handle)
{
	/* 'default' enter sequence for region slave */
	react_main_region_sync_slave__entry_Default(handle);
}

/* Default exit sequence for state init */
static void exseq_main_region_init(Master_sc* handle)
{
	/* Default exit sequence for state init */
	handle->stateConfVector[0] = Master_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state active */
static void exseq_main_region_sync_tdma_active(Master_sc* handle)
{
	/* Default exit sequence for state active */
	handle->stateConfVector[0] = Master_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Sync */
static void exseq_main_region_sync_Sync_slot_Sync(Master_sc* handle)
{
	/* Default exit sequence for state Sync */
	handle->stateConfVector[1] = Master_sc_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state wait */
static void exseq_main_region_sync_Sync_slot_wait(Master_sc* handle)
{
	/* Default exit sequence for state wait */
	handle->stateConfVector[1] = Master_sc_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state Follow Up */
static void exseq_main_region_sync_Follow_up_slot_Follow_Up(Master_sc* handle)
{
	/* Default exit sequence for state Follow Up */
	handle->stateConfVector[2] = Master_sc_last_state;
	handle->stateConfVectorPosition = 2;
}

/* Default exit sequence for state wait */
static void exseq_main_region_sync_Follow_up_slot_wait(Master_sc* handle)
{
	/* Default exit sequence for state wait */
	handle->stateConfVector[2] = Master_sc_last_state;
	handle->stateConfVectorPosition = 2;
}

/* Default exit sequence for state wait slave */
static void exseq_main_region_sync_slave_wait_slave(Master_sc* handle)
{
	/* Default exit sequence for state wait slave */
	handle->stateConfVector[3] = Master_sc_last_state;
	handle->stateConfVectorPosition = 3;
}

/* Default exit sequence for state start lave slot */
static void exseq_main_region_sync_slave_start_lave_slot(Master_sc* handle)
{
	/* Default exit sequence for state start lave slot */
	handle->stateConfVector[3] = Master_sc_last_state;
	handle->stateConfVectorPosition = 3;
}

/* Default exit sequence for region main region */
static void exseq_main_region(Master_sc* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of master_sc.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Master_sc_main_region_init :
		{
			exseq_main_region_init(handle);
			break;
		}
		case Master_sc_main_region_sync_tdma_active :
		{
			exseq_main_region_sync_tdma_active(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of master_sc.main_region) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Master_sc_main_region_sync_Sync_slot_Sync :
		{
			exseq_main_region_sync_Sync_slot_Sync(handle);
			break;
		}
		case Master_sc_main_region_sync_Sync_slot_wait :
		{
			exseq_main_region_sync_Sync_slot_wait(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of master_sc.main_region) at position 2... */
	switch(handle->stateConfVector[ 2 ])
	{
		case Master_sc_main_region_sync_Follow_up_slot_Follow_Up :
		{
			exseq_main_region_sync_Follow_up_slot_Follow_Up(handle);
			break;
		}
		case Master_sc_main_region_sync_Follow_up_slot_wait :
		{
			exseq_main_region_sync_Follow_up_slot_wait(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of master_sc.main_region) at position 3... */
	switch(handle->stateConfVector[ 3 ])
	{
		case Master_sc_main_region_sync_slave_wait_slave :
		{
			exseq_main_region_sync_slave_wait_slave(handle);
			break;
		}
		case Master_sc_main_region_sync_slave_start_lave_slot :
		{
			exseq_main_region_sync_slave_start_lave_slot(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region tdma */
static void exseq_main_region_sync_tdma(Master_sc* handle)
{
	/* Default exit sequence for region tdma */
	/* Handle exit of all possible states (of master_sc.main_region.sync.tdma) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Master_sc_main_region_sync_tdma_active :
		{
			exseq_main_region_sync_tdma_active(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region Sync slot */
static void exseq_main_region_sync_Sync_slot(Master_sc* handle)
{
	/* Default exit sequence for region Sync slot */
	/* Handle exit of all possible states (of master_sc.main_region.sync.Sync_slot) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Master_sc_main_region_sync_Sync_slot_Sync :
		{
			exseq_main_region_sync_Sync_slot_Sync(handle);
			break;
		}
		case Master_sc_main_region_sync_Sync_slot_wait :
		{
			exseq_main_region_sync_Sync_slot_wait(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region Follow up slot */
static void exseq_main_region_sync_Follow_up_slot(Master_sc* handle)
{
	/* Default exit sequence for region Follow up slot */
	/* Handle exit of all possible states (of master_sc.main_region.sync.Follow_up_slot) at position 2... */
	switch(handle->stateConfVector[ 2 ])
	{
		case Master_sc_main_region_sync_Follow_up_slot_Follow_Up :
		{
			exseq_main_region_sync_Follow_up_slot_Follow_Up(handle);
			break;
		}
		case Master_sc_main_region_sync_Follow_up_slot_wait :
		{
			exseq_main_region_sync_Follow_up_slot_wait(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region slave */
static void exseq_main_region_sync_slave(Master_sc* handle)
{
	/* Default exit sequence for region slave */
	/* Handle exit of all possible states (of master_sc.main_region.sync.slave) at position 3... */
	switch(handle->stateConfVector[ 3 ])
	{
		case Master_sc_main_region_sync_slave_wait_slave :
		{
			exseq_main_region_sync_slave_wait_slave(handle);
			break;
		}
		case Master_sc_main_region_sync_slave_start_lave_slot :
		{
			exseq_main_region_sync_slave_start_lave_slot(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state init. */
static void react_main_region_init(Master_sc* handle)
{
	/* The reactions of state init. */
	effect_main_region_init_tr0(handle);
}

/* The reactions of state active. */
static void react_main_region_sync_tdma_active(Master_sc* handle)
{
	/* The reactions of state active. */
	if (check_main_region_sync_tdma_active_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_sync_tdma_active_tr0(handle);
	} 
}

/* The reactions of state Sync. */
static void react_main_region_sync_Sync_slot_Sync(Master_sc* handle)
{
	/* The reactions of state Sync. */
	if (check_main_region_sync_Sync_slot_Sync_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_sync_Sync_slot_Sync_tr0(handle);
	} 
}

/* The reactions of state wait. */
static void react_main_region_sync_Sync_slot_wait(Master_sc* handle)
{
	/* The reactions of state wait. */
	if (check_main_region_sync_Sync_slot_wait_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_sync_Sync_slot_wait_tr0(handle);
	} 
}

/* The reactions of state Follow Up. */
static void react_main_region_sync_Follow_up_slot_Follow_Up(Master_sc* handle)
{
	/* The reactions of state Follow Up. */
	if (check_main_region_sync_Follow_up_slot_Follow_Up_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_sync_Follow_up_slot_Follow_Up_tr0(handle);
	} 
}

/* The reactions of state wait. */
static void react_main_region_sync_Follow_up_slot_wait(Master_sc* handle)
{
	/* The reactions of state wait. */
	if (check_main_region_sync_Follow_up_slot_wait_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_sync_Follow_up_slot_wait_tr0(handle);
	} 
}

/* The reactions of state wait slave. */
static void react_main_region_sync_slave_wait_slave(Master_sc* handle)
{
	/* The reactions of state wait slave. */
	if (check_main_region_sync_slave_wait_slave_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_sync_slave_wait_slave_tr0(handle);
	} 
}

/* The reactions of state start lave slot. */
static void react_main_region_sync_slave_start_lave_slot(Master_sc* handle)
{
	/* The reactions of state start lave slot. */
	if (check_main_region_sync_slave_start_lave_slot_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_sync_slave_start_lave_slot_tr0(handle);
	}  else
	{
		if (check_main_region_sync_slave_start_lave_slot_tr1_tr1(handle) == bool_true)
		{ 
			effect_main_region_sync_slave_start_lave_slot_tr1(handle);
		}  else
		{
			if (check_main_region_sync_slave_start_lave_slot_tr2_tr2(handle) == bool_true)
			{ 
				effect_main_region_sync_slave_start_lave_slot_tr2(handle);
			} 
		}
	}
}

/* The reactions of state null. */
static void react_main_region_sync_tdma__choice_0(Master_sc* handle)
{
	/* The reactions of state null. */
	if (check_main_region_sync_tdma__choice_0_tr1_tr1(handle) == bool_true)
	{ 
		effect_main_region_sync_tdma__choice_0_tr1(handle);
	}  else
	{
		if (check_main_region_sync_tdma__choice_0_tr2_tr2(handle) == bool_true)
		{ 
			effect_main_region_sync_tdma__choice_0_tr2(handle);
		}  else
		{
			effect_main_region_sync_tdma__choice_0_tr0(handle);
		}
	}
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(Master_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_init_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_sync_tdma__entry_Default(Master_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_sync_tdma_active_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_sync_Sync_slot__entry_Default(Master_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_sync_Sync_slot_wait_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_sync_Follow_up_slot__entry_Default(Master_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_sync_Follow_up_slot_wait_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_sync_slave__entry_Default(Master_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_sync_slave_wait_slave_default(handle);
}


static void master_sc_internal_event_init(master_sc_internal_event * ev, master_sc_event_name name)
{
	ev->name = name;
}

static void master_sc_eventqueue_init(master_sc_eventqueue * eq)
{
	eq->push_index = 0;
	eq->pop_index = 0;
	eq->size = 0;
}

static sc_integer master_sc_eventqueue_size(master_sc_eventqueue * eq)
{
	return eq->size;
}

static master_sc_internal_event master_sc_eventqueue_pop(master_sc_eventqueue * eq)
{
	master_sc_internal_event event;
	if(master_sc_eventqueue_size(eq) <= 0) {
		master_sc_internal_event_init(&event, master_sc_invalid_event);
	}
	else {
		event = eq->events[eq->pop_index];
		
		if(eq->pop_index < MASTER_SC_EVENTQUEUE_BUFFERSIZE - 1) {
			eq->pop_index++;
		} 
		else {
			eq->pop_index = 0;
		}
		eq->size--;
	}
	return event;
}

static sc_boolean master_sc_eventqueue_push(master_sc_eventqueue * eq, master_sc_internal_event ev)
{
	if(master_sc_eventqueue_size(eq) == MASTER_SC_EVENTQUEUE_BUFFERSIZE) {
		return false;
	}
	else {
		eq->events[eq->push_index] = ev;
		
		if(eq->push_index < MASTER_SC_EVENTQUEUE_BUFFERSIZE - 1) {
			eq->push_index++;
		}
		else {
			eq->push_index = 0;
		}
		eq->size++;
		
		return true;
	}
}

static void master_sc_add_event_to_queue(Master_sc* handle, master_sc_event_name name)
{
	master_sc_internal_event event;
	master_sc_internal_event_init(&event, name);
	master_sc_eventqueue_push(&(handle->internal_event_queue), event);
}


static void master_sc_dispatch_event(Master_sc* handle, const master_sc_internal_event * event) {
	switch(event->name) {
		case master_scInternal_slave_slot:
		{
			handle->internal.slave_slot_raised = bool_true;
			break;
		}
		case master_scInternal_sync_slot:
		{
			handle->internal.sync_slot_raised = bool_true;
			break;
		}
		case master_scInternal_followup_slot:
		{
			handle->internal.followup_slot_raised = bool_true;
			break;
		}
		default:
			break;
	}
}
