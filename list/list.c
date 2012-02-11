#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "list.h"

p_list_t list_create(void)
{
	p_list_t list = NULL;

	list = (p_list_t)malloc(sizeof(list_t));
	if (NULL == list)
	{
		errno = ENOMEM;
		return NULL;
	}

	list->size = 0;
	list->head = (p_l_node_t)malloc(sizeof(l_node_t));
	if (NULL == list->head)
	{
		free(list);	/* easy to forget */
		errno = ENOMEM;
		return NULL;
	}

	list->head->data = NULL;
	list->head->next = NULL;
	list->tail = list->head;

	return list;
}

void list_destroy(p_list_t list)
{
	int index = 0;
	p_l_node_t current = NULL, ptr = NULL;

	if (NULL == list)
	{
		errno = EINVAL;
		return;
	}
	
	ptr = current = list->head;
	for (index = 0; index < list->size; index++)
	{
		current = current->next;
		free(ptr->data);
		free(ptr);
		ptr = current;
	}

	free(list);	/* easy to forget */
}
