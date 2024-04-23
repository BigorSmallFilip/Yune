#include <stdio.h>
#include "yune.h"

int main(int argc, char** argv)
{
	printf("Yune programming language test\n");

	Yu_State* state = Yu_CreateState();
	if (!state) return 1;


	return 0;
}
