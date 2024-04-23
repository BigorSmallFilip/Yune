#include "yu_state.h"

Yu_State* Yu_CreateState()
{
	Yu_State* state = Yu_AllocType(Yu_State);
	if (!state) return NULL;
	state->max_value_memory = 1024 * 4;
	return state;
}
