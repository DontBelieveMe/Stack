#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "stack.h"
#include "parse.h"

int 
main(int argc, char ** argv) {
    stack_st *s = new_stack();
	module *f = load_file(argv[1]);
	
	mod_execute(s, f);
	close_file(f);
	close_stack(s);
	return 0;
}