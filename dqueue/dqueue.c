/********************************************************
*	文件名: dqueue.c
*
*	文件描述: 双向循环队列操作的实现
*
*	创建人: Astrol 2011-12-7 19:18:22
*
*	版本号: 1.0
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "dqueue.h"

static p_dl_node_t node_create(void *data)
{
	p_dl_node_t node_ret = NULL;
	node_ret = (p_dl_node_t)malloc(sizeof(dl_node));
	if (NULL == node_ret)
	{
		errno = ENOMEM;
		return NULL;
	}
	
	node_ret->data = data;
	node_ret->prev = NULL;
	node_ret->next = NULL;
	
	return node_ret;
}

p_dqueue_t dqueue_create(void)
{
	p_dqueue_t dqueue_ret = NULL;
	
	dqueue_ret = (p_dqueue_t)malloc(sizeof(dqueue_t));
	if (NULL == dqueue_ret)
	{
		errno = ENOMEM;
		return NULL;
	}
	
	dqueue_ret->head = (p_dl_node_t)malloc(sizeof(dl_node));
	if (NULL == dqueue_ret->head)
	{
		free(dqueue_ret);	/* easy to forget */
		errno = ENOMEM;
		return NULL;
	}
	dqueue_ret->head->data = NULL;
	dqueue_ret->head->prev = NULL;
	dqueue_ret->head->next = NULL;
	dqueue_ret->size = 0;
	dqueue_ret->tail = dqueue_ret->head;
	
	return dqueue_ret;
}

bool dqueue_destroy(p_dqueue_t dqueue)
{
	if (NULL == dqueue)
	{
		errno = EINVAL;
		return false;
	}
	
	p_dl_node_t head = dqueue->head;	/* 指向第一个节点 */
	while (head)
	{
		p_dl_node_t temp = head;
		if (head->data)
		{
			free(head->data)
		}
		free(head);
		head = temp->next;
	}
	return true;
}

bool dqueue_empty(p_dqueue_t dqueue)
{
	if (NULL == dqueue || NULL == dqueue->head)
	{
		errno = EINVAL;
		return false;
	}
	
	return (dqueue->size == 0);
}

