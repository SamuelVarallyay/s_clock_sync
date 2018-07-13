
#include <stdlib.h>
#include <string.h>
#include "..\src\sc_types.h"
#include "Timesync_slave.h"
/*! \file Implementation of the state machine 'timesync_slave'
*/

/* prototypes of all internal functions */
static void enseq_sync_a_default(Timesync_slave* handle);
static void enseq_sync_default(Timesync_slave* handle);
static void exseq_sync_a(Timesync_slave* handle);
static void exseq_sync(Timesync_slave* handle);
static void react_sync_a(Timesync_slave* handle);
static void react_sync__entry_Default(Timesync_slave* handle);
static void clearInEvents(Timesync_slave* handle);
static void clearOutEvents(Timesync_slave* handle);


void timesync_slave_init(Timesync_slave* handle)
{
		sc_integer i;
	
		for (i = 0; i < TIMESYNC_SLAVE_MAX_ORTHOGONAL_STATES; ++i)
		{
			handle->stateConfVector[i] = Timesync_slave_last_state;
		}
		
		
		handle->stateConfVectorPosition = 0;
	
		clearInEvents(handle);
		clearOutEvents(handle);
	
}

void timesync_slave_enter(Timesync_slave* handle)
{
	/* Default enter sequence for statechart timesync_slave */
	enseq_sync_default(handle);
}

void timesync_slave_exit(Timesync_slave* handle)
{
	/* Default exit sequence for statechart timesync_slave */
	exseq_sync(handle);
}

sc_boolean timesync_slave_isActive(const Timesync_slave* handle)
{
	sc_boolean result = bool_false;
	int i;
	
	for(i = 0; i < TIMESYNC_SLAVE_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Timesync_slave_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean timesync_slave_isFinal(const Timesync_slave* handle)
{
   return bool_false;
}

static void clearInEvents(Timesync_slave* handle)
{
}

static void clearOutEvents(Timesync_slave* handle)
{
}

void timesync_slave_runCycle(Timesync_slave* handle)
{
	
	clearOutEvents(handle);
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < TIMESYNC_SLAVE_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case Timesync_slave_sync_a:
		{
			react_sync_a(handle);
			break;
		}
		default:
			break;
		}
	}
	
	clearInEvents(handle);
}


sc_boolean timesync_slave_isStateActive(const Timesync_slave* handle, Timesync_slaveStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Timesync_slave_sync_a :
			result = (sc_boolean) (handle->stateConfVector[SCVI_TIMESYNC_SLAVE_SYNC_A] == Timesync_slave_sync_a
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}


/* implementations of all internal functions */

/* 'default' enter sequence for state a */
static void enseq_sync_a_default(Timesync_slave* handle)
{
	/* 'default' enter sequence for state a */
	handle->stateConfVector[0] = Timesync_slave_sync_a;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region sync */
static void enseq_sync_default(Timesync_slave* handle)
{
	/* 'default' enter sequence for region sync */
	react_sync__entry_Default(handle);
}

/* Default exit sequence for state a */
static void exseq_sync_a(Timesync_slave* handle)
{
	/* Default exit sequence for state a */
	handle->stateConfVector[0] = Timesync_slave_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for region sync */
static void exseq_sync(Timesync_slave* handle)
{
	/* Default exit sequence for region sync */
	/* Handle exit of all possible states (of timesync_slave.sync) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Timesync_slave_sync_a :
		{
			exseq_sync_a(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state a. */
static void react_sync_a(Timesync_slave* handle)
{
}

/* Default react sequence for initial entry  */
static void react_sync__entry_Default(Timesync_slave* handle)
{
	/* Default react sequence for initial entry  */
	enseq_sync_a_default(handle);
}


