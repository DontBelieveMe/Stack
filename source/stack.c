#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

int _addp(Stack *s, int x, int y) {
	int result = x + y;
	stack_push(s, result);
	return result;
}

/*
	Creates a new stack. Free with stack_close(). Returns 0 on failure.
*/

error_code
new_stack(Stack **out) {
	Stack *new_stack = malloc(sizeof(Stack));

	if(!new_stack)
		return BAD_MEMORY_ALLOC;

	new_stack->head = NULL;
	new_stack->size = 0;
	
	*out = new_stack;

	return OK;
}

/*
	Frees all resources belonging to the stack and itself.
*/

error_code 
close_stack(Stack *s) {
	Element *tmp;
	while(s->head != NULL) {
		tmp = s->head;
		s->head = s->head->next;
		free(tmp);
		tmp = NULL;
	}

	free(s);
	s = NULL;

	return OK;
}

/*
	Pushes a value onto the stack.
*/

error_code 
stack_push(Stack *s, int value) {
	Element *new_element = malloc(sizeof(Element));

	if(!new_element)
		return BAD_MEMORY_ALLOC;

	new_element->value = value;
	new_element->next = s->head;
	s->head = new_element;
	s->size = s->size + 1;

	return OK;
}

/*
	Pops and returns the value on top of the stack.
*/

error_code
stack_pop(Stack *s, int *popped_value) {

	if(s->size < 1)
		return STACK_UNDERFLOW;

	Element *next_node = s->head->next;
	*popped_value = s->head->value;
	free(s->head);
	s->head = next_node;
	s->size = s->size - 1;

	return OK;
}

/*
	Alias for stack_pop().
*/

error_code 
stack_popnt(Stack *s) {
	return stack_pop(s, 0);
}

/*
	Pops two numbers off the stack, performs addition, and pushes the
	result back onto the stack.
*/

error_code
stack_add(Stack *s) {
	int op;
	int op2;

	if(stack_pop(s, &op) == STACK_UNDERFLOW || stack_pop(s, &op2) == STACK_UNDERFLOW)
		return STACK_UNDERFLOW;

	
	_addp(s, op, op2);

	return OK;
}

/*
	Pops two numbers off the stack, performs subtraction, and pushes the
	result back onto the stack.
*/

error_code
stack_sub(Stack *s) {
	int op;
	int op2;

	if(stack_pop(s, &op) == STACK_UNDERFLOW || stack_pop(s, &op2) == STACK_UNDERFLOW)
		return STACK_UNDERFLOW;

	_addp(s, -op, op2);

	return OK;
}

/*
	Pops two numbers off the stack, performs multiplication, and pushes the
	result back onto the stack.
*/

error_code 
stack_mult(Stack *s) {
	int op;
	int multiplier;

	if(stack_pop(s, &op) == STACK_UNDERFLOW || stack_pop(s, &multiplier) == STACK_UNDERFLOW)
		return STACK_UNDERFLOW;

	int result = op * multiplier;
	return stack_push(s, result);
}

/*
	Pops two numbers off the stack, performs division, and pushes the
	result back onto the stack.
*/

error_code 
stack_div(Stack *s) {
	int op;
	int op2;

	if(stack_pop(s, &op) == STACK_UNDERFLOW || stack_pop(s, &op2) == STACK_UNDERFLOW)
		return STACK_UNDERFLOW;
	
	int result = op / op2;
	return stack_push(s, result);
}

/*
	Duplicates the item on top of the stack.
*/

error_code
stack_dup(Stack *s) {
	error_code status_code;

	int value = 0;
	if((status_code = stack_pop(s, &value) != OK))
		return status_code;
	
	if((status_code = stack_push(s, value) != OK))
		return status_code;
	
	if((status_code = stack_push(s, value) != OK))
		return status_code;
	
	return OK;
}

/*
	Prints each item on the stack.
*/

error_code
stack_print(Stack *s) {
	error_code status_code;

	if((status_code = stack_dup(s)) != OK)
		return status_code;
	
	int value = 0;

	if((status_code = stack_pop(s, &value) != OK))
		return status_code;
	
	return OK;
}

/*
	Returns the top item on the stack without popping it.
*/

error_code 
stack_gettop(Stack *s, int *top_stack_value) {
	error_code status_code;

	if((status_code = stack_dup(s)) != OK)
		return status_code;
	
	int value = 0;
	if((status_code = stack_pop(s, &value)) != OK)
		return status_code;
	
	return OK;
}

/*
	Swap two values on top of the stack.
*/

error_code
stack_swap(Stack *s) {
	error_code status_code;

	int temp = 0;
	if((status_code = stack_pop(s, &temp)) != OK)
		return status_code;
	
	int top = 0;
	if((status_code = stack_pop(s, &top)) != OK)
		return status_code;
	
	if((status_code = stack_push(s, temp)) != OK)
		return status_code;

	if((status_code = stack_push(s, top)) != OK)
		return status_code;

	return OK;
}