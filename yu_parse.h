#ifndef __Yu_PARSE_H__
#define __Yu_PARSE_H__

#include "yu_utility.h"
#include "yu_state.h"
#include "yu_code.h"

typedef struct
{
	Yu_State* main_state;
	const char* filename;
	const char* sourcecode;
	int tabsize;            /* Number of spaces equivalent to a tab. For indentation */
	int charpos;            /* Lexer character index */
	int linenum;            /* The current line being read by the lexer */
	int errorcount;
	Yu_Vector tokens;       /* Vector of Yu_Tokens. This is set by the Yu_TokenizeSourceCode function */
	int curtoken;           /* Parser token index */
} Yu_ParserState;

Yu_Bool Yu_TokenizeSourceCode(Yu_ParserState* state);

Yu_CodeBlock* Yu_ParseSourceCode(Yu_State* state, const char* sourcecode);

#endif
