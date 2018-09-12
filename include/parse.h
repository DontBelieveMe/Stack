#ifndef _PARSE_
#define _PARSE_

#include "stack.h"

#define COMMAND_COUNT 14
#define MAX_MACROS 100

typedef struct _Command {
	error_code (*fptr)();
	const char  *name;
} Command;

typedef struct _Macro {
	char *str_value;
	char *name;
} Macro;

extern Command _commands[COMMAND_COUNT];
extern Macro* _macros[MAX_MACROS];

typedef struct _Line {
    char   	       *string;
    struct _Line   *next;
	Command        *command;
	int           	arg;
	int           	number;
} Line;

typedef struct _Module {
	int   lines;
	Line *head;
	int   macros;
} Module;

error_code module_load    (Module **module, const char *path);
error_code module_close   (Module  *mod);
error_code line_execute   (Line *line, Stack *s);
error_code line_execute_ln(Line **line, Stack *s, int line_number, Module *module);
error_code mod_execute    (Stack *s, Module *module);
error_code line_at_ln     (Line **line, Module *module, int line_number);

#endif