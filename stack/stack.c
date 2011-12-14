/**********************************************************
*	文件名: stack.h
*
*	文件描述: 链栈的函数实现
*
*	创建人: Astrol 2011-12-13 20:35:39
*
*	版本号: 1.0
*
*	修改记录:
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "stack.h"

static p_slnode_t node_create(void *data)
{
	p_slnode_t new_node = NULL;

	new_node = (p_slnode_t)malloc(sizeof(slnode_t));
	if (NULL == new_node)
	{
		errno = ENOMEM;
		return NULL;
	}

	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

p_stack_t stack_create(void)
{
	p_stack_t stack_ret = NULL;

	stack_ret = (p_stack_t)malloc(sizeof(stack_t));
	if (NULL == stack_ret)
	{
		errno = ENOMEM;
		return NULL;
	}

	stack_ret->top = node_create(NULL);
	if (NULL == stack_ret->top)
	{
		free(stack_ret);	/* easy to forget */
		errno = ENOMEM;
		return NULL;
	}
	
	stack_ret->size = 0;
	stack_ret->base = stack_ret->top;

	return stack_ret;
}

bool stack_destroy(p_stack_t stack)
{
	if (NULL == stack || NULL == stack->top)
	{
		errno = EINVAL;
		return false;
	}

	size_t count = stack->size;

	for (; count > 0; count--)
	{
		stack_pop(stack);
	}
	
	return true;
}
	
bool stack_empty(const p_stack_t stack)
{
	if (NULL == stack || NULL == stack->top)
	{
		errno = EINVAL;
		return false;
	}

	return (stack->size == 0);
}

bool stack_push(p_stack_t stack, void *data)
{
	if (NULL == stack || NULL == stack->top)
	{
		errno = EINVAL;
		return false;
	}

	if (0 == stack->size)
	{
		stack->top->data = data;
		stack->size++;
		return true;
	}

	p_slnode_t new_node = NULL;
	new_node = node_create(data);
	if (NULL == new_node)
	{
		errno = ENOMEM;
		return false;
	}
	
	new_node->next = stack->top;
	stack->top = new_node;
	stack->size++;

	return true;
}

bool stack_pop(p_stack_t stack)
{
	if (NULL == stack || 0 == stack->size)
	{
		errno = EINVAL;
		return false;
	}

	p_slnode_t top = stack->top;
	stack->top = top->next;
	free(top->data);
	free(top);
	stack->size--;

	return true;
}

void *get_top(const p_stack_t stack)
{
	if (NULL == stack || 0 == stack->size)
	{
		errno = EINVAL;
		return NULL;
	}

	return stack->top->data;
}

void stack_print(const p_stack_t stack, void (*fp)(void *data))
{
	if (NULL == stack || 0 == stack->size)
	{
		errno = EINVAL;
		return;
	}

	p_slnode_t top = stack->top;

	while (top)
	{
		(*fp)(top->data);
		top = top->next;
	}
}

