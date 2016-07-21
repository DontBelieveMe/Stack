#ifndef _STACK_
#define _STACK_

typedef struct _element {
	int value;
	struct _element *next;
} element_t;

typedef struct _stack {
	int			    size;
	element_t *head;
} stack;

stack 	*new_stack();
void     close_stack(stack *s);

int 	 stack_pop(stack *s);
int	 	 stack_gettop(stack *s);

void 	 stack_push(stack *s, int value);
void     stack_popnt(stack *s);
void 	 stack_add(stack *s);
void	 stack_sub(stack *s);
void     stack_mult(stack *s);
void     stack_div(stack *s);
void 	 stack_dup(stack *s);
void 	 stack_print(stack *s);
void     stack_swap(stack *s);

#endif // _STACK_