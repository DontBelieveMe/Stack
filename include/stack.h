#ifndef _STACK_
#define _STACK_

typedef struct _Element {
	int              value;
	struct _Element *next;
} Element;

typedef struct _Stack {
	int		   size;
	Element   *head;
} Stack;

typedef enum
{
	OK               = 0,
	BAD_MEMORY_ALLOC = 1,
	STACK_UNDERFLOW  = 2


} error_code;

error_code 	   new_stack   (Stack **out);
error_code     close_stack (Stack *s);

error_code 	   stack_pop   (Stack *s, int *popped_value);
error_code	   stack_gettop(Stack *s, int *top_stack_value);

error_code 	   stack_push  (Stack *s, int value);
error_code     stack_popnt (Stack *s);
error_code 	   stack_add   (Stack *s);
error_code	   stack_sub   (Stack *s);
error_code     stack_mult  (Stack *s);
error_code     stack_div   (Stack *s);
error_code 	   stack_dup   (Stack *s);
error_code 	   stack_print (Stack *s);
error_code     stack_swap  (Stack *s);

#endif // _STACK_