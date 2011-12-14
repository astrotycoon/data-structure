#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

 
void err_exit(char *err_str);
void *make(int n);
void print(void *data);
int main(int argc, char *argv[])
{
	p_stack_t stack;
	stack = stack_create();
	if (NULL == stack)
	{
		err_exit("create error");
	}
	printf("----------------->%s<----------------\n", stack_empty(stack) ? "empty" : "full");
	int i = 0;
	for (; i < 10; i++)
	{
		if (!stack_push(stack, make(i)))
		{
			err_exit("push error");
		}
	}
	printf("----------------->%s<----------------\n", stack_empty(stack) ? "empty" : "full");
	putchar('\n');

	stack_print(stack, print);
	printf("\nThe first data is %d\n", *(int *)get_top(stack));
	putchar('\n');

	if (!stack_push(stack, make(10)))
	{
		err_exit("push error");
	}
	stack_print(stack, print);
	printf("\nThe first data is %d\n", *(int *)get_top(stack));
	putchar('\n');

	if (!stack_pop(stack))
	{
		err_exit("pop error");
	}
	stack_print(stack, print);
	printf("\nThe first data is %d\n", *(int *)get_top(stack));
	putchar('\n');

	stack_destroy(stack);

	return 0;

}

void err_exit(char *err_str)
{
	perror(err_str);
	exit(EXIT_FAILURE);
}

void *make(int n)
{
	int *p = (int *)malloc(sizeof(int));
	if (NULL == p)
	{
		err_exit("malloc error");
	}

	*p = n;

	return p;
}

void print(void *data)
{
	printf("%4d", *(int *)data);
}
