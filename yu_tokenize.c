#include "yu_parse.h"

#include <ctype.h>



typedef enum
{
	CT_NULL,		/* Default type or any char not recognised */
	CT_ALPHA,		/* Letter or underscore */
	CT_NUMBER,
	CT_POINT,
	CT_OPERATOR,
	CT_SEPARATOR,
	CT_SPACE,		/* Space or tab */
	CT_QUOTE,		/* Quotation marks for strings */
	CT_COMMENT,		/* Comments start with # and end with an endline */
	CT_ENDLINE,
} chartype;

#define is_alpha(c) (isalpha(c) || c == '_')
#define is_operator_char(c) (strchr("+-/*=<>!&|", c))
#define is_separator_char(c) (strchr("()[]{},", c))
#define is_quote_char(c) (c == '\"' || c == '\'')
#define is_invalid(c) (c < 0)

static chartype check_chartype(const char c)
{
	Yu_Assert(c != 0);
	if (c < 0)                 return CT_NULL;
	if (is_alpha(c))           return CT_ALPHA;
	if (isdigit(c))            return CT_NUMBER;
	if (c == '.')              return CT_POINT;
	if (is_operator_char(c))   return CT_OPERATOR;
	if (is_separator_char(c))  return CT_SEPARATOR;
	if (isblank(c))            return CT_SPACE;
	if (c == '\n' || c == ';') return CT_ENDLINE; /* Semicolon acts the same as endline */
	if (is_quote_char(c))      return CT_QUOTE;
	if (c == '#')              return CT_COMMENT;
	return CT_NULL;
}

static Yu_Token* create_token()
{
	Yu_Token* token = Yu_Malloc(sizeof(Yu_Token)); /* Malloc instead of calloc since this will setup everything manually so no need to 0 out token */
	if (!token) return NULL;
	token->type = Yu_TT_NULL;
	token->keywordid = Yu_KW_NULL;
	token->operatorid = Yu_OP_NULL;
	token->separatorid = Yu_SP_NULL;
	token->string = NULL;
	token->lastonline = Yu_FALSE;
	token->linenum = -1;
	token->indentlevel = -1;
	return token;
}



Yu_Bool Yu_TokenizeSourceCode(Yu_ParserState* parser)
{
	for (int i = 128; i < 256; i++)
	{
		printf("%i > %c > %i\n", i, (char)i, check_chartype((char)i));
	}
	return Yu_FALSE;

	parser->charpos = 0;
	parser->linenum = 1;
	if (!Yu_InitVector(&parser->tokens)) return Yu_FALSE;
	short line_indentlevel = 0;
	Yu_Bool reading_indent = Yu_TRUE;

	while (1)
	{
		if (parser->charpos >= parser->max_sourcecode_length)
		{
			//syntax_error("Sourcecode exceeds max length of %i characters", parser->max_sourcecode_length);
			break;
		}

		char c = parser->sourcecode[parser->charpos];
		if (c == '\0') break;
		if (c < 0)
		{
			//syntax_error("Non-ASCII character %X", c);
			parser->charpos++;
			continue;
		}

		//Yu_Token* token = NULL;
		//switch (check_chartype(c))
		//{
		//case CT_ALPHA:     token = read_alpha_token(parser, sourcecode); break;
		//case CT_NUMBER:	   token = read_number_token(parser, sourcecode); break;
		//case CT_POINT:
		//case CT_OPERATOR:  token = read_operator_token(parser, sourcecode); break;
		//case CT_SEPARATOR: token = read_separator_token(parser, c); break;
		//case CT_QUOTE:     token = read_string_token(parser, sourcecode); break;
		//case CT_COMMENT:   read_comment(parser, sourcecode); continue;
		//case CT_ENDLINE:
		//{
		//	/* If an endline char is found then the previous token gets the lastonline flag set */
		//	if (parser->tokens.count > 0)
		//	{
		//		Yu_Token* lasttoken = (Yu_Token*)parser->tokens.buffer[parser->tokens.count - 1];
		//		lasttoken->lastonline = Yu_TRUE;
		//	}
		//	/* Only real endlines reset the indentation, not semicolons which count as endlines */
		//	if (c == '\n')
		//	{
		//		parser->linenum++;
		//		line_indentlevel = 0;
		//		reading_indent = Yu_TRUE;
		//	}
		//	parser->charpos++;
		//	break;
		//}
		//case CT_SPACE:
		//	if (reading_indent)
		//	{
		//		if (c == ' ') line_indentlevel++;
		//		else if (c == '\t') line_indentlevel += parser->tabsize;
		//	}
		//	parser->charpos++;
		//	continue;

		//default:
		//	syntax_error("Invalid character '%c'", c);
		//	parser->charpos++;
		//	break;
		//}

		//if (parser->charpos < 0) goto fail;

		//if (token)
		//{
		//	token->linenum = parser->linenum;
		//	if (reading_indent)
		//	{
		//		token->indentlevel = line_indentlevel;
		//		reading_indent = Yu_FALSE;
		//	}
		//	Yu_PushBackVector(&parser->tokens, token);
		//}
	}

	/* Last token in file gets the lastonline flag set */
	Yu_Token* lasttoken = Yu_VectorBack(parser->tokens, Yu_Token*);
	if (lasttoken) lasttoken->lastonline = Yu_TRUE;

	return Yu_TRUE;

fail:
	for (int i = 0; i < parser->tokens.count; i++)
	{
		Yu_FreeToken(parser->tokens.buffer[i]);
	}
	Yu_Free(parser->tokens.buffer);
	return Yu_FALSE;
}



void Yu_PrintSourceCodeTokens(Yu_ParserState* parser)
{
	if (!parser) return;
	if (!parser->tokens.buffer || parser->tokens.count <= 0) return;

	printf(" === Tokens ===\n");
	for (int i = 0; i < (int)parser->tokens.count; i++)
	{
		Yu_Token* token = parser->tokens.buffer[i];
		for (int intent = 0; intent < 1 + token->indentlevel; intent++)
			putchar(' ');
		Yu_PrintToken(token);
		putchar(token->lastonline ? '\n' : ' ');
	}
	putchar('\n');
}
