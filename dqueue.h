/******************************************************
*	¿¿¿: dqueue.h	
*
*	¿¿¿¿: ¿¿¿¿¿¿¿
*
*	¿¿¿: Astrol	2011-12-8 15:45:43
*
*	¿¿¿: 1.0
*******************************************************/

#ifndef __DQUEUE_H__
#define __DQUEUE_H__

#include <stdbool.h>	/* C99¿¿ */
#include <stddef.h>
/*  ¿¿¿¿¿¿ */
typedef struct dl_node
{
	void *data;
	struct dl_node *prev;
	struct dl_node *next;
}dl_node_t, p_dl_node_t;

/* ¿¿¿¿¿¿ */
typedef struct dqueue
{
	size_t size;	/* ¿¿¿¿ */
	struct dl_node *head;	/* ¿¿¿¿, ¿¿¿¿¿, ¿¿¿¿¿¿¿ */
	struct dl_node *tail;	/* ¿¿¿¿, ¿¿¿, ¿¿¿¿¿¿, ¿¿¿, ¿¿¿¿¿ */
}dqueue_t, *p_dqueue_t;

/* ¿¿¿¿ */
p_dqueue_t dqueue_create(void);

bool dqueue_destroy(p_dqueue_t dqueue);

bool dqueue_empty(p_dqueue_t dqueue);

#endif	/* __DQUEUE_H__ */
