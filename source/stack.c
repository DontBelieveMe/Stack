#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

int _addp(stack *s, int x, int y) {
	int result = x + y;
	stack_push(s, result);
	return result;
}

stack*
new_stack() {
	stack *_stack = malloc(sizeof(stack));
	_stack->head = NULL;
	_stack->size = 0;
	return _stack;
}

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

void 
stack_push(stack *s, int value) {
	element_t *new_element = malloc(sizeof(element_t));
	new_element->value = value;
	new_element->next = s->head;
	s->head = new_element;
	s->size = s->size + 1;
}

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

void 
stack_popnt(stack *s) {
	stack_pop(s);
}


void 
stack_add(stack *s) {
	int op1 = stack_pop(s);
	int op2 = stack_pop(s);
	_addp(s, op1, op2);
}

void 
stack_mult(stack *s) {
	int multip = stack_pop(s);
	int op     = stack_pop(s);
	int result = op * multip;
	stack_push(s, result);
}

void 
stack_sub(stack *s) {
	int op1 = stack_pop(s);
	int op2 = stack_pop(s);
	_addp(s, -op1, op2);
}

void 
stack_dup(stack *s) {
	int value = stack_pop(s);
	stack_push(s, value);
	stack_push(s, value);
}

void
stack_print(stack *s) {
	stack_dup(s);
	printf("%i\n", stack_pop(s));
}

int 
stack_gettop(stack *s) {
	stack_dup(s);
	int value = stack_pop(s);
	return value;
}

void 
stack_swap(stack *s) {
	int tmp = stack_pop(s);
	int top = stack_pop(s);
	stack_push(s, tmp);
	stack_push(s, top);
}

void 
stack_div(stack *s) {
	int op2 = stack_pop(s);
	int op1 = stack_pop(s);
	int result = op1 / op2;
	stack_push(s, result);
}