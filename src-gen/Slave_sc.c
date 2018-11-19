
#include "Slave_sc.h"
#include "sc_types.h"

#include <stdlib.h>
#include <string.h>
/*! \file Implementation of the state machine 'slave_sc'
*/

/* prototypes of all internal functions */
static sc_boolean check_main_region_init_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_wait_for_followup_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_tbma_active_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_response_response_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_response_timediff_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_sync_wait_for_sync_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_followup_wait_for_2_followup_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_followup_wait_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_wait_for_sync_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_tbma__choice_0_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_tbma__choice_0_tr1_tr1(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_tbma__choice_0_tr2_tr2(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_tbma__choice_0_tr3_tr3(const Slave_sc* handle);
static sc_boolean check_main_region__choice_0_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region__choice_0_tr1_tr1(const Slave_sc* handle);
static void effect_main_region_init_tr0(Slave_sc* handle);
static void effect_main_region_wait_for_followup_tr0(Slave_sc* handle);
static void effect_main_region_cycle_tbma_active_tr0(Slave_sc* handle);
static void effect_main_region_cycle_response_response_tr0(Slave_sc* handle);
static void effect_main_region_cycle_response_timediff_tr0(Slave_sc* handle);
static void effect_main_region_cycle_sync_wait_for_sync_tr0(Slave_sc* handle);
static void effect_main_region_cycle_followup_wait_for_2_followup_tr0(Slave_sc* handle);
static void effect_main_region_cycle_followup_wait_tr0(Slave_sc* handle);
static void effect_main_region_wait_for_sync_tr0(Slave_sc* handle);
static void effect_main_region_cycle_tbma__choice_0_tr0(Slave_sc* handle);
static void effect_main_region_cycle_tbma__choice_0_tr1(Slave_sc* handle);
static void effect_main_region_cycle_tbma__choice_0_tr2(Slave_sc* handle);
static void effect_main_region_cycle_tbma__choice_0_tr3(Slave_sc* handle);
static void effect_main_region__choice_0_tr0(Slave_sc* handle);
static void effect_main_region__choice_0_tr1(Slave_sc* handle);
static void enact_main_region_init(Slave_sc* handle);
static void enact_main_region_cycle_response_response(Slave_sc* handle);
static void enact_main_region_wait_for_sync(Slave_sc* handle);
static void enseq_main_region_init_default(Slave_sc* handle);
static void enseq_main_region_wait_for_followup_default(Slave_sc* handle);
static void enseq_main_region_cycle_default(Slave_sc* handle);
static void enseq_main_region_cycle_tbma_active_default(Slave_sc* handle);
static void enseq_main_region_cycle_response_response_default(Slave_sc* handle);
static void enseq_main_region_cycle_response_timediff_default(Slave_sc* handle);
static void enseq_main_region_cycle_sync_wait_for_sync_default(Slave_sc* handle);
static void enseq_main_region_cycle_followup_wait_for_2_followup_default(Slave_sc* handle);
static void enseq_main_region_cycle_followup_wait_default(Slave_sc* handle);
static void enseq_main_region_wait_for_sync_default(Slave_sc* handle);
static void enseq_main_region_default(Slave_sc* handle);
static void enseq_main_region_cycle_tbma_default(Slave_sc* handle);
static void enseq_main_region_cycle_response_default(Slave_sc* handle);
static void enseq_main_region_cycle_sync_default(Slave_sc* handle);
static void enseq_main_region_cycle_followup_default(Slave_sc* handle);
static void exseq_main_region_init(Slave_sc* handle);
static void exseq_main_region_wait_for_followup(Slave_sc* handle);
static void exseq_main_region_cycle_tbma_active(Slave_sc* handle);
static void exseq_main_region_cycle_response_response(Slave_sc* handle);
static void exseq_main_region_cycle_response_timediff(Slave_sc* handle);
static void exseq_main_region_cycle_sync_wait_for_sync(Slave_sc* handle);
static void exseq_main_region_cycle_followup_wait_for_2_followup(Slave_sc* handle);
static void exseq_main_region_cycle_followup_wait(Slave_sc* handle);
static void exseq_main_region_wait_for_sync(Slave_sc* handle);
static void exseq_main_region(Slave_sc* handle);
static void exseq_main_region_cycle_tbma(Slave_sc* handle);
static void exseq_main_region_cycle_response(Slave_sc* handle);
static void exseq_main_region_cycle_sync(Slave_sc* handle);
static void exseq_main_region_cycle_followup(Slave_sc* handle);
static void react_main_region_init(Slave_sc* handle);
static void react_main_region_wait_for_followup(Slave_sc* handle);
static void react_main_region_cycle_tbma_active(Slave_sc* handle);
static void react_main_region_cycle_response_response(Slave_sc* handle);
static void react_main_region_cycle_response_timediff(Slave_sc* handle);
static void react_main_region_cycle_sync_wait_for_sync(Slave_sc* handle);
static void react_main_region_cycle_followup_wait_for_2_followup(Slave_sc* handle);
static void react_main_region_cycle_followup_wait(Slave_sc* handle);
static void react_main_region_wait_for_sync(Slave_sc* handle);
static void react_main_region_cycle_tbma__choice_0(Slave_sc* handle);
static void react_main_region__choice_0(Slave_sc* handle);
static void react_main_region__entry_Default(Slave_sc* handle);
static void react_main_region_cycle_tbma__entry_Default(Slave_sc* handle);
static void react_main_region_cycle_response__entry_Default(Slave_sc* handle);
static void react_main_region_cycle_sync__entry_Default(Slave_sc* handle);
static void react_main_region_cycle_followup__entry_Default(Slave_sc* handle);
static void clearInEvents(Slave_sc* handle);
static void clearOutEvents(Slave_sc* handle);
static void slave_sc_eventqueue_init(slave_sc_eventqueue * eq);
static sc_integer slave_sc_eventqueue_size(slave_sc_eventqueue * eq);
static slave_sc_internal_event slave_sc_eventqueue_pop(slave_sc_eventqueue * eq);
static sc_boolean slave_sc_eventqueue_push(slave_sc_eventqueue * eq, slave_sc_internal_event ev);

static void slave_sc_dispatch_event(Slave_sc* handle, const slave_sc_internal_event * event);

static void slave_sc_internal_event_init(slave_sc_internal_event * ev, slave_sc_event_name name);
static void slave_sc_add_event_to_queue(Slave_sc* handle, slave_sc_event_name name);


void slave_sc_init(Slave_sc* handle)
{
		sc_integer i;
	
		for (i = 0; i < SLAVE_SC_MAX_ORTHOGONAL_STATES; ++i)
		{
			handle->stateConfVector[i] = Slave_sc_last_state;
		}
		
		
		handle->stateConfVectorPosition = 0;
	
		clearInEvents(handle);
		clearOutEvents(handle);
	
		/* Default init sequence for statechart slave_sc */
		handle->iface.slave_index = 0;
		handle->internal.sync_tx_ts = 0;
		handle->internal.sync_rx_ts = 0;
		handle->internal.slave_time_diff = 0;
		handle->internal.master_time_diff = 0;
		handle->internal.offset = 0;
		handle->internal.delay = 0;
		handle->internal.drift = 0.0;
	slave_sc_eventqueue_init(&(handle->internal_event_queue));
}

void slave_sc_enter(Slave_sc* handle)
{
	/* Default enter sequence for statechart slave_sc */
	enseq_main_region_default(handle);
}

void slave_sc_runCycle(Slave_sc* handle)
{
	clearOutEvents(handle);
	
	slave_sc_internal_event currentEvent = slave_sc_eventqueue_pop(&(handle->internal_event_queue));
	
	do {
		slave_sc_dispatch_event(handle, &currentEvent);
		for (handle->stateConfVectorPosition = 0;
			handle->stateConfVectorPosition < SLAVE_SC_MAX_ORTHOGONAL_STATES;
			handle->stateConfVectorPosition++)
			{
				
			switch (handle->stateConfVector[handle->stateConfVectorPosition])
			{
			case Slave_sc_main_region_init:
			{
				react_main_region_init(handle);
				break;
			}
			case Slave_sc_main_region_wait_for_followup:
			{
				react_main_region_wait_for_followup(handle);
				break;
			}
			case Slave_sc_main_region_cycle_tbma_active:
			{
				react_main_region_cycle_tbma_active(handle);
				break;
			}
			case Slave_sc_main_region_cycle_response_response:
			{
				react_main_region_cycle_response_response(handle);
				break;
			}
			case Slave_sc_main_region_cycle_response_timediff:
			{
				react_main_region_cycle_response_timediff(handle);
				break;
			}
			case Slave_sc_main_region_cycle_sync_wait_for_sync:
			{
				react_main_region_cycle_sync_wait_for_sync(handle);
				break;
			}
			case Slave_sc_main_region_cycle_followup_wait_for_2_followup:
			{
				react_main_region_cycle_followup_wait_for_2_followup(handle);
				break;
			}
			case Slave_sc_main_region_cycle_followup_wait:
			{
				react_main_region_cycle_followup_wait(handle);
				break;
			}
			case Slave_sc_main_region_wait_for_sync:
			{
				react_main_region_wait_for_sync(handle);
				break;
			}
			default:
				break;
			}
		}
		
		clearInEvents(handle);
	} while((currentEvent = slave_sc_eventqueue_pop(&(handle->internal_event_queue))).name != slave_sc_invalid_event);
	
}

void slave_sc_exit(Slave_sc* handle)
{
	/* Default exit sequence for statechart slave_sc */
	exseq_main_region(handle);
}

sc_boolean slave_sc_isActive(const Slave_sc* handle)
{
	sc_boolean result = bool_false;
	int i;
	
	for(i = 0; i < SLAVE_SC_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Slave_sc_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean slave_sc_isFinal(const Slave_sc* handle)
{
   return bool_false;
}

sc_boolean slave_sc_isStateActive(const Slave_sc* handle, Slave_scStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Slave_sc_main_region_init :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_INIT] == Slave_sc_main_region_init
			);
			break;
		case Slave_sc_main_region_wait_for_followup :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_WAIT_FOR_FOLLOWUP] == Slave_sc_main_region_wait_for_followup
			);
			break;
		case Slave_sc_main_region_cycle :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE] >= Slave_sc_main_region_cycle
				&& handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE] <= Slave_sc_main_region_cycle_followup_wait);
			break;
		case Slave_sc_main_region_cycle_tbma_active :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE_TBMA_ACTIVE] == Slave_sc_main_region_cycle_tbma_active
			);
			break;
		case Slave_sc_main_region_cycle_response_response :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE_RESPONSE_RESPONSE] == Slave_sc_main_region_cycle_response_response
			);
			break;
		case Slave_sc_main_region_cycle_response_timediff :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE_RESPONSE_TIMEDIFF] == Slave_sc_main_region_cycle_response_timediff
			);
			break;
		case Slave_sc_main_region_cycle_sync_wait_for_sync :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE_SYNC_WAIT_FOR_SYNC] == Slave_sc_main_region_cycle_sync_wait_for_sync
			);
			break;
		case Slave_sc_main_region_cycle_followup_wait_for_2_followup :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE_FOLLOWUP_WAIT_FOR_2_FOLLOWUP] == Slave_sc_main_region_cycle_followup_wait_for_2_followup
			);
			break;
		case Slave_sc_main_region_cycle_followup_wait :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE_FOLLOWUP_WAIT] == Slave_sc_main_region_cycle_followup_wait
			);
			break;
		case Slave_sc_main_region_wait_for_sync :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_WAIT_FOR_SYNC] == Slave_sc_main_region_wait_for_sync
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}

static void clearInEvents(Slave_sc* handle)
{
	handle->iface.packet_sent_raised = bool_false;
	handle->iface.packet_received_raised = bool_false;
	handle->iface.tdma_slot_raised = bool_false;
	handle->internal.slave_slot_raised = bool_false;
	handle->internal.sync_slot_raised = bool_false;
	handle->internal.followup_slot_raised = bool_false;
}

static void clearOutEvents(Slave_sc* handle)
{
}

void slave_scIface_raise_packet_sent(Slave_sc* handle, int64_t value)
{
	handle->iface.packet_sent_value = value;
	handle->iface.packet_sent_raised = bool_true;
	
	slave_sc_runCycle(handle);
}
void slave_scIface_raise_packet_received(Slave_sc* handle, int64_t value)
{
	handle->iface.packet_received_value = value;
	handle->iface.packet_received_raised = bool_true;
	
	slave_sc_runCycle(handle);
}
void slave_scIface_raise_tdma_slot(Slave_sc* handle, uint8_t value)
{
	handle->iface.tdma_slot_value = value;
	handle->iface.tdma_slot_raised = bool_true;
	
	slave_sc_runCycle(handle);
}


uint8_t * slave_scIface_get_rx_packet(const Slave_sc* handle)
{
	return handle->iface.rx_packet;
}
void slave_scIface_set_rx_packet(Slave_sc* handle, uint8_t * value)
{
	handle->iface.rx_packet = value;
}
uint8_t slave_scIface_get_slave_index(const Slave_sc* handle)
{
	return handle->iface.slave_index;
}
void slave_scIface_set_slave_index(Slave_sc* handle, uint8_t value)
{
	handle->iface.slave_index = value;
}

/* implementations of all internal functions */

static sc_boolean check_main_region_init_tr0_tr0(const Slave_sc* handle)
{
	return bool_true;
}

static sc_boolean check_main_region_wait_for_followup_tr0_tr0(const Slave_sc* handle)
{
	return ((handle->iface.packet_received_raised) && (getPacketType(handle->iface.rx_packet) == FOLLOW_UP)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_cycle_tbma_active_tr0_tr0(const Slave_sc* handle)
{
	return handle->iface.tdma_slot_raised;
}

static sc_boolean check_main_region_cycle_response_response_tr0_tr0(const Slave_sc* handle)
{
	return handle->iface.packet_sent_raised;
}

static sc_boolean check_main_region_cycle_response_timediff_tr0_tr0(const Slave_sc* handle)
{
	return handle->internal.slave_slot_raised;
}

static sc_boolean check_main_region_cycle_sync_wait_for_sync_tr0_tr0(const Slave_sc* handle)
{
	return ((handle->iface.packet_received_raised) && (getPacketType(handle->iface.rx_packet) == SYNC)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_cycle_followup_wait_for_2_followup_tr0_tr0(const Slave_sc* handle)
{
	return ((handle->iface.packet_received_raised) && (getPacketType(handle->iface.rx_packet) == FOLLOW_UP)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_cycle_followup_wait_tr0_tr0(const Slave_sc* handle)
{
	return ((handle->iface.packet_received_raised) && (getPacketType(handle->iface.rx_packet) == FOLLOW_UP)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_wait_for_sync_tr0_tr0(const Slave_sc* handle)
{
	return handle->iface.packet_received_raised;
}

static sc_boolean check_main_region_cycle_tbma__choice_0_tr0_tr0(const Slave_sc* handle)
{
	return (handle->iface.tdma_slot_value == (handle->iface.slave_index + 2)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_cycle_tbma__choice_0_tr1_tr1(const Slave_sc* handle)
{
	return (handle->iface.tdma_slot_value == 0) ? bool_true : bool_false;
}

static sc_boolean check_main_region_cycle_tbma__choice_0_tr2_tr2(const Slave_sc* handle)
{
	return (handle->iface.tdma_slot_value == 1) ? bool_true : bool_false;
}

static sc_boolean check_main_region_cycle_tbma__choice_0_tr3_tr3(const Slave_sc* handle)
{
	return bool_true;
}

static sc_boolean check_main_region__choice_0_tr0_tr0(const Slave_sc* handle)
{
	return (getPacketType(handle->iface.rx_packet) == SYNC) ? bool_true : bool_false;
}

static sc_boolean check_main_region__choice_0_tr1_tr1(const Slave_sc* handle)
{
	return bool_true;
}

static void effect_main_region_init_tr0(Slave_sc* handle)
{
	exseq_main_region_init(handle);
	enseq_main_region_wait_for_sync_default(handle);
}

static void effect_main_region_wait_for_followup_tr0(Slave_sc* handle)
{
	exseq_main_region_wait_for_followup(handle);
	s_clockAddInt(-handle->internal.offset);
	handle->internal.sync_rx_ts = handle->internal.sync_tx_ts + handle->internal.delay;
	enseq_main_region_cycle_default(handle);
}

static void effect_main_region_cycle_tbma_active_tr0(Slave_sc* handle)
{
	exseq_main_region_cycle_tbma_active(handle);
	react_main_region_cycle_tbma__choice_0(handle);
}

static void effect_main_region_cycle_response_response_tr0(Slave_sc* handle)
{
	exseq_main_region_cycle_response_response(handle);
	handle->internal.slave_time_diff = ((int32_t) (handle->iface.packet_sent_value - handle->internal.sync_rx_ts));
	enseq_main_region_cycle_response_timediff_default(handle);
}

static void effect_main_region_cycle_response_timediff_tr0(Slave_sc* handle)
{
	exseq_main_region_cycle_response_timediff(handle);
	enseq_main_region_cycle_response_response_default(handle);
}

static void effect_main_region_cycle_sync_wait_for_sync_tr0(Slave_sc* handle)
{
	exseq_main_region_cycle_sync_wait_for_sync(handle);
	handle->internal.sync_rx_ts = handle->iface.packet_received_value;
	handle->internal.master_time_diff = ((int32_t) getDelayResp(handle->iface.rx_packet, handle->iface.slave_index));
	handle->internal.delay = (handle->internal.master_time_diff - handle->internal.slave_time_diff) / 2;
	enseq_main_region_cycle_sync_wait_for_sync_default(handle);
}

static void effect_main_region_cycle_followup_wait_for_2_followup_tr0(Slave_sc* handle)
{
	exseq_main_region_cycle_followup_wait_for_2_followup(handle);
	handle->internal.sync_tx_ts = handle->iface.packet_received_value;
	handle->internal.offset = handle->internal.sync_rx_ts - handle->internal.sync_tx_ts - handle->internal.delay;
	handle->internal.drift = (((float) handle->internal.offset)) / CYCLE_LENGTH;
	s_clockDriftCorrection(fixedpt_fromfloat(handle->internal.drift));
	handle->internal.PIctrl.I = handle->internal.drift;
	s_clockAddInt(-handle->internal.offset);
	enseq_main_region_cycle_followup_wait_default(handle);
}

static void effect_main_region_cycle_followup_wait_tr0(Slave_sc* handle)
{
	exseq_main_region_cycle_followup_wait(handle);
	handle->internal.sync_tx_ts = handle->iface.packet_received_value;
	handle->internal.offset = handle->internal.sync_rx_ts - handle->internal.sync_tx_ts - handle->internal.delay;
	handle->internal.drift = PIcontroller(&(handle->internal.PIctrl), (((float) handle->internal.offset)) / CYCLE_LENGTH);
	s_clockDriftCorrection(fixedpt_fromfloat(handle->internal.drift));
	enseq_main_region_cycle_followup_wait_default(handle);
}

static void effect_main_region_wait_for_sync_tr0(Slave_sc* handle)
{
	exseq_main_region_wait_for_sync(handle);
	react_main_region__choice_0(handle);
}

static void effect_main_region_cycle_tbma__choice_0_tr0(Slave_sc* handle)
{
	slave_sc_add_event_to_queue(handle, slave_scInternal_slave_slot);
	enseq_main_region_cycle_tbma_active_default(handle);
}

static void effect_main_region_cycle_tbma__choice_0_tr1(Slave_sc* handle)
{
	startRx();
	slave_sc_add_event_to_queue(handle, slave_scInternal_sync_slot);
	enseq_main_region_cycle_tbma_active_default(handle);
}

static void effect_main_region_cycle_tbma__choice_0_tr2(Slave_sc* handle)
{
	startRx();
	slave_sc_add_event_to_queue(handle, slave_scInternal_followup_slot);
	enseq_main_region_cycle_tbma_active_default(handle);
}

static void effect_main_region_cycle_tbma__choice_0_tr3(Slave_sc* handle)
{
	enseq_main_region_cycle_tbma_active_default(handle);
}

static void effect_main_region__choice_0_tr0(Slave_sc* handle)
{
	handle->internal.sync_rx_ts = handle->iface.packet_received_value;
	startRx();
	enseq_main_region_wait_for_followup_default(handle);
}

static void effect_main_region__choice_0_tr1(Slave_sc* handle)
{
	enseq_main_region_wait_for_sync_default(handle);
}

/* Entry action for state 'init'. */
static void enact_main_region_init(Slave_sc* handle)
{
	/* Entry action for state 'init'. */
	setSourceAddress(tx_packet, handle->iface.slave_index + 1);
	setPacketType(tx_packet, DATA);
	handle->internal.PIctrl.Ki = 1 / 4;
	handle->internal.PIctrl.Kp = 1 / 16;
}

/* Entry action for state 'response'. */
static void enact_main_region_cycle_response_response(Slave_sc* handle)
{
	/* Entry action for state 'response'. */
	sendPacket(tx_packet);
}

/* Entry action for state 'wait for sync'. */
static void enact_main_region_wait_for_sync(Slave_sc* handle)
{
	/* Entry action for state 'wait for sync'. */
	startRx();
}

/* 'default' enter sequence for state init */
static void enseq_main_region_init_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state init */
	enact_main_region_init(handle);
	handle->stateConfVector[0] = Slave_sc_main_region_init;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state wait for followup */
static void enseq_main_region_wait_for_followup_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait for followup */
	handle->stateConfVector[0] = Slave_sc_main_region_wait_for_followup;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state cycle */
static void enseq_main_region_cycle_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state cycle */
	enseq_main_region_cycle_tbma_default(handle);
	enseq_main_region_cycle_response_default(handle);
	enseq_main_region_cycle_sync_default(handle);
	enseq_main_region_cycle_followup_default(handle);
}

/* 'default' enter sequence for state active */
static void enseq_main_region_cycle_tbma_active_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state active */
	handle->stateConfVector[0] = Slave_sc_main_region_cycle_tbma_active;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state response */
static void enseq_main_region_cycle_response_response_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state response */
	enact_main_region_cycle_response_response(handle);
	handle->stateConfVector[1] = Slave_sc_main_region_cycle_response_response;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state timediff */
static void enseq_main_region_cycle_response_timediff_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state timediff */
	handle->stateConfVector[1] = Slave_sc_main_region_cycle_response_timediff;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state wait for sync */
static void enseq_main_region_cycle_sync_wait_for_sync_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait for sync */
	handle->stateConfVector[2] = Slave_sc_main_region_cycle_sync_wait_for_sync;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state wait for 2.followup */
static void enseq_main_region_cycle_followup_wait_for_2_followup_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait for 2.followup */
	handle->stateConfVector[3] = Slave_sc_main_region_cycle_followup_wait_for_2_followup;
	handle->stateConfVectorPosition = 3;
}

/* 'default' enter sequence for state wait */
static void enseq_main_region_cycle_followup_wait_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait */
	handle->stateConfVector[3] = Slave_sc_main_region_cycle_followup_wait;
	handle->stateConfVectorPosition = 3;
}

/* 'default' enter sequence for state wait for sync */
static void enseq_main_region_wait_for_sync_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait for sync */
	enact_main_region_wait_for_sync(handle);
	handle->stateConfVector[0] = Slave_sc_main_region_wait_for_sync;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(Slave_sc* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
}

/* 'default' enter sequence for region tbma */
static void enseq_main_region_cycle_tbma_default(Slave_sc* handle)
{
	/* 'default' enter sequence for region tbma */
	react_main_region_cycle_tbma__entry_Default(handle);
}

/* 'default' enter sequence for region response */
static void enseq_main_region_cycle_response_default(Slave_sc* handle)
{
	/* 'default' enter sequence for region response */
	react_main_region_cycle_response__entry_Default(handle);
}

/* 'default' enter sequence for region sync */
static void enseq_main_region_cycle_sync_default(Slave_sc* handle)
{
	/* 'default' enter sequence for region sync */
	react_main_region_cycle_sync__entry_Default(handle);
}

/* 'default' enter sequence for region followup */
static void enseq_main_region_cycle_followup_default(Slave_sc* handle)
{
	/* 'default' enter sequence for region followup */
	react_main_region_cycle_followup__entry_Default(handle);
}

/* Default exit sequence for state init */
static void exseq_main_region_init(Slave_sc* handle)
{
	/* Default exit sequence for state init */
	handle->stateConfVector[0] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state wait for followup */
static void exseq_main_region_wait_for_followup(Slave_sc* handle)
{
	/* Default exit sequence for state wait for followup */
	handle->stateConfVector[0] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state active */
static void exseq_main_region_cycle_tbma_active(Slave_sc* handle)
{
	/* Default exit sequence for state active */
	handle->stateConfVector[0] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state response */
static void exseq_main_region_cycle_response_response(Slave_sc* handle)
{
	/* Default exit sequence for state response */
	handle->stateConfVector[1] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state timediff */
static void exseq_main_region_cycle_response_timediff(Slave_sc* handle)
{
	/* Default exit sequence for state timediff */
	handle->stateConfVector[1] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state wait for sync */
static void exseq_main_region_cycle_sync_wait_for_sync(Slave_sc* handle)
{
	/* Default exit sequence for state wait for sync */
	handle->stateConfVector[2] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 2;
}

/* Default exit sequence for state wait for 2.followup */
static void exseq_main_region_cycle_followup_wait_for_2_followup(Slave_sc* handle)
{
	/* Default exit sequence for state wait for 2.followup */
	handle->stateConfVector[3] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 3;
}

/* Default exit sequence for state wait */
static void exseq_main_region_cycle_followup_wait(Slave_sc* handle)
{
	/* Default exit sequence for state wait */
	handle->stateConfVector[3] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 3;
}

/* Default exit sequence for state wait for sync */
static void exseq_main_region_wait_for_sync(Slave_sc* handle)
{
	/* Default exit sequence for state wait for sync */
	handle->stateConfVector[0] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
static void exseq_main_region(Slave_sc* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of slave_sc.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Slave_sc_main_region_init :
		{
			exseq_main_region_init(handle);
			break;
		}
		case Slave_sc_main_region_wait_for_followup :
		{
			exseq_main_region_wait_for_followup(handle);
			break;
		}
		case Slave_sc_main_region_cycle_tbma_active :
		{
			exseq_main_region_cycle_tbma_active(handle);
			break;
		}
		case Slave_sc_main_region_wait_for_sync :
		{
			exseq_main_region_wait_for_sync(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of slave_sc.main_region) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Slave_sc_main_region_cycle_response_response :
		{
			exseq_main_region_cycle_response_response(handle);
			break;
		}
		case Slave_sc_main_region_cycle_response_timediff :
		{
			exseq_main_region_cycle_response_timediff(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of slave_sc.main_region) at position 2... */
	switch(handle->stateConfVector[ 2 ])
	{
		case Slave_sc_main_region_cycle_sync_wait_for_sync :
		{
			exseq_main_region_cycle_sync_wait_for_sync(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of slave_sc.main_region) at position 3... */
	switch(handle->stateConfVector[ 3 ])
	{
		case Slave_sc_main_region_cycle_followup_wait_for_2_followup :
		{
			exseq_main_region_cycle_followup_wait_for_2_followup(handle);
			break;
		}
		case Slave_sc_main_region_cycle_followup_wait :
		{
			exseq_main_region_cycle_followup_wait(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region tbma */
static void exseq_main_region_cycle_tbma(Slave_sc* handle)
{
	/* Default exit sequence for region tbma */
	/* Handle exit of all possible states (of slave_sc.main_region.cycle.tbma) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Slave_sc_main_region_cycle_tbma_active :
		{
			exseq_main_region_cycle_tbma_active(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region response */
static void exseq_main_region_cycle_response(Slave_sc* handle)
{
	/* Default exit sequence for region response */
	/* Handle exit of all possible states (of slave_sc.main_region.cycle.response) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Slave_sc_main_region_cycle_response_response :
		{
			exseq_main_region_cycle_response_response(handle);
			break;
		}
		case Slave_sc_main_region_cycle_response_timediff :
		{
			exseq_main_region_cycle_response_timediff(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region sync */
static void exseq_main_region_cycle_sync(Slave_sc* handle)
{
	/* Default exit sequence for region sync */
	/* Handle exit of all possible states (of slave_sc.main_region.cycle.sync) at position 2... */
	switch(handle->stateConfVector[ 2 ])
	{
		case Slave_sc_main_region_cycle_sync_wait_for_sync :
		{
			exseq_main_region_cycle_sync_wait_for_sync(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region followup */
static void exseq_main_region_cycle_followup(Slave_sc* handle)
{
	/* Default exit sequence for region followup */
	/* Handle exit of all possible states (of slave_sc.main_region.cycle.followup) at position 3... */
	switch(handle->stateConfVector[ 3 ])
	{
		case Slave_sc_main_region_cycle_followup_wait_for_2_followup :
		{
			exseq_main_region_cycle_followup_wait_for_2_followup(handle);
			break;
		}
		case Slave_sc_main_region_cycle_followup_wait :
		{
			exseq_main_region_cycle_followup_wait(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state init. */
static void react_main_region_init(Slave_sc* handle)
{
	/* The reactions of state init. */
	effect_main_region_init_tr0(handle);
}

/* The reactions of state wait for followup. */
static void react_main_region_wait_for_followup(Slave_sc* handle)
{
	/* The reactions of state wait for followup. */
	if (check_main_region_wait_for_followup_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_wait_for_followup_tr0(handle);
	} 
}

/* The reactions of state active. */
static void react_main_region_cycle_tbma_active(Slave_sc* handle)
{
	/* The reactions of state active. */
	if (check_main_region_cycle_tbma_active_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_cycle_tbma_active_tr0(handle);
	} 
}

/* The reactions of state response. */
static void react_main_region_cycle_response_response(Slave_sc* handle)
{
	/* The reactions of state response. */
	if (check_main_region_cycle_response_response_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_cycle_response_response_tr0(handle);
	} 
}

/* The reactions of state timediff. */
static void react_main_region_cycle_response_timediff(Slave_sc* handle)
{
	/* The reactions of state timediff. */
	if (check_main_region_cycle_response_timediff_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_cycle_response_timediff_tr0(handle);
	} 
}

/* The reactions of state wait for sync. */
static void react_main_region_cycle_sync_wait_for_sync(Slave_sc* handle)
{
	/* The reactions of state wait for sync. */
	if (check_main_region_cycle_sync_wait_for_sync_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_cycle_sync_wait_for_sync_tr0(handle);
	} 
}

/* The reactions of state wait for 2.followup. */
static void react_main_region_cycle_followup_wait_for_2_followup(Slave_sc* handle)
{
	/* The reactions of state wait for 2.followup. */
	if (check_main_region_cycle_followup_wait_for_2_followup_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_cycle_followup_wait_for_2_followup_tr0(handle);
	} 
}

/* The reactions of state wait. */
static void react_main_region_cycle_followup_wait(Slave_sc* handle)
{
	/* The reactions of state wait. */
	if (check_main_region_cycle_followup_wait_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_cycle_followup_wait_tr0(handle);
	} 
}

/* The reactions of state wait for sync. */
static void react_main_region_wait_for_sync(Slave_sc* handle)
{
	/* The reactions of state wait for sync. */
	if (check_main_region_wait_for_sync_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_wait_for_sync_tr0(handle);
	} 
}

/* The reactions of state null. */
static void react_main_region_cycle_tbma__choice_0(Slave_sc* handle)
{
	/* The reactions of state null. */
	if (check_main_region_cycle_tbma__choice_0_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_cycle_tbma__choice_0_tr0(handle);
	}  else
	{
		if (check_main_region_cycle_tbma__choice_0_tr1_tr1(handle) == bool_true)
		{ 
			effect_main_region_cycle_tbma__choice_0_tr1(handle);
		}  else
		{
			if (check_main_region_cycle_tbma__choice_0_tr2_tr2(handle) == bool_true)
			{ 
				effect_main_region_cycle_tbma__choice_0_tr2(handle);
			}  else
			{
				effect_main_region_cycle_tbma__choice_0_tr3(handle);
			}
		}
	}
}

/* The reactions of state null. */
static void react_main_region__choice_0(Slave_sc* handle)
{
	/* The reactions of state null. */
	if (check_main_region__choice_0_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region__choice_0_tr0(handle);
	}  else
	{
		effect_main_region__choice_0_tr1(handle);
	}
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(Slave_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_init_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_cycle_tbma__entry_Default(Slave_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_cycle_tbma_active_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_cycle_response__entry_Default(Slave_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_cycle_response_timediff_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_cycle_sync__entry_Default(Slave_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_cycle_sync_wait_for_sync_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_cycle_followup__entry_Default(Slave_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_cycle_followup_wait_for_2_followup_default(handle);
}


static void slave_sc_internal_event_init(slave_sc_internal_event * ev, slave_sc_event_name name)
{
	ev->name = name;
}

static void slave_sc_eventqueue_init(slave_sc_eventqueue * eq)
{
	eq->push_index = 0;
	eq->pop_index = 0;
	eq->size = 0;
}

static sc_integer slave_sc_eventqueue_size(slave_sc_eventqueue * eq)
{
	return eq->size;
}

static slave_sc_internal_event slave_sc_eventqueue_pop(slave_sc_eventqueue * eq)
{
	slave_sc_internal_event event;
	if(slave_sc_eventqueue_size(eq) <= 0) {
		slave_sc_internal_event_init(&event, slave_sc_invalid_event);
	}
	else {
		event = eq->events[eq->pop_index];
		
		if(eq->pop_index < SLAVE_SC_EVENTQUEUE_BUFFERSIZE - 1) {
			eq->pop_index++;
		} 
		else {
			eq->pop_index = 0;
		}
		eq->size--;
	}
	return event;
}

static sc_boolean slave_sc_eventqueue_push(slave_sc_eventqueue * eq, slave_sc_internal_event ev)
{
	if(slave_sc_eventqueue_size(eq) == SLAVE_SC_EVENTQUEUE_BUFFERSIZE) {
		return false;
	}
	else {
		eq->events[eq->push_index] = ev;
		
		if(eq->push_index < SLAVE_SC_EVENTQUEUE_BUFFERSIZE - 1) {
			eq->push_index++;
		}
		else {
			eq->push_index = 0;
		}
		eq->size++;
		
		return true;
	}
}

static void slave_sc_add_event_to_queue(Slave_sc* handle, slave_sc_event_name name)
{
	slave_sc_internal_event event;
	slave_sc_internal_event_init(&event, name);
	slave_sc_eventqueue_push(&(handle->internal_event_queue), event);
}


static void slave_sc_dispatch_event(Slave_sc* handle, const slave_sc_internal_event * event) {
	switch(event->name) {
		case slave_scInternal_slave_slot:
		{
			handle->internal.slave_slot_raised = bool_true;
			break;
		}
		case slave_scInternal_sync_slot:
		{
			handle->internal.sync_slot_raised = bool_true;
			break;
		}
		case slave_scInternal_followup_slot:
		{
			handle->internal.followup_slot_raised = bool_true;
			break;
		}
		default:
			break;
	}
}
