#include <stdio.h>
#include "stack.h"
#include "parse.h"

#include "common/list.h"

int 
main(int argc, char ** argv) {
    stack *s = new_stack();
	module *f = load_file(argv[1]);
	list *vector = NEW_LIST(const char*);
	LIST_ADD_ITEM(vector, const char*, "Hello");
	printf("%i %i %s\n", vector->size, vector->capacity, LIST_GET_AT(vector, const char*, 0));
	mod_execute(s, f);
	close_file(f);
	close_stack(s);
	return 0;
}