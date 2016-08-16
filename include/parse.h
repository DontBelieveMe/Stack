#ifndef _PARSE_
#define _PARSE_

#include "stack.h"

#define CMD_COUNT 14
#define MAX_MACROS 100

typedef struct _cmd {
	void (*fptr)();
	const char *name;
} cmd_t;

typedef struct _macro {
	char *str_value;
	char *name;
} macro_t;

extern cmd_t _cmds[CMD_COUNT];
extern macro_t* _macros[MAX_MACROS];

typedef struct _line {
    char   	     	*string;
    struct _line 	*next;
	cmd_t           *cmd;
	int           	arg;
	int           	number;
} line_t;

typedef struct _module {
	int lines;
	line_t *head;
	int macros;
} module;

module *load_file(const char *path);
void    close_file(module *mod);
void	line_execute(stack *s, line_t *line);
line_t *line_execute_ln(stack *s, int ln, module *mod);
void    mod_execute(stack *s, module *mod);
line_t *line_at_ln(module *mod, int ln);

#endif