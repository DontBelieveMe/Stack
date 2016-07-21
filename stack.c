#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

int _addp(stack_st *s, int x, int y) {
	int result = x + y;
	stack_push(s, result);
	return result;
}

stack_st*
new_stack() {
	stack_st *_stack = malloc(sizeof(stack_st));
	_stack->head = NULL;
	_stack->size = 0;
	return _stack;
}

void 
close_stack(stack_st *s) {
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
stack_push(stack_st *s, int value) {
	element_t *new_element = malloc(sizeof(element_t));
	new_element->value = value;
	new_element->next = s->head;
	s->head = new_element;
	s->size = s->size + 1;
}

int 
stack_pop(stack_st *s) {
	int value = -1;
	element_t *next_node = s->head->next;
	value = s->head->value;
	free(s->head);
	s->head = next_node;
	s->size = s->size - 1;
	return value;
}

void 
stack_popnt(stack_st *s) {
	stack_pop(s);
}


void 
stack_add(stack_st *s) {
	int op1 = stack_pop(s);
	int op2 = stack_pop(s);
	_addp(s, op1, op2);
}

void 
stack_mult(stack_st *s) {
	int multip = stack_pop(s);
	int op     = stack_pop(s);
	int result = op * multip;
	stack_push(s, result);
}

void 
stack_sub(stack_st *s) {
	int op1 = stack_pop(s);
	int op2 = stack_pop(s);
	_addp(s, -op1, op2);
}

void 
stack_dup(stack_st *s) {
	int value = stack_pop(s);
	stack_push(s, value);
	stack_push(s, value);
}

void
stack_print(stack_st *s) {
	stack_dup(s);
	printf("%i\n", stack_pop(s));
}

int 
stack_gettop(stack_st *s) {
	stack_dup(s);
	int value = stack_pop(s);
	return value;
}

void 
stack_swap(stack_st *s) {
	int tmp = stack_pop(s);
	int top = stack_pop(s);
	stack_push(s, tmp);
	stack_push(s, top);
}

void 
stack_div(stack_st *s) {
	int op2 = stack_pop(s);
	int op1 = stack_pop(s);
	int result = op1 / op2;
	stack_push(s, result);
}