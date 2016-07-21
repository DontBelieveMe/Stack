#ifndef _STACK_
#define _STACK_

typedef struct _element {
	int value;
	struct _element *next;
} element_t;

typedef struct stack {
	int			    size;
	element_t *head;
} stack_st;

stack_st *new_stack();
void     close_stack(stack_st *s);

int 	 stack_pop(stack_st *s);
int	 	 stack_gettop(stack_st *s);

void 	 stack_push(stack_st *s, int value);
void     stack_popnt(stack_st *s);
void 	 stack_add(stack_st *s);
void	 stack_sub(stack_st *s);
void     stack_mult(stack_st *s);
void     stack_div(stack_st *s);
void 	 stack_dup(stack_st *s);
void 	 stack_print(stack_st *s);
void     stack_swap(stack_st *s);

#endif // _STACK_