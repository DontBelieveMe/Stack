#include "parse.h"

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common/string.h"

Command 
_commands[COMMAND_COUNT] = {
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

Macro* 
_macros[MAX_MACROS] = {0};

int 
_eval_line(Line *line_out, char *line_in, int *nmacros) {
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
	for(i = 0; i < COMMAND_COUNT; ++i) {
		if(strstr(line_in, _commands[i].name) != NULL) {
		 	line_out->command = &_commands[i];
		 	if(strstr(line_in, "push")) {
		 		int arg;
		 		sscanf(line_in, "push %d", &arg);
		 		line_out->arg = arg;
		 	}
			if(strstr(line_in, "set")) {
				Macro *macro = malloc(sizeof(Macro));
				char *name = malloc(100);
				char *value = malloc(10);
				sscanf(line_in, "set %s  %s", name, value);
				macro->name = name;
				macro->str_value = value;
				_macros[*nmacros] = macro;
				*nmacros = *nmacros + 1;
			}
			if(strstr(line_in, "label")) {
				Macro *macro = malloc(sizeof(Macro));
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

/*
	Loads file and begin parsing of contents. Returns 0 on failure.
*/

error_code
module_load(Module **module, const char *path) {
	FILE *fp;
	char line[128];
    
	Module *_file = malloc(sizeof(Module));

	if(!_file)
		return BAD_MEMORY_ALLOC;

	_file->head = NULL;
	_file->macros = 0;
	
	Line *current = NULL;
	fp = fopen(path, "r");

	if(!fp)
	{
		free(_file);
		return BAD_MEMORY_ALLOC;
	}

	int lines = 0;
    while(fgets(line, sizeof(line), fp)){
		char *__line = line;
		__line = str_trimwhitespace(__line);

		if(__line[0] == '\0' || __line[0] == ';' || __line[0] == '}' || __line[0] == '{') {
			continue;
		}
		lines = lines + 1;
	    Line *node = malloc(sizeof(Line));

		if(!node)
		{
			free(_file);
			fclose(fp);
			return BAD_MEMORY_ALLOC;
		}

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

	*module = _file;

	return OK;
}

/*
	Closes and frees all resources associated with @mod.
*/

error_code 
module_close(Module *module) {
	Line *tmp;
	while(module->head != NULL) {
		tmp = module->head;
		module->head = module->head->next;
		free(tmp->string);
		tmp->string = NULL;
		free(tmp);
		tmp = NULL;
	}
	free(module);
	module = NULL;

	return OK;
}

/*
	Execute the correct function depending on string value.
*/

error_code
line_execute(Line *line, Stack *s) {
	if(strcmp(line->string, "\n") != 0 && line->command->fptr != NULL) {
		if(line->arg == -1) {
			line->command->fptr(s);
		} else {
			line->command->fptr(s, line->arg);
		}
	}

	return OK;
}

/*
	Get a line_t object of the file at line @line_number. Returns 0 if line is not found.
*/

error_code
line_at_ln(Line **line, Module *module, int line_number) {
	Line *current = module->head;
	while(current != NULL) {
		if(current->number == line_number) {
			*line = current;
			break;
		}
		current = current->next;
	}

	return OK;
}

/*
	Executes a line of code at line @line_number.
*/

error_code
line_execute_ln(Line **line, Stack *s, int line_number, Module *module) {
	Line *it;
	
	line_at_ln(&it, module, line_number);
	line_execute(it, s);

	*line = it;
	
	return OK;
}

/*
	Parses and executes certain operations at runtime.
*/

error_code
mod_execute(Stack *s, Module *module) {
	int i;
	for(i = 1; i <= module->lines; ++i) {
		Line *line;
		line_at_ln(&line, module, i);
	//	printf("%s\n", line->string);
		const char *name =  line->command->name;
		// It isn't good that these operations are parsed at 'runtime'...
		// TODO: change
		if(strcmp(name, "jump") == 0) {
			int line_n;
			sscanf(line->string, "jump %d", &line_n);
			i = line_n;

			line_execute_line(s, line_n, module);
			continue;
		}

		if(strcmp(name, "ifeq") == 0) {
			int line_n;
			sscanf(line->string, "ifeq %d", &line_n);

			int value = 0;
			error_code status_code;
			if((status_code = stack_gettop(s, &value)) != OK)
				return status_code;
			
		//	printf("%d %d\n", value, line_n);
			if(value != 0) {
				i = line_n;
				line_execute_line(s, line_n, module);
			}
		}

		if(strcmp(name, "settop") == 0) {
			Macro *macro = malloc(sizeof(Macro));
			char *name = malloc(100);
			char *value = malloc(10);
			sscanf(line->string, "settop %s", name);

			int top = 0;
			error_code status_code;
			if((status_code = stack_gettop(s, &top)) != OK)
			{
				free(macro);
				free(name);
				free(value);
				return status_code;
			}

			sprintf(value, "%d", top);
			macro->name = name;
			macro->str_value = value;
			_macros[module->macros] = macro;
			module->macros = module->macros + 1;
		}

		line_execute(line, s);
	}

	return OK;
}