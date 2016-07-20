#ifndef _STACK_
#define _STACK_

typedef struct _element {
	int value;
	struct _element *next;
} element_t;

typedef struct stack {
	int			    size;
	element_t *head;
} stack_t;

stack_t *new_stack();
void     close_stack(stack_t *s);

int 	 stack_pop(stack_t *s);
int	 	 stack_gettop(stack_t *s);

void 	 stack_push(stack_t *s, int value);
void     stack_popnt(stack_t *s);
void 	 stack_add(stack_t *s);
void	 stack_sub(stack_t *s);
void     stack_mult(stack_t *s);
void     stack_div(stack_t *s);
void 	 stack_dup(stack_t *s);
void 	 stack_print(stack_t *s);
void     stack_swap(stack_t *s);

#endif // _STACK_