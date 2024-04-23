#ifndef __Yu_STATE_H__
#define __Yu_STATE_H__

#include "yu_utility.h"

typedef struct
{
	size_t max_value_memory; /* The maximum amount of memory allowed for storing values */
} Yu_State;

Yu_State* Yu_CreateState();

#endif
