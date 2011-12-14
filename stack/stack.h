/*************************************************************
*	文件名: stack.h
*
*	文件描述: FIFO stack(链栈)
*
*	创建人: Astrol 2011-12-13 20:09:30
*
*	版本号: 1.0
*
*	修改记录:
**************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>	/* C99特性 */
#include <stddef.h>

/* 结点定义 */
typedef struct slnode
{
	void *data;
	struct slnode *next;
}slnode_t, *p_slnode_t;

/* 链栈定义 */
typedef struct stack
{
	size_t size;		/* 栈大小*/
	struct slnode *top;	/* 栈顶指针 */
	struct slnode *base;/* 在构造之前和销毁之后, base的值为NULL */
}stack_t, *p_stack_t;

/* 各种操作 */

p_stack_t stack_create(void);

bool stack_destroy(p_stack_t stack);

bool stack_empty(const p_stack_t stack);

bool stack_push(p_stack_t stack, void *data);

bool stack_pop(p_stack_t stack);

void *get_top(const p_stack_t stack);

void stack_print(const p_stack_t stack, void (*fp)(void *data));

#endif	/* __STACK_H__ */
