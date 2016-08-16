#include "parse.h"

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common/string.h"

cmd_t 
_cmds[CMD_COUNT] = {
	{&stack_push,  "push" },
	{&stack_popnt, "pop"  },
	{&stack_add,   "add"  },
	{&stack_sub,   "sub"  },
	{&stack_mult,  "mult" },
	{&stack_dup,   "dup"  },
	{&stack_print, "print"},
	{&stack_swap,  "swap" },
	{&stack_div,   "div"  },
	{NULL,         "jump" },		/* These four are parsed at runtime, therefore have no */
	{NULL,         "ifeq" },
	{NULL,         "set"  },			/* cmd pointers. They are here for the name lookup. */ 
	{NULL,		   "settop"},
	{NULL,         "label"}
};

macro_t* 
_macros[MAX_MACROS] = {0};

int 
_eval_line(line_t *line_out, char *line_in, int *nmacros) {
	line_out->arg = -1;
	
	if(*nmacros > 0) {
		int i;
		for(i = 0; i < *nmacros; ++i) {
			char *name = _macros[i]->name;
			char *value = _macros[i]->str_value;
			printf("%s %s\n", name, value);
			str_replace(line_in, name, value);
		}
	}
	
	int error;
	int i;
	for(i = 0; i < CMD_COUNT; ++i) {
		if(strstr(line_in, _cmds[i].name) != NULL) {
		 	line_out->cmd = &_cmds[i];
		 	if(strstr(line_in, "push")) {
		 		int arg;
		 		sscanf(line_in, "push %d", &arg);
		 		line_out->arg = arg;
		 	}
			if(strstr(line_in, "set")) {
				macro_t *macro = malloc(sizeof(macro_t));
				char *name = malloc(100);
				char *value = malloc(10);
				sscanf(line_in, "set %s  %s", name, value);
				macro->name = name;
				macro->str_value = value;
				_macros[*nmacros] = macro;
				*nmacros = *nmacros + 1;
			}
			if(strstr(line_in, "label")) {
				macro_t *macro = malloc(sizeof(macro_t));
				char *name = malloc(100);
				char *value = malloc(10);
				sscanf(line_in, "label %s", name);
				macro->name = name;
				sprintf(value, "%d", line_out->number);
				printf("%s\n", value);
				macro->str_value = value;
				_macros[*nmacros] = macro;
				*nmacros = *nmacros + 1;
			}
		} else {
			error = 0;
		}
	} 
	if(error == 1) {
		printf("Syntax error [%i]: %sNot a command", line_out->number, line_out->string);
	}
	return error;
}

module*
load_file(const char *path) {
	FILE *fp;
	char line[128];
    
	module *_file = malloc(sizeof(module));
	_file->head = NULL;
	_file->macros = 0;
	
	line_t *current = NULL;
	fp = fopen(path, "r");

	int lines = 0;
    while(fgets(line, sizeof(line), fp)){
		char *__line = line;
		__line = str_trimwhitespace(__line);

		if(__line[0] == '\0' || __line[0] == ';' || __line[0] == '}' || __line[0] == '{') {
			continue;
		}
		lines = lines + 1;
	    line_t *node = malloc(sizeof(line_t));
        node->string = str_dup(line);
		node->number = lines;

		if(_eval_line(node, __line, &(_file->macros)) == 1) {
			printf("[Error notification!]");
			break;
		}

        node->next = NULL;

        if(_file->head == NULL){
            current = _file->head = node;
        } else {
            current = current->next = node;
        }
    }

	_file->lines = lines;

    fclose(fp);
	return _file;
}

void 
close_file(module *mod) {
	line_t *tmp;
	while(mod->head != NULL) {
		tmp = mod->head;
		mod->head = mod->head->next;
		free(tmp->string);
		tmp->string = NULL;
		free(tmp);
		tmp = NULL;
	}
	free(mod);
	mod = NULL;
}

void
line_execute(stack *s, line_t *line) {
	if(strcmp(line->string, "\n") != 0 && line->cmd->fptr != NULL) {
		if(line->arg == -1) {
			line->cmd->fptr(s);
		} else {
			line->cmd->fptr(s, line->arg);
		}
	}
}

line_t*
line_at_ln(module *mod, int ln) {
	line_t *it = mod->head;
	while(it != NULL) {
		if(it->number == ln) {
			return it;
			break;
		}
		it = it->next;
	}
	return NULL;
}

line_t* 
line_execute_ln(stack *s, int ln, module *mod) {
	line_t *it = line_at_ln(mod, ln);
	line_execute(s, it);
	return it;
}

void
mod_execute(stack *s, module *mod) {
	int i;
	for(i = 1; i <= mod->lines; ++i) {
		line_t *ln = line_at_ln(mod, i);
	//	printf("%s\n", ln->string);
		const char *name =  ln->cmd->name;
		// It isn't good that these operations are parsed at 'runtime'...
		// TODO: change
		if(strcmp(name, "jump") == 0) {
			int line_n;
			sscanf(ln->string, "jump %d", &line_n);
			i = line_n;
			line_execute_ln(s, line_n, mod);
			continue;
		}

		if(strcmp(name, "ifeq") == 0) {
			int line_n;
			sscanf(ln->string, "ifeq %d", &line_n);
			int value = stack_gettop(s);
		//	printf("%d %d\n", value, line_n);
			if(value != 0) {
				i = line_n;
				line_execute_ln(s, line_n, mod);
			}
		}

		if(strcmp(name, "settop") == 0) {
			macro_t *macro = malloc(sizeof(macro_t));
			char *name = malloc(100);
			char *value = malloc(10);
			sscanf(ln->string, "settop %s", name);
			int top = stack_gettop(s);
			sprintf(value, "%d", top);
			macro->name = name;
			macro->str_value = value;
			_macros[mod->macros] = macro;
			mod->macros = mod->macros + 1;
		}

		line_execute(s, ln);
	}
}