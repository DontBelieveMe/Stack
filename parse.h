#ifndef _PARSE_
#define _PARSE_

#include "stack.h"

#define CMD_COUNT 12
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

typedef struct _file {
	int lines;
	line_t *head;
	int macros;
} file_t;

file_t *load_file(const char *path);
void    close_file(file_t *mod);
void	line_execute(stack_t *s, line_t *line);
line_t *line_execute_ln(stack_t *s, int ln, file_t *mod);
void    mod_execute(stack_t *s, file_t *mod);
line_t *line_at_ln(file_t *mod, int ln);

#endif