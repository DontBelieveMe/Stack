#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

int _addp(stack *s, int x, int y) {
	int result = x + y;
	stack_push(s, result);
	return result;
}

/*
	Creates a new stack. Free with stack_close(). Returns 0 on failure.
*/

stack*
new_stack() {
	stack *_stack = malloc(sizeof(stack));

	if(!_stack)
		return 0;

	_stack->head = NULL;
	_stack->size = 0;
	return _stack;
}

/*
	Frees all resources belonging to the stack and itself.
*/

void 
close_stack(stack *s) {
	element_t *tmp;
	while(s->head != NULL) {
		tmp = s->head;
		s->head = s->head->next;
		free(tmp);
		tmp = NULL;
	}

	free(s);
	s = NULL;
}

/*
	Pushes a value onto the stack.
*/

void 
stack_push(stack *s, int value) {
	element_t *new_element = malloc(sizeof(element_t));

	if(!new_element)
		return;

	new_element->value = value;
	new_element->next = s->head;
	s->head = new_element;
	s->size = s->size + 1;
}

/*
	Pops and returns the value on top of the stack.
*/

int 
stack_pop(stack *s) {
	int value = -1;
	element_t *next_node = s->head->next;
	value = s->head->value;
	free(s->head);
	s->head = next_node;
	s->size = s->size - 1;
	return value;
}

/*
	Alias for stack_pop().
*/

void 
stack_popnt(stack *s) {
	stack_pop(s);
}

/*
	Pops two numbers off the stack, performs addition, and pushes the
	result back onto the stack.
*/

void 
stack_add(stack *s) {
	int op1 = stack_pop(s);
	int op2 = stack_pop(s);
	_addp(s, op1, op2);
}

/*
	Pops two numbers off the stack, performs subtraction, and pushes the
	result back onto the stack.
*/

void 
stack_sub(stack *s) {
	int op1 = stack_pop(s);
	int op2 = stack_pop(s);
	_addp(s, -op1, op2);
}

/*
	Pops two numbers off the stack, performs multiplication, and pushes the
	result back onto the stack.
*/

void 
stack_mult(stack *s) {
	int multip = stack_pop(s);
	int op     = stack_pop(s);
	int result = op * multip;
	stack_push(s, result);
}

/*
	Pops two numbers off the stack, performs division, and pushes the
	result back onto the stack.
*/

void 
stack_div(stack *s) {
	int op2 = stack_pop(s);
	int op1 = stack_pop(s);
	int result = op1 / op2;
	stack_push(s, result);
}

/*
	Duplicates the item on top of the stack.
*/

void 
stack_dup(stack *s) {
	int value = stack_pop(s);
	stack_push(s, value);
	stack_push(s, value);
}

/*
	Prints each item on the stack.
*/

void
stack_print(stack *s) {
	stack_dup(s);
	printf("%i\n", stack_pop(s));
}

/*
	Returns the top item on the stack without popping it.
*/

int 
stack_gettop(stack *s) {
	stack_dup(s);
	int value = stack_pop(s);
	return value;
}

/*
	Swap two values on top of the stack.
*/

void 
stack_swap(stack *s) {
	int tmp = stack_pop(s);
	int top = stack_pop(s);
	stack_push(s, tmp);
	stack_push(s, top);
}