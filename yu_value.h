#ifndef __Yu_VALUE_H__
#define __Yu_VALUE_H__

#include "yu_utility.h"

typedef unsigned char Yu_ValueType;
enum
{
	Yu_VT_BOOL,
	Yu_VT_NUMBER,
	Yu_VT_STRING,
	Yu_VT_VECTOR,
	Yu_VT_LIST,
	Yu_VT_OBJECT,
	Yu_VT_FUNCTION,
	Yu_VT_NULL,
	Yu_NUM_VALUETYPES = Yu_VT_NULL
};

typedef struct
{
	char* str;
	Yu_Size length;
	Yu_Hash hash;
	Yu_Vector format; /* Vector of Yu_ExprNodes for each format expression in the string */
} Yu_FormatString;

/*
** This is completely separate from normal Yu_Vector.
** This is a 2-4 component vector used in the scripting.
** Similar to vec2, vec3, float4 in various languages.
*/
typedef struct
{
	int num_components;
	Yu_Float comp0;
	Yu_Float comp1;
	Yu_Float comp2;
	Yu_Float comp3;
} Yu_ValueVector;

typedef struct
{
	Yu_Vector members;
	Yu_Value* prototype;
} Yu_ValueObject;

typedef struct
{
	char* key;
	Yu_Hash hash;
	Yu_Value value;
} Yu_ValueObjectMember;

typedef struct
{
	Yu_Vector parameters; /* Vector of Yu_ValueFunctionParameters */
	struct Yu_Bytecode* bytecode;
} Yu_ValueFunction;

typedef struct
{
	char* str;
	Yu_Hash hash;
	Yu_Value* defaultvalue;
} Yu_ValueFunctionParameter;

typedef union
{
	Yu_Bool t_bool;
	Yu_Float t_number;
	Yu_FormatString t_string;
	Yu_ValueVector t_vector;
	Yu_Vector t_list;
	Yu_ValueObject t_object;

} Yu_ValueUnion;

typedef struct
{
	Yu_ValueType type;
	Yu_ValueUnion value;
} Yu_Value;

#endif