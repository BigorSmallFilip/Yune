#include <stdio.h>
#include "yune.h"
#include "yu_code.h"
#include "yu_parse.h"

int main(int argc, char** argv)
{
	printf("Yune programming language test but here??\n");

	Yu_State* state = Yu_CreateState();
	if (!state) return 1;
	
	Yu_CodeBlock* block = Yu_ParseSourceCode(state, "if 5 < 10 print('Oh no')");

	return 0;
}
