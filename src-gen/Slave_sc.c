
#include "Slave_sc.h"
#include "sc_types.h"

#include <stdlib.h>
#include <string.h>
/*! \file Implementation of the state machine 'slave_sc'
*/

/* prototypes of all internal functions */
static sc_boolean check_main_region_init_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_wait_for_followup_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_response_response_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_response_timediff_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_sync_wait_for_sync_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_sync_wait_for_sync_tr1_tr1(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_sync_wait_for_sync_slot_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_followup_wait_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_followup_wait_tr1_tr1(const Slave_sc* handle);
static sc_boolean check_main_region_cycle_followup_wait_for_fup_slot_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_wait_for_sync_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_wait_for_sync_1_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region_wait_for_fup_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region__choice_0_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region__choice_0_tr1_tr1(const Slave_sc* handle);
static sc_boolean check_main_region__choice_1_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region__choice_1_tr1_tr1(const Slave_sc* handle);
static sc_boolean check_main_region__choice_2_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region__choice_2_tr1_tr1(const Slave_sc* handle);
static sc_boolean check_main_region__choice_3_tr0_tr0(const Slave_sc* handle);
static sc_boolean check_main_region__choice_3_tr1_tr1(const Slave_sc* handle);
static sc_boolean check_main_region__choice_4_tr1_tr1(const Slave_sc* handle);
static sc_boolean check_main_region__choice_4_tr0_tr0(const Slave_sc* handle);
static void effect_main_region_init_tr0(Slave_sc* handle);
static void effect_main_region_wait_for_followup_tr0(Slave_sc* handle);
static void effect_main_region_cycle_tr0(Slave_sc* handle);
static void effect_main_region_cycle_response_response_tr0(Slave_sc* handle);
static void effect_main_region_cycle_response_timediff_tr0(Slave_sc* handle);
static void effect_main_region_cycle_sync_wait_for_sync_tr0(Slave_sc* handle);
static void effect_main_region_cycle_sync_wait_for_sync_tr1(Slave_sc* handle);
static void effect_main_region_cycle_sync_wait_for_sync_slot_tr0(Slave_sc* handle);
static void effect_main_region_cycle_followup_wait_tr0(Slave_sc* handle);
static void effect_main_region_cycle_followup_wait_tr1(Slave_sc* handle);
static void effect_main_region_cycle_followup_wait_for_fup_slot_tr0(Slave_sc* handle);
static void effect_main_region_wait_for_sync_tr0(Slave_sc* handle);
static void effect_main_region_wait_for_sync_1_tr0(Slave_sc* handle);
static void effect_main_region_wait_for_fup_tr0(Slave_sc* handle);
static void effect_main_region__choice_0_tr0(Slave_sc* handle);
static void effect_main_region__choice_0_tr1(Slave_sc* handle);
static void effect_main_region__choice_1_tr0(Slave_sc* handle);
static void effect_main_region__choice_1_tr1(Slave_sc* handle);
static void effect_main_region__choice_2_tr0(Slave_sc* handle);
static void effect_main_region__choice_2_tr1(Slave_sc* handle);
static void effect_main_region__choice_3_tr0(Slave_sc* handle);
static void effect_main_region__choice_3_tr1(Slave_sc* handle);
static void effect_main_region__choice_4_tr1(Slave_sc* handle);
static void effect_main_region__choice_4_tr0(Slave_sc* handle);
static void enact_main_region_init(Slave_sc* handle);
static void enact_main_region_cycle_response_response(Slave_sc* handle);
static void enact_main_region_wait_for_sync(Slave_sc* handle);
static void enact_main_region_wait_for_sync_1(Slave_sc* handle);
static void enseq_main_region_init_default(Slave_sc* handle);
static void enseq_main_region_wait_for_followup_default(Slave_sc* handle);
static void enseq_main_region_cycle_default(Slave_sc* handle);
static void enseq_main_region_cycle_response_response_default(Slave_sc* handle);
static void enseq_main_region_cycle_response_timediff_default(Slave_sc* handle);
static void enseq_main_region_cycle_sync_wait_for_sync_default(Slave_sc* handle);
static void enseq_main_region_cycle_sync_wait_for_sync_slot_default(Slave_sc* handle);
static void enseq_main_region_cycle_followup_wait_default(Slave_sc* handle);
static void enseq_main_region_cycle_followup_wait_for_fup_slot_default(Slave_sc* handle);
static void enseq_main_region_wait_for_sync_default(Slave_sc* handle);
static void enseq_main_region_wait_for_sync_1_default(Slave_sc* handle);
static void enseq_main_region_wait_for_fup_default(Slave_sc* handle);
static void enseq_main_region_default(Slave_sc* handle);
static void enseq_main_region_cycle_response_default(Slave_sc* handle);
static void enseq_main_region_cycle_sync_default(Slave_sc* handle);
static void enseq_main_region_cycle_followup_default(Slave_sc* handle);
static void exseq_main_region_init(Slave_sc* handle);
static void exseq_main_region_wait_for_followup(Slave_sc* handle);
static void exseq_main_region_cycle(Slave_sc* handle);
static void exseq_main_region_cycle_response_response(Slave_sc* handle);
static void exseq_main_region_cycle_response_timediff(Slave_sc* handle);
static void exseq_main_region_cycle_sync_wait_for_sync(Slave_sc* handle);
static void exseq_main_region_cycle_sync_wait_for_sync_slot(Slave_sc* handle);
static void exseq_main_region_cycle_followup_wait(Slave_sc* handle);
static void exseq_main_region_cycle_followup_wait_for_fup_slot(Slave_sc* handle);
static void exseq_main_region_wait_for_sync(Slave_sc* handle);
static void exseq_main_region_wait_for_sync_1(Slave_sc* handle);
static void exseq_main_region_wait_for_fup(Slave_sc* handle);
static void exseq_main_region(Slave_sc* handle);
static void exseq_main_region_cycle_response(Slave_sc* handle);
static void exseq_main_region_cycle_sync(Slave_sc* handle);
static void exseq_main_region_cycle_followup(Slave_sc* handle);
static void react_main_region_init(Slave_sc* handle);
static void react_main_region_wait_for_followup(Slave_sc* handle);
static void react_main_region_cycle_response_response(Slave_sc* handle);
static void react_main_region_cycle_response_timediff(Slave_sc* handle);
static void react_main_region_cycle_sync_wait_for_sync(Slave_sc* handle);
static void react_main_region_cycle_sync_wait_for_sync_slot(Slave_sc* handle);
static void react_main_region_cycle_followup_wait(Slave_sc* handle);
static void react_main_region_cycle_followup_wait_for_fup_slot(Slave_sc* handle);
static void react_main_region_wait_for_sync(Slave_sc* handle);
static void react_main_region_wait_for_sync_1(Slave_sc* handle);
static void react_main_region_wait_for_fup(Slave_sc* handle);
static void react_main_region__choice_0(Slave_sc* handle);
static void react_main_region__choice_1(Slave_sc* handle);
static void react_main_region__choice_2(Slave_sc* handle);
static void react_main_region__choice_3(Slave_sc* handle);
static void react_main_region__choice_4(Slave_sc* handle);
static void react_main_region__entry_Default(Slave_sc* handle);
static void react_main_region_cycle_response__entry_Default(Slave_sc* handle);
static void react_main_region_cycle_sync__entry_Default(Slave_sc* handle);
static void react_main_region_cycle_followup__entry_Default(Slave_sc* handle);
static void react_main_region_cycle_sync__exit_Default(Slave_sc* handle);
static void react_main_region_cycle_followup__exit_Default(Slave_sc* handle);
static void clearInEvents(Slave_sc* handle);
static void clearOutEvents(Slave_sc* handle);


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
		handle->iface.own_id = 0;
		handle->iface.own_slot = 0;
		handle->iface.sensor_ts = 0;
		handle->internal.good_sync = 0;
		handle->internal.sync_tx_ts = 0;
		handle->internal.sync_rx_ts = 0;
		handle->internal.slave_time_diff = 0;
		handle->internal.master_time_diff = 0;
		handle->internal.offset = 0;
		handle->internal.delay = 0;
		handle->internal.drift = 0.0;
}

void slave_sc_enter(Slave_sc* handle)
{
	/* Default enter sequence for statechart slave_sc */
	enseq_main_region_default(handle);
}

void slave_sc_runCycle(Slave_sc* handle)
{
	clearOutEvents(handle);
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
		case Slave_sc_main_region_cycle_sync_wait_for_sync_slot:
		{
			react_main_region_cycle_sync_wait_for_sync_slot(handle);
			break;
		}
		case Slave_sc_main_region_cycle_followup_wait:
		{
			react_main_region_cycle_followup_wait(handle);
			break;
		}
		case Slave_sc_main_region_cycle_followup_wait_for_fup_slot:
		{
			react_main_region_cycle_followup_wait_for_fup_slot(handle);
			break;
		}
		case Slave_sc_main_region_wait_for_sync:
		{
			react_main_region_wait_for_sync(handle);
			break;
		}
		case Slave_sc_main_region_wait_for_sync_1:
		{
			react_main_region_wait_for_sync_1(handle);
			break;
		}
		case Slave_sc_main_region_wait_for_fup:
		{
			react_main_region_wait_for_fup(handle);
			break;
		}
		default:
			break;
		}
	}
	
	clearInEvents(handle);
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
				&& handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE] <= Slave_sc_main_region_cycle_followup_wait_for_fup_slot);
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
		case Slave_sc_main_region_cycle_sync_wait_for_sync_slot :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE_SYNC_WAIT_FOR_SYNC_SLOT] == Slave_sc_main_region_cycle_sync_wait_for_sync_slot
			);
			break;
		case Slave_sc_main_region_cycle_followup_wait :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE_FOLLOWUP_WAIT] == Slave_sc_main_region_cycle_followup_wait
			);
			break;
		case Slave_sc_main_region_cycle_followup_wait_for_fup_slot :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_CYCLE_FOLLOWUP_WAIT_FOR_FUP_SLOT] == Slave_sc_main_region_cycle_followup_wait_for_fup_slot
			);
			break;
		case Slave_sc_main_region_wait_for_sync :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_WAIT_FOR_SYNC] == Slave_sc_main_region_wait_for_sync
			);
			break;
		case Slave_sc_main_region_wait_for_sync_1 :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_WAIT_FOR_SYNC_1] == Slave_sc_main_region_wait_for_sync_1
			);
			break;
		case Slave_sc_main_region_wait_for_fup :
			result = (sc_boolean) (handle->stateConfVector[SCVI_SLAVE_SC_MAIN_REGION_WAIT_FOR_FUP] == Slave_sc_main_region_wait_for_fup
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
	handle->iface.slave_slot_raised = bool_false;
	handle->iface.sync_slot_raised = bool_false;
	handle->iface.followup_slot_raised = bool_false;
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
void slave_scIface_raise_slave_slot(Slave_sc* handle, int32_t value)
{
	handle->iface.slave_slot_value = value;
	handle->iface.slave_slot_raised = bool_true;
	
	slave_sc_runCycle(handle);
}
void slave_scIface_raise_sync_slot(Slave_sc* handle)
{
	handle->iface.sync_slot_raised = bool_true;
	
	slave_sc_runCycle(handle);
}
void slave_scIface_raise_followup_slot(Slave_sc* handle)
{
	handle->iface.followup_slot_raised = bool_true;
	
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
uint8_t slave_scIface_get_own_id(const Slave_sc* handle)
{
	return handle->iface.own_id;
}
void slave_scIface_set_own_id(Slave_sc* handle, uint8_t value)
{
	handle->iface.own_id = value;
}
int32_t slave_scIface_get_own_slot(const Slave_sc* handle)
{
	return handle->iface.own_slot;
}
void slave_scIface_set_own_slot(Slave_sc* handle, int32_t value)
{
	handle->iface.own_slot = value;
}
int64_t slave_scIface_get_sensor_ts(const Slave_sc* handle)
{
	return handle->iface.sensor_ts;
}
void slave_scIface_set_sensor_ts(Slave_sc* handle, int64_t value)
{
	handle->iface.sensor_ts = value;
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

static sc_boolean check_main_region_cycle_response_response_tr0_tr0(const Slave_sc* handle)
{
	return handle->iface.packet_sent_raised;
}

static sc_boolean check_main_region_cycle_response_timediff_tr0_tr0(const Slave_sc* handle)
{
	return ((handle->iface.slave_slot_raised) && (handle->iface.slave_slot_value == handle->iface.own_slot)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_cycle_sync_wait_for_sync_tr0_tr0(const Slave_sc* handle)
{
	return ((handle->iface.packet_received_raised) && (getPacketType(handle->iface.rx_packet) == SYNC)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_cycle_sync_wait_for_sync_tr1_tr1(const Slave_sc* handle)
{
	return handle->iface.followup_slot_raised;
}

static sc_boolean check_main_region_cycle_sync_wait_for_sync_slot_tr0_tr0(const Slave_sc* handle)
{
	return handle->iface.sync_slot_raised;
}

static sc_boolean check_main_region_cycle_followup_wait_tr0_tr0(const Slave_sc* handle)
{
	return ((handle->iface.packet_received_raised) && (getPacketType(handle->iface.rx_packet) == FOLLOW_UP)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_cycle_followup_wait_tr1_tr1(const Slave_sc* handle)
{
	return handle->iface.slave_slot_raised;
}

static sc_boolean check_main_region_cycle_followup_wait_for_fup_slot_tr0_tr0(const Slave_sc* handle)
{
	return handle->iface.followup_slot_raised;
}

static sc_boolean check_main_region_wait_for_sync_tr0_tr0(const Slave_sc* handle)
{
	return handle->iface.packet_received_raised;
}

static sc_boolean check_main_region_wait_for_sync_1_tr0_tr0(const Slave_sc* handle)
{
	return handle->iface.packet_received_raised;
}

static sc_boolean check_main_region_wait_for_fup_tr0_tr0(const Slave_sc* handle)
{
	return ((handle->iface.packet_received_raised) && (getPacketType(handle->iface.rx_packet) == FOLLOW_UP)) ? bool_true : bool_false;
}

static sc_boolean check_main_region__choice_0_tr0_tr0(const Slave_sc* handle)
{
	return (getPacketType(handle->iface.rx_packet) == SYNC) ? bool_true : bool_false;
}

static sc_boolean check_main_region__choice_0_tr1_tr1(const Slave_sc* handle)
{
	return bool_true;
}

static sc_boolean check_main_region__choice_1_tr0_tr0(const Slave_sc* handle)
{
	return (getPacketType(handle->iface.rx_packet) == SYNC) ? bool_true : bool_false;
}

static sc_boolean check_main_region__choice_1_tr1_tr1(const Slave_sc* handle)
{
	return bool_true;
}

static sc_boolean check_main_region__choice_2_tr0_tr0(const Slave_sc* handle)
{
	return (handle->internal.offset < 48 && handle->internal.offset > -48) ? bool_true : bool_false;
}

static sc_boolean check_main_region__choice_2_tr1_tr1(const Slave_sc* handle)
{
	return bool_true;
}

static sc_boolean check_main_region__choice_3_tr0_tr0(const Slave_sc* handle)
{
	return (handle->internal.good_sync > 9) ? bool_true : bool_false;
}

static sc_boolean check_main_region__choice_3_tr1_tr1(const Slave_sc* handle)
{
	return bool_true;
}

static sc_boolean check_main_region__choice_4_tr1_tr1(const Slave_sc* handle)
{
	return (handle->internal.offset > 48000 || handle->internal.offset < -48000) ? bool_true : bool_false;
}

static sc_boolean check_main_region__choice_4_tr0_tr0(const Slave_sc* handle)
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
	handle->internal.sync_tx_ts = getSyncTimeStamp(handle->iface.rx_packet);
	handle->internal.offset = handle->internal.sync_rx_ts - handle->internal.sync_tx_ts - handle->internal.delay;
	dbgPrintInt("offset:", handle->internal.offset);
	s_clockAddInt(-handle->internal.offset);
	handle->internal.sync_rx_ts = handle->internal.sync_tx_ts + handle->internal.delay;
	enseq_main_region_wait_for_sync_1_default(handle);
}

static void effect_main_region_cycle_tr0(Slave_sc* handle)
{
	exseq_main_region_cycle(handle);
	enseq_main_region_wait_for_sync_1_default(handle);
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
	handle->internal.master_time_diff = getDelayResp(handle->iface.rx_packet, handle->iface.own_slot);
	handle->internal.delay = handle->internal.master_time_diff == 0 ? handle->internal.delay : (handle->internal.master_time_diff - handle->internal.slave_time_diff) / 2;
	enseq_main_region_cycle_sync_wait_for_sync_slot_default(handle);
}

static void effect_main_region_cycle_sync_wait_for_sync_tr1(Slave_sc* handle)
{
	exseq_main_region_cycle_sync_wait_for_sync(handle);
	handle->internal.offset = 0;
	handle->internal.drift = PIcontroller(&(handle->internal.PIctrl), ((float) 0));
	s_clockDriftCorrection(fixedpt_fromxfloat(handle->internal.drift));
	dbgPrintStr("lostsync");
	react_main_region_cycle_sync__exit_Default(handle);
}

static void effect_main_region_cycle_sync_wait_for_sync_slot_tr0(Slave_sc* handle)
{
	exseq_main_region_cycle_sync_wait_for_sync_slot(handle);
	startRx();
	setMeasurement(tx_packet, handle->iface.sensor_ts);
	enseq_main_region_cycle_sync_wait_for_sync_default(handle);
}

static void effect_main_region_cycle_followup_wait_tr0(Slave_sc* handle)
{
	exseq_main_region_cycle_followup_wait(handle);
	handle->internal.sync_tx_ts = getSyncTimeStamp(handle->iface.rx_packet);
	handle->internal.offset = handle->internal.sync_rx_ts - handle->internal.sync_tx_ts - handle->internal.delay;
	handle->internal.drift = PIcontroller(&(handle->internal.PIctrl), (((float) handle->internal.offset)) / FRAME_LENGTH);
	s_clockDriftCorrection(fixedpt_fromxfloat(-handle->internal.drift));
	logPrint(handle->internal.offset, handle->internal.delay, ((int32_t) (handle->internal.PIctrl.I * 1000)));
	enseq_main_region_cycle_followup_wait_for_fup_slot_default(handle);
}

static void effect_main_region_cycle_followup_wait_tr1(Slave_sc* handle)
{
	exseq_main_region_cycle_followup_wait(handle);
	handle->internal.offset = 0;
	handle->internal.drift = PIcontroller(&(handle->internal.PIctrl), ((float) 0));
	s_clockDriftCorrection(fixedpt_fromxfloat(handle->internal.drift));
	dbgPrintStr("lostsync");
	react_main_region_cycle_followup__exit_Default(handle);
}

static void effect_main_region_cycle_followup_wait_for_fup_slot_tr0(Slave_sc* handle)
{
	exseq_main_region_cycle_followup_wait_for_fup_slot(handle);
	startRx();
	enseq_main_region_cycle_followup_wait_default(handle);
}

static void effect_main_region_wait_for_sync_tr0(Slave_sc* handle)
{
	exseq_main_region_wait_for_sync(handle);
	react_main_region__choice_0(handle);
}

static void effect_main_region_wait_for_sync_1_tr0(Slave_sc* handle)
{
	exseq_main_region_wait_for_sync_1(handle);
	react_main_region__choice_1(handle);
}

static void effect_main_region_wait_for_fup_tr0(Slave_sc* handle)
{
	exseq_main_region_wait_for_fup(handle);
	handle->internal.sync_tx_ts = getSyncTimeStamp(handle->iface.rx_packet);
	handle->internal.offset = handle->internal.sync_rx_ts - handle->internal.sync_tx_ts - handle->internal.delay;
	handle->internal.drift = PIcontroller(&(handle->internal.PIctrl), (((float) handle->internal.offset)) / FRAME_LENGTH);
	logPrint(handle->internal.offset, handle->internal.delay, ((int32_t) (handle->internal.PIctrl.I * 1000)));
	s_clockDriftCorrection(fixedpt_fromxfloat(-handle->internal.drift));
	react_main_region__choice_2(handle);
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

static void effect_main_region__choice_1_tr0(Slave_sc* handle)
{
	handle->internal.sync_rx_ts = handle->iface.packet_received_value;
	startRx();
	enseq_main_region_wait_for_fup_default(handle);
}

static void effect_main_region__choice_1_tr1(Slave_sc* handle)
{
	enseq_main_region_wait_for_sync_1_default(handle);
}

static void effect_main_region__choice_2_tr0(Slave_sc* handle)
{
	handle->internal.good_sync++;
	react_main_region__choice_3(handle);
}

static void effect_main_region__choice_2_tr1(Slave_sc* handle)
{
	handle->internal.good_sync = 0;
	react_main_region__choice_4(handle);
}

static void effect_main_region__choice_3_tr0(Slave_sc* handle)
{
	dbgPrintStr("synced");
	setMeasurement(tx_packet, ((int32_t) handle->internal.offset));
	enseq_main_region_cycle_default(handle);
}

static void effect_main_region__choice_3_tr1(Slave_sc* handle)
{
	enseq_main_region_wait_for_sync_1_default(handle);
}

static void effect_main_region__choice_4_tr1(Slave_sc* handle)
{
	enseq_main_region_init_default(handle);
}

static void effect_main_region__choice_4_tr0(Slave_sc* handle)
{
	enseq_main_region_wait_for_sync_1_default(handle);
}

/* Entry action for state 'init'. */
static void enact_main_region_init(Slave_sc* handle)
{
	/* Entry action for state 'init'. */
	setSourceAddress(tx_packet, handle->iface.own_id);
	setPacketType(tx_packet, SLAVE);
	handle->internal.PIctrl.Kp = ((float) (1.0 / 4));
	handle->internal.PIctrl.Ki = ((float) (1.0 / 64));
	handle->internal.PIctrl.I = ((float) 0);
	handle->internal.delay = -3118;
	s_clockDriftReset();
	dbgPrintStr("start");
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

/* Entry action for state 'wait for sync 1'. */
static void enact_main_region_wait_for_sync_1(Slave_sc* handle)
{
	/* Entry action for state 'wait for sync 1'. */
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
	enseq_main_region_cycle_response_default(handle);
	enseq_main_region_cycle_sync_default(handle);
	enseq_main_region_cycle_followup_default(handle);
}

/* 'default' enter sequence for state response */
static void enseq_main_region_cycle_response_response_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state response */
	enact_main_region_cycle_response_response(handle);
	handle->stateConfVector[0] = Slave_sc_main_region_cycle_response_response;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state timediff */
static void enseq_main_region_cycle_response_timediff_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state timediff */
	handle->stateConfVector[0] = Slave_sc_main_region_cycle_response_timediff;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state wait for sync */
static void enseq_main_region_cycle_sync_wait_for_sync_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait for sync */
	handle->stateConfVector[1] = Slave_sc_main_region_cycle_sync_wait_for_sync;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state wait for sync slot */
static void enseq_main_region_cycle_sync_wait_for_sync_slot_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait for sync slot */
	handle->stateConfVector[1] = Slave_sc_main_region_cycle_sync_wait_for_sync_slot;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state wait */
static void enseq_main_region_cycle_followup_wait_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait */
	handle->stateConfVector[2] = Slave_sc_main_region_cycle_followup_wait;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state wait for fup slot */
static void enseq_main_region_cycle_followup_wait_for_fup_slot_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait for fup slot */
	handle->stateConfVector[2] = Slave_sc_main_region_cycle_followup_wait_for_fup_slot;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state wait for sync */
static void enseq_main_region_wait_for_sync_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait for sync */
	enact_main_region_wait_for_sync(handle);
	handle->stateConfVector[0] = Slave_sc_main_region_wait_for_sync;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state wait for sync 1 */
static void enseq_main_region_wait_for_sync_1_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait for sync 1 */
	enact_main_region_wait_for_sync_1(handle);
	handle->stateConfVector[0] = Slave_sc_main_region_wait_for_sync_1;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state wait for fup */
static void enseq_main_region_wait_for_fup_default(Slave_sc* handle)
{
	/* 'default' enter sequence for state wait for fup */
	handle->stateConfVector[0] = Slave_sc_main_region_wait_for_fup;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(Slave_sc* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
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

/* Default exit sequence for state cycle */
static void exseq_main_region_cycle(Slave_sc* handle)
{
	/* Default exit sequence for state cycle */
	exseq_main_region_cycle_response(handle);
	exseq_main_region_cycle_sync(handle);
	exseq_main_region_cycle_followup(handle);
}

/* Default exit sequence for state response */
static void exseq_main_region_cycle_response_response(Slave_sc* handle)
{
	/* Default exit sequence for state response */
	handle->stateConfVector[0] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state timediff */
static void exseq_main_region_cycle_response_timediff(Slave_sc* handle)
{
	/* Default exit sequence for state timediff */
	handle->stateConfVector[0] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state wait for sync */
static void exseq_main_region_cycle_sync_wait_for_sync(Slave_sc* handle)
{
	/* Default exit sequence for state wait for sync */
	handle->stateConfVector[1] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state wait for sync slot */
static void exseq_main_region_cycle_sync_wait_for_sync_slot(Slave_sc* handle)
{
	/* Default exit sequence for state wait for sync slot */
	handle->stateConfVector[1] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state wait */
static void exseq_main_region_cycle_followup_wait(Slave_sc* handle)
{
	/* Default exit sequence for state wait */
	handle->stateConfVector[2] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 2;
}

/* Default exit sequence for state wait for fup slot */
static void exseq_main_region_cycle_followup_wait_for_fup_slot(Slave_sc* handle)
{
	/* Default exit sequence for state wait for fup slot */
	handle->stateConfVector[2] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 2;
}

/* Default exit sequence for state wait for sync */
static void exseq_main_region_wait_for_sync(Slave_sc* handle)
{
	/* Default exit sequence for state wait for sync */
	handle->stateConfVector[0] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state wait for sync 1 */
static void exseq_main_region_wait_for_sync_1(Slave_sc* handle)
{
	/* Default exit sequence for state wait for sync 1 */
	handle->stateConfVector[0] = Slave_sc_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state wait for fup */
static void exseq_main_region_wait_for_fup(Slave_sc* handle)
{
	/* Default exit sequence for state wait for fup */
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
		case Slave_sc_main_region_wait_for_sync :
		{
			exseq_main_region_wait_for_sync(handle);
			break;
		}
		case Slave_sc_main_region_wait_for_sync_1 :
		{
			exseq_main_region_wait_for_sync_1(handle);
			break;
		}
		case Slave_sc_main_region_wait_for_fup :
		{
			exseq_main_region_wait_for_fup(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of slave_sc.main_region) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Slave_sc_main_region_cycle_sync_wait_for_sync :
		{
			exseq_main_region_cycle_sync_wait_for_sync(handle);
			break;
		}
		case Slave_sc_main_region_cycle_sync_wait_for_sync_slot :
		{
			exseq_main_region_cycle_sync_wait_for_sync_slot(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of slave_sc.main_region) at position 2... */
	switch(handle->stateConfVector[ 2 ])
	{
		case Slave_sc_main_region_cycle_followup_wait :
		{
			exseq_main_region_cycle_followup_wait(handle);
			break;
		}
		case Slave_sc_main_region_cycle_followup_wait_for_fup_slot :
		{
			exseq_main_region_cycle_followup_wait_for_fup_slot(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region response */
static void exseq_main_region_cycle_response(Slave_sc* handle)
{
	/* Default exit sequence for region response */
	/* Handle exit of all possible states (of slave_sc.main_region.cycle.response) at position 0... */
	switch(handle->stateConfVector[ 0 ])
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
	/* Handle exit of all possible states (of slave_sc.main_region.cycle.sync) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Slave_sc_main_region_cycle_sync_wait_for_sync :
		{
			exseq_main_region_cycle_sync_wait_for_sync(handle);
			break;
		}
		case Slave_sc_main_region_cycle_sync_wait_for_sync_slot :
		{
			exseq_main_region_cycle_sync_wait_for_sync_slot(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region followup */
static void exseq_main_region_cycle_followup(Slave_sc* handle)
{
	/* Default exit sequence for region followup */
	/* Handle exit of all possible states (of slave_sc.main_region.cycle.followup) at position 2... */
	switch(handle->stateConfVector[ 2 ])
	{
		case Slave_sc_main_region_cycle_followup_wait :
		{
			exseq_main_region_cycle_followup_wait(handle);
			break;
		}
		case Slave_sc_main_region_cycle_followup_wait_for_fup_slot :
		{
			exseq_main_region_cycle_followup_wait_for_fup_slot(handle);
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
	}  else
	{
		if (check_main_region_cycle_sync_wait_for_sync_tr1_tr1(handle) == bool_true)
		{ 
			effect_main_region_cycle_sync_wait_for_sync_tr1(handle);
		} 
	}
}

/* The reactions of state wait for sync slot. */
static void react_main_region_cycle_sync_wait_for_sync_slot(Slave_sc* handle)
{
	/* The reactions of state wait for sync slot. */
	if (check_main_region_cycle_sync_wait_for_sync_slot_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_cycle_sync_wait_for_sync_slot_tr0(handle);
	} 
}

/* The reactions of state wait. */
static void react_main_region_cycle_followup_wait(Slave_sc* handle)
{
	/* The reactions of state wait. */
	if (check_main_region_cycle_followup_wait_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_cycle_followup_wait_tr0(handle);
	}  else
	{
		if (check_main_region_cycle_followup_wait_tr1_tr1(handle) == bool_true)
		{ 
			effect_main_region_cycle_followup_wait_tr1(handle);
		} 
	}
}

/* The reactions of state wait for fup slot. */
static void react_main_region_cycle_followup_wait_for_fup_slot(Slave_sc* handle)
{
	/* The reactions of state wait for fup slot. */
	if (check_main_region_cycle_followup_wait_for_fup_slot_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_cycle_followup_wait_for_fup_slot_tr0(handle);
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

/* The reactions of state wait for sync 1. */
static void react_main_region_wait_for_sync_1(Slave_sc* handle)
{
	/* The reactions of state wait for sync 1. */
	if (check_main_region_wait_for_sync_1_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_wait_for_sync_1_tr0(handle);
	} 
}

/* The reactions of state wait for fup. */
static void react_main_region_wait_for_fup(Slave_sc* handle)
{
	/* The reactions of state wait for fup. */
	if (check_main_region_wait_for_fup_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_wait_for_fup_tr0(handle);
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

/* The reactions of state null. */
static void react_main_region__choice_1(Slave_sc* handle)
{
	/* The reactions of state null. */
	if (check_main_region__choice_1_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region__choice_1_tr0(handle);
	}  else
	{
		effect_main_region__choice_1_tr1(handle);
	}
}

/* The reactions of state null. */
static void react_main_region__choice_2(Slave_sc* handle)
{
	/* The reactions of state null. */
	if (check_main_region__choice_2_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region__choice_2_tr0(handle);
	}  else
	{
		effect_main_region__choice_2_tr1(handle);
	}
}

/* The reactions of state null. */
static void react_main_region__choice_3(Slave_sc* handle)
{
	/* The reactions of state null. */
	if (check_main_region__choice_3_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region__choice_3_tr0(handle);
	}  else
	{
		effect_main_region__choice_3_tr1(handle);
	}
}

/* The reactions of state null. */
static void react_main_region__choice_4(Slave_sc* handle)
{
	/* The reactions of state null. */
	if (check_main_region__choice_4_tr1_tr1(handle) == bool_true)
	{ 
		effect_main_region__choice_4_tr1(handle);
	}  else
	{
		effect_main_region__choice_4_tr0(handle);
	}
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(Slave_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_init_default(handle);
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
	enseq_main_region_cycle_sync_wait_for_sync_slot_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_cycle_followup__entry_Default(Slave_sc* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_cycle_followup_wait_for_fup_slot_default(handle);
}

/* The reactions of exit default. */
static void react_main_region_cycle_sync__exit_Default(Slave_sc* handle)
{
	/* The reactions of exit default. */
	effect_main_region_cycle_tr0(handle);
}

/* The reactions of exit default. */
static void react_main_region_cycle_followup__exit_Default(Slave_sc* handle)
{
	/* The reactions of exit default. */
	effect_main_region_cycle_tr0(handle);
}


