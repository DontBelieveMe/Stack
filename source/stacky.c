#include <stdio.h>
#include "stack.h"
#include "parse.h"

#include "common/list.h"

int 
main(int argc, char ** argv) {

	Stack *s;
	Module *m;
    new_stack(&s);
	module_load(&m, argv[1]);
	
	mod_execute(m, s);
	module_close(m);
	close_stack(s);
	return 0;
}