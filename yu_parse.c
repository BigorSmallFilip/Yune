#include "yu_parse.h"



Yu_CodeBlock* Yu_ParseSourceCode(Yu_State* state, const char* sourcecode)
{
	Yu_ParserState parser = { 0 };
	parser.main_state = state;
	parser.tabsize = state->tabsize;
	parser.filename = NULL;
	return Yu_FALSE;
}
