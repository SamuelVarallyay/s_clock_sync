
#include "Timesync_master.h"
#include "..\src\sc_types.h"
#include "Timesync_masterRequired.h"

#include <stdlib.h>
#include <string.h>
/*! \file Implementation of the state machine 'timesync_master'
*/

/* prototypes of all internal functions */
static sc_boolean check_sync_SendSync_lr0_lr0(const Timesync_master* handle);
static sc_boolean check_sync_SendSync_tr0_tr0(const Timesync_master* handle);
static sc_boolean check_sync_S2_r1_wait_tr0_tr0(const Timesync_master* handle);
static sc_boolean check_sync_S2_r1_ready_tr0_timesync_master_sync__sync1join_check(const Timesync_master* handle);
static sc_boolean check_sync_S2_r1_SendFollowUp_lr0_lr0(const Timesync_master* handle);
static sc_boolean check_sync_S2_r1_SendFollowUp_tr0_tr0(const Timesync_master* handle);
static sc_boolean check_sync_S2_r2_wait_tr0_tr0(const Timesync_master* handle);
static sc_boolean check_sync_S2_r2_ready_tr0_timesync_master_sync__sync1join_check(const Timesync_master* handle);
static void effect_sync_SendSync_lr0_lr0(Timesync_master* handle);
static void effect_sync_SendSync_tr0(Timesync_master* handle);
static void effect_sync_S2_r1_wait_tr0(Timesync_master* handle);
static void effect_sync_S2_r1_ready_tr0(Timesync_master* handle);
static void effect_sync_S2_r1_SendFollowUp_lr0_lr0(Timesync_master* handle);
static void effect_sync_S2_r1_SendFollowUp_tr0(Timesync_master* handle);
static void effect_sync_S2_r2_wait_tr0(Timesync_master* handle);
static void effect_sync_S2_r2_ready_tr0(Timesync_master* handle);
static void enact_sync_S2_r2_wait(Timesync_master* handle);
static void exact_sync_SendSync(Timesync_master* handle);
static void exact_sync_S2_r1_SendFollowUp(Timesync_master* handle);
static void exact_sync_S2_r2_wait(Timesync_master* handle);
static void enseq_sync_SendSync_default(Timesync_master* handle);
static void enseq_sync_S2_r1_wait_default(Timesync_master* handle);
static void enseq_sync_S2_r1_ready_default(Timesync_master* handle);
static void enseq_sync_S2_r1_SendFollowUp_default(Timesync_master* handle);
static void enseq_sync_S2_r2_wait_default(Timesync_master* handle);
static void enseq_sync_S2_r2_ready_default(Timesync_master* handle);
static void enseq_sync_default(Timesync_master* handle);
static void exseq_sync_SendSync(Timesync_master* handle);
static void exseq_sync_S2(Timesync_master* handle);
static void exseq_sync_S2_r1_wait(Timesync_master* handle);
static void exseq_sync_S2_r1_ready(Timesync_master* handle);
static void exseq_sync_S2_r1_SendFollowUp(Timesync_master* handle);
static void exseq_sync_S2_r2_wait(Timesync_master* handle);
static void exseq_sync_S2_r2_ready(Timesync_master* handle);
static void exseq_sync(Timesync_master* handle);
static void exseq_sync_S2_r1(Timesync_master* handle);
static void exseq_sync_S2_r2(Timesync_master* handle);
static void react_sync_SendSync(Timesync_master* handle);
static void react_sync_S2_r1_wait(Timesync_master* handle);
static void react_sync_S2_r1_ready(Timesync_master* handle);
static void react_sync_S2_r1_SendFollowUp(Timesync_master* handle);
static void react_sync_S2_r2_wait(Timesync_master* handle);
static void react_sync_S2_r2_ready(Timesync_master* handle);
static void react_sync__entry_Default(Timesync_master* handle);
static void react_sync__sync0(Timesync_master* handle);
static void react_sync__sync1(Timesync_master* handle);
static void clearInEvents(Timesync_master* handle);
static void clearOutEvents(Timesync_master* handle);


void timesync_master_init(Timesync_master* handle)
{
		sc_integer i;
	
		for (i = 0; i < TIMESYNC_MASTER_MAX_ORTHOGONAL_STATES; ++i)
		{
			handle->stateConfVector[i] = Timesync_master_last_state;
		}
		
		
		handle->stateConfVectorPosition = 0;
	
		clearInEvents(handle);
		clearOutEvents(handle);
	
		/* Default init sequence for statechart timesync_master */
		handle->iface.t = 0;
		handle->iface.errorCode = 1;
}

void timesync_master_enter(Timesync_master* handle)
{
	/* Default enter sequence for statechart timesync_master */
	enseq_sync_default(handle);
}

void timesync_master_runCycle(Timesync_master* handle)
{
	clearOutEvents(handle);
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < TIMESYNC_MASTER_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case Timesync_master_sync_SendSync:
		{
			react_sync_SendSync(handle);
			break;
		}
		case Timesync_master_sync_S2_r1_wait:
		{
			react_sync_S2_r1_wait(handle);
			break;
		}
		case Timesync_master_sync_S2_r1_ready:
		{
			react_sync_S2_r1_ready(handle);
			break;
		}
		case Timesync_master_sync_S2_r1_SendFollowUp:
		{
			react_sync_S2_r1_SendFollowUp(handle);
			break;
		}
		case Timesync_master_sync_S2_r2_wait:
		{
			react_sync_S2_r2_wait(handle);
			break;
		}
		case Timesync_master_sync_S2_r2_ready:
		{
			react_sync_S2_r2_ready(handle);
			break;
		}
		default:
			break;
		}
	}
	
	clearInEvents(handle);
}

void timesync_master_exit(Timesync_master* handle)
{
	/* Default exit sequence for statechart timesync_master */
	exseq_sync(handle);
}

sc_boolean timesync_master_isActive(const Timesync_master* handle)
{
	sc_boolean result = bool_false;
	int i;
	
	for(i = 0; i < TIMESYNC_MASTER_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Timesync_master_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean timesync_master_isFinal(const Timesync_master* handle)
{
   return bool_false;
}

void timesync_master_raiseTimeEvent(Timesync_master* handle, sc_eventid evid)
{
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + sizeof(Timesync_masterTimeEvents))
		{
		*(sc_boolean*)evid = bool_true;
	}		
}

sc_boolean timesync_master_isStateActive(const Timesync_master* handle, Timesync_masterStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Timesync_master_sync_SendSync :
			result = (sc_boolean) (handle->stateConfVector[SCVI_TIMESYNC_MASTER_SYNC_SENDSYNC] == Timesync_master_sync_SendSync
			);
			break;
		case Timesync_master_sync_S2 :
			result = (sc_boolean) (handle->stateConfVector[SCVI_TIMESYNC_MASTER_SYNC_S2] >= Timesync_master_sync_S2
				&& handle->stateConfVector[SCVI_TIMESYNC_MASTER_SYNC_S2] <= Timesync_master_sync_S2_r2_ready);
			break;
		case Timesync_master_sync_S2_r1_wait :
			result = (sc_boolean) (handle->stateConfVector[SCVI_TIMESYNC_MASTER_SYNC_S2_R1_WAIT] == Timesync_master_sync_S2_r1_wait
			);
			break;
		case Timesync_master_sync_S2_r1_ready :
			result = (sc_boolean) (handle->stateConfVector[SCVI_TIMESYNC_MASTER_SYNC_S2_R1_READY] == Timesync_master_sync_S2_r1_ready
			);
			break;
		case Timesync_master_sync_S2_r1_SendFollowUp :
			result = (sc_boolean) (handle->stateConfVector[SCVI_TIMESYNC_MASTER_SYNC_S2_R1_SENDFOLLOWUP] == Timesync_master_sync_S2_r1_SendFollowUp
			);
			break;
		case Timesync_master_sync_S2_r2_wait :
			result = (sc_boolean) (handle->stateConfVector[SCVI_TIMESYNC_MASTER_SYNC_S2_R2_WAIT] == Timesync_master_sync_S2_r2_wait
			);
			break;
		case Timesync_master_sync_S2_r2_ready :
			result = (sc_boolean) (handle->stateConfVector[SCVI_TIMESYNC_MASTER_SYNC_S2_R2_READY] == Timesync_master_sync_S2_r2_ready
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}

static void clearInEvents(Timesync_master* handle)
{
	handle->iface.syncSent_raised = bool_false;
	handle->timeEvents.timesync_master_sync_S2_r2_wait_tev0_raised = bool_false;
}

static void clearOutEvents(Timesync_master* handle)
{
}

void timesync_masterIface_raise_syncSent(Timesync_master* handle)
{
	handle->iface.syncSent_raised = bool_true;
}


sc_integer timesync_masterIface_get_t(const Timesync_master* handle)
{
	return handle->iface.t;
}
void timesync_masterIface_set_t(Timesync_master* handle, sc_integer value)
{
	handle->iface.t = value;
}
sc_integer timesync_masterIface_get_errorCode(const Timesync_master* handle)
{
	return handle->iface.errorCode;
}
void timesync_masterIface_set_errorCode(Timesync_master* handle, sc_integer value)
{
	handle->iface.errorCode = value;
}

/* implementations of all internal functions */

static sc_boolean check_sync_SendSync_lr0_lr0(const Timesync_master* handle)
{
	return bool_true;
}

static sc_boolean check_sync_SendSync_tr0_tr0(const Timesync_master* handle)
{
	return (handle->iface.errorCode == 0) ? bool_true : bool_false;
}

static sc_boolean check_sync_S2_r1_wait_tr0_tr0(const Timesync_master* handle)
{
	return handle->iface.syncSent_raised;
}

static sc_boolean check_sync_S2_r1_ready_tr0_timesync_master_sync__sync1join_check(const Timesync_master* handle)
{
	return timesync_master_isStateActive(handle, Timesync_master_sync_S2_r2_ready);
}

static sc_boolean check_sync_S2_r1_SendFollowUp_lr0_lr0(const Timesync_master* handle)
{
	return bool_true;
}

static sc_boolean check_sync_S2_r1_SendFollowUp_tr0_tr0(const Timesync_master* handle)
{
	return (handle->iface.errorCode == 0) ? bool_true : bool_false;
}

static sc_boolean check_sync_S2_r2_wait_tr0_tr0(const Timesync_master* handle)
{
	return handle->timeEvents.timesync_master_sync_S2_r2_wait_tev0_raised;
}

static sc_boolean check_sync_S2_r2_ready_tr0_timesync_master_sync__sync1join_check(const Timesync_master* handle)
{
	return timesync_master_isStateActive(handle, Timesync_master_sync_S2_r1_ready);
}

static void effect_sync_SendSync_lr0_lr0(Timesync_master* handle)
{
	handle->iface.errorCode = timesync_masterIface_sendSync(handle);
}

static void effect_sync_SendSync_tr0(Timesync_master* handle)
{
	exseq_sync_SendSync(handle);
	react_sync__sync0(handle);
}

static void effect_sync_S2_r1_wait_tr0(Timesync_master* handle)
{
	exseq_sync_S2_r1_wait(handle);
	enseq_sync_S2_r1_SendFollowUp_default(handle);
}

static void effect_sync_S2_r1_ready_tr0(Timesync_master* handle)
{
	exseq_sync_S2(handle);
	react_sync__sync1(handle);
}

static void effect_sync_S2_r1_SendFollowUp_lr0_lr0(Timesync_master* handle)
{
	handle->iface.errorCode = timesync_masterIface_sendFollowUp(handle);
}

static void effect_sync_S2_r1_SendFollowUp_tr0(Timesync_master* handle)
{
	exseq_sync_S2_r1_SendFollowUp(handle);
	enseq_sync_S2_r1_ready_default(handle);
}

static void effect_sync_S2_r2_wait_tr0(Timesync_master* handle)
{
	exseq_sync_S2_r2_wait(handle);
	enseq_sync_S2_r2_ready_default(handle);
}

static void effect_sync_S2_r2_ready_tr0(Timesync_master* handle)
{
	exseq_sync_S2(handle);
	react_sync__sync1(handle);
}

/* Entry action for state 'wait'. */
static void enact_sync_S2_r2_wait(Timesync_master* handle)
{
	/* Entry action for state 'wait'. */
	timesync_master_setTimer(handle, (sc_eventid) &(handle->timeEvents.timesync_master_sync_S2_r2_wait_tev0_raised) , handle->iface.t, bool_false);
}

/* Exit action for state 'SendSync'. */
static void exact_sync_SendSync(Timesync_master* handle)
{
	/* Exit action for state 'SendSync'. */
	handle->iface.errorCode = 1;
	handle->iface.t = timesync_masterIface_getPeriod(handle);
}

/* Exit action for state 'SendFollowUp'. */
static void exact_sync_S2_r1_SendFollowUp(Timesync_master* handle)
{
	/* Exit action for state 'SendFollowUp'. */
	handle->iface.errorCode = 1;
}

/* Exit action for state 'wait'. */
static void exact_sync_S2_r2_wait(Timesync_master* handle)
{
	/* Exit action for state 'wait'. */
	timesync_master_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.timesync_master_sync_S2_r2_wait_tev0_raised) );		
}

/* 'default' enter sequence for state SendSync */
static void enseq_sync_SendSync_default(Timesync_master* handle)
{
	/* 'default' enter sequence for state SendSync */
	handle->stateConfVector[0] = Timesync_master_sync_SendSync;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state wait */
static void enseq_sync_S2_r1_wait_default(Timesync_master* handle)
{
	/* 'default' enter sequence for state wait */
	handle->stateConfVector[0] = Timesync_master_sync_S2_r1_wait;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state ready */
static void enseq_sync_S2_r1_ready_default(Timesync_master* handle)
{
	/* 'default' enter sequence for state ready */
	handle->stateConfVector[0] = Timesync_master_sync_S2_r1_ready;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state SendFollowUp */
static void enseq_sync_S2_r1_SendFollowUp_default(Timesync_master* handle)
{
	/* 'default' enter sequence for state SendFollowUp */
	handle->stateConfVector[0] = Timesync_master_sync_S2_r1_SendFollowUp;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state wait */
static void enseq_sync_S2_r2_wait_default(Timesync_master* handle)
{
	/* 'default' enter sequence for state wait */
	enact_sync_S2_r2_wait(handle);
	handle->stateConfVector[1] = Timesync_master_sync_S2_r2_wait;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state ready */
static void enseq_sync_S2_r2_ready_default(Timesync_master* handle)
{
	/* 'default' enter sequence for state ready */
	handle->stateConfVector[1] = Timesync_master_sync_S2_r2_ready;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for region sync */
static void enseq_sync_default(Timesync_master* handle)
{
	/* 'default' enter sequence for region sync */
	react_sync__entry_Default(handle);
}

/* Default exit sequence for state SendSync */
static void exseq_sync_SendSync(Timesync_master* handle)
{
	/* Default exit sequence for state SendSync */
	handle->stateConfVector[0] = Timesync_master_last_state;
	handle->stateConfVectorPosition = 0;
	exact_sync_SendSync(handle);
}

/* Default exit sequence for state S2 */
static void exseq_sync_S2(Timesync_master* handle)
{
	/* Default exit sequence for state S2 */
	exseq_sync_S2_r1(handle);
	exseq_sync_S2_r2(handle);
}

/* Default exit sequence for state wait */
static void exseq_sync_S2_r1_wait(Timesync_master* handle)
{
	/* Default exit sequence for state wait */
	handle->stateConfVector[0] = Timesync_master_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state ready */
static void exseq_sync_S2_r1_ready(Timesync_master* handle)
{
	/* Default exit sequence for state ready */
	handle->stateConfVector[0] = Timesync_master_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state SendFollowUp */
static void exseq_sync_S2_r1_SendFollowUp(Timesync_master* handle)
{
	/* Default exit sequence for state SendFollowUp */
	handle->stateConfVector[0] = Timesync_master_last_state;
	handle->stateConfVectorPosition = 0;
	exact_sync_S2_r1_SendFollowUp(handle);
}

/* Default exit sequence for state wait */
static void exseq_sync_S2_r2_wait(Timesync_master* handle)
{
	/* Default exit sequence for state wait */
	handle->stateConfVector[1] = Timesync_master_last_state;
	handle->stateConfVectorPosition = 1;
	exact_sync_S2_r2_wait(handle);
}

/* Default exit sequence for state ready */
static void exseq_sync_S2_r2_ready(Timesync_master* handle)
{
	/* Default exit sequence for state ready */
	handle->stateConfVector[1] = Timesync_master_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for region sync */
static void exseq_sync(Timesync_master* handle)
{
	/* Default exit sequence for region sync */
	/* Handle exit of all possible states (of timesync_master.sync) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Timesync_master_sync_SendSync :
		{
			exseq_sync_SendSync(handle);
			break;
		}
		case Timesync_master_sync_S2_r1_wait :
		{
			exseq_sync_S2_r1_wait(handle);
			break;
		}
		case Timesync_master_sync_S2_r1_ready :
		{
			exseq_sync_S2_r1_ready(handle);
			break;
		}
		case Timesync_master_sync_S2_r1_SendFollowUp :
		{
			exseq_sync_S2_r1_SendFollowUp(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of timesync_master.sync) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Timesync_master_sync_S2_r2_wait :
		{
			exseq_sync_S2_r2_wait(handle);
			break;
		}
		case Timesync_master_sync_S2_r2_ready :
		{
			exseq_sync_S2_r2_ready(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void exseq_sync_S2_r1(Timesync_master* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of timesync_master.sync.S2.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Timesync_master_sync_S2_r1_wait :
		{
			exseq_sync_S2_r1_wait(handle);
			break;
		}
		case Timesync_master_sync_S2_r1_ready :
		{
			exseq_sync_S2_r1_ready(handle);
			break;
		}
		case Timesync_master_sync_S2_r1_SendFollowUp :
		{
			exseq_sync_S2_r1_SendFollowUp(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r2 */
static void exseq_sync_S2_r2(Timesync_master* handle)
{
	/* Default exit sequence for region r2 */
	/* Handle exit of all possible states (of timesync_master.sync.S2.r2) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Timesync_master_sync_S2_r2_wait :
		{
			exseq_sync_S2_r2_wait(handle);
			break;
		}
		case Timesync_master_sync_S2_r2_ready :
		{
			exseq_sync_S2_r2_ready(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state SendSync. */
static void react_sync_SendSync(Timesync_master* handle)
{
	/* The reactions of state SendSync. */
	if (check_sync_SendSync_tr0_tr0(handle) == bool_true)
	{ 
		effect_sync_SendSync_tr0(handle);
	}  else
	{
		effect_sync_SendSync_lr0_lr0(handle);
	}
}

/* The reactions of state wait. */
static void react_sync_S2_r1_wait(Timesync_master* handle)
{
	/* The reactions of state wait. */
	if (check_sync_S2_r1_wait_tr0_tr0(handle) == bool_true)
	{ 
		effect_sync_S2_r1_wait_tr0(handle);
	} 
}

/* The reactions of state ready. */
static void react_sync_S2_r1_ready(Timesync_master* handle)
{
	/* The reactions of state ready. */
	if (check_sync_S2_r1_ready_tr0_timesync_master_sync__sync1join_check(handle) == bool_true)
	{ 
		effect_sync_S2_r1_ready_tr0(handle);
	} 
}

/* The reactions of state SendFollowUp. */
static void react_sync_S2_r1_SendFollowUp(Timesync_master* handle)
{
	/* The reactions of state SendFollowUp. */
	if (check_sync_S2_r1_SendFollowUp_tr0_tr0(handle) == bool_true)
	{ 
		effect_sync_S2_r1_SendFollowUp_tr0(handle);
	}  else
	{
		effect_sync_S2_r1_SendFollowUp_lr0_lr0(handle);
	}
}

/* The reactions of state wait. */
static void react_sync_S2_r2_wait(Timesync_master* handle)
{
	/* The reactions of state wait. */
	if (check_sync_S2_r2_wait_tr0_tr0(handle) == bool_true)
	{ 
		effect_sync_S2_r2_wait_tr0(handle);
	} 
}

/* The reactions of state ready. */
static void react_sync_S2_r2_ready(Timesync_master* handle)
{
	/* The reactions of state ready. */
	if (check_sync_S2_r2_ready_tr0_timesync_master_sync__sync1join_check(handle) == bool_true)
	{ 
		effect_sync_S2_r2_ready_tr0(handle);
	} 
}

/* Default react sequence for initial entry  */
static void react_sync__entry_Default(Timesync_master* handle)
{
	/* Default react sequence for initial entry  */
	enseq_sync_SendSync_default(handle);
}

/* The reactions of state null. */
static void react_sync__sync0(Timesync_master* handle)
{
	/* The reactions of state null. */
	enseq_sync_S2_r1_wait_default(handle);
	enseq_sync_S2_r2_wait_default(handle);
}

/* The reactions of state null. */
static void react_sync__sync1(Timesync_master* handle)
{
	/* The reactions of state null. */
	enseq_sync_SendSync_default(handle);
}


