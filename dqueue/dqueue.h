/******************************************************
  *       文件名: dqueue.h
  *
  *       文件描述: 双向队列头文件
  *
  *       创建人: Astrol     2011-12-8 15:45:43
  *
  *       版本号: 1.0
  *******************************************************/

#ifndef __DQUEUE_H__
#define __DQUEUE_H__

#include <stdbool.h>    /* C99特性 */
#include <stddef.h>
/* 队列结点定义 */
typedef struct dl_node
{
	void *data;
	struct dl_node *prev;
	struct dl_node *next;
}dl_node_t, *p_dl_node_t;

/* 队列结构定义 */
typedef struct dqueue
{
	size_t size;  			/* 队列大小 */
	struct dl_node *head;   	/* 对头指针,若队列不空,指向队列头结点 */
	struct dl_node *tail;   	/* 队尾指针,若不空,指向队尾元素,若为空,指向头结点 */
}dqueue_t, *p_dqueue_t;

/* 函数声明 */
p_dqueue_t dqueue_create(void);

bool dqueue_destroy(p_dqueue_t dqueue);

bool dqueue_empty(p_dqueue_t dqueue);

void *dqueue_gethead(p_dqueue_t dqueue);

bool dqueue_put(p_dqueue_t dqueue, void *data);

bool dqueue_pop_head(p_dqueue_t dqueue);

bool dqueue_pop_tail(p_dqueue_t dqueue);

bool dqueue_delete(p_dqueue_t dqueue);

void dqueue_print(p_dqueue_t dqueue, void (*fp)(void *data));

#endif  /* __DQUEUE_H__ */

