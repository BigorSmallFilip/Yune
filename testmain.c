#include <stdio.h>
#include "yune.h"
#include "yu_code.h"

int main(int argc, char** argv)
{
	printf("Yune programming language test\n");

	Yu_State* state = Yu_CreateState();
	if (!state) return 1;
	
	Yu_ExprNode node = { Yu_ET_VECTOR, .u_vector = { 100, NULL, NULL, NULL, NULL } };
	Yu_PrintExprNode(&node);

	return 0;
}
