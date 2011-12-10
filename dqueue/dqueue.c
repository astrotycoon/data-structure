/*********************************************************
*	文件名: dqueue.c
*
*	文件描述：双向队列函数实现
*
*	创建人: Astrol 2011-12-8 16:02:33
*
*	版本号: 1.0
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "dqueue.h"

static p_dl_node_t node_create(void *data)
{
	p_dl_node_t new_node = NULL;
	new_node = (p_dl_node_t)malloc(sizeof(dl_node_t));
	if (NULL == new_node)
	{
		errno = ENOMEM;
		return NULL;
	}
	new_node->data = data;
	new_node->prev = NULL;
	new_node->next = NULL;

	return new_node;
}

p_dqueue_t dqueue_create(void)
{
	p_dqueue_t dqueue = NULL;

	dqueue = (p_dqueue_t)malloc(sizeof(dqueue_t));
	if (NULL == dqueue)
	{
		errno = ENOMEM;
		return NULL;
	}
	dqueue->head = node_create(NULL);
	if (NULL == dqueue->head)
	{
		free(dqueue);
		errno = ENOMEM;
		return NULL;
	}
	dqueue->size = 0;
	dqueue->tail = dqueue->head;

	return dqueue;
}	

bool dqueue_destroy(p_dqueue_t dqueue)
{
	if (NULL == dqueue)
	{
		errno = EINVAL;
		return false;
	}
	size_t count = 0;

	for (count = dqueue->size; count >= 1; --count)
	{
		dqueue_delete(dqueue);
	}
	free(dqueue);

	return true;
}

bool dqueue_empty(p_dqueue_t dqueue)
{
	if (NULL == dqueue)
	{
		errno = EINVAL;
		return false;
	}

	return (dqueue->size == 0);

}

void *dqueue_gethead(p_dqueue_t dqueue)
{
	if (NULL == dqueue || 0 == dqueue->size)
	{
		errno = EINVAL;
		return NULL;
	}
	return dqueue->head->data;
}

bool dqueue_put(p_dqueue_t dqueue, void *data)
{
	if (NULL == dqueue || NULL == dqueue->head)
	{
		errno = EINVAL;
		return false;
	}

	if (0 == dqueue->size)
	{
		dqueue->head->data = data;
		dqueue->size++;
		return true;
	}

	p_dl_node_t new_node = NULL;
	new_node = node_create(data);
	if (NULL == new_node)
	{
		errno = ENOMEM;
		return false;
	}
	
	new_node->prev = dqueue->tail;
	new_node->next = NULL;
	dqueue->tail->next = new_node;
	dqueue->tail = new_node;
	dqueue->size++;

	return true;
}

bool dqueue_pop_head(p_dqueue_t dqueue)
{
	if (NULL == dqueue || 0 == dqueue->size)
	{
		errno = EINVAL;
		return false;
	}
	
	p_dl_node_t head = dqueue->head->next;
	free(dqueue->head->data);
	free(dqueue->head);
	dqueue->head = head;
	if (NULL != dqueue->head)
	{
		dqueue->head->prev = NULL;
	}
	dqueue->size--;

	return true;
}

bool dqueue_delete(p_dqueue_t dqueue)
{
	if (NULL == dqueue || 0 == dqueue->size)
	{
		errno = EINVAL;
		return false;
	}

	p_dl_node_t head = dqueue->head;	/* head指向队列头结点 */
	free(head->data);
	free(head);
	dqueue->head = dqueue->head->next;
	if (NULL != dqueue->head)
	{
		dqueue->head->prev = NULL;
	}
	dqueue->size--;

	return true;
}

void dqueue_print(p_dqueue_t dqueue, void (*fp)(void *data))
{
	if (NULL == dqueue || 0 == dqueue->size)
	{
		errno = EINVAL;
		return;
	}
	p_dl_node_t head = dqueue->head;
	while (head)
	{
		(*fp)(head->data);
		head = head->next;
	}
}

