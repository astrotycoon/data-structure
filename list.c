#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* on error, NULL is returned. Othersize the pointer to the new list_node */
extern list_node_t* list_node_create(void* data)
{
	list_node_t* node_ret = NULL;

	if ((node_ret =(list_node_t *)LIST_MALLOC(sizeof(list_node_t))) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}

	node_ret->data = data;
	node_ret->prev = NULL;
	node_ret->next = NULL;
	
	return node_ret;
}

/* on error, NULL is returned. Othersize the pointer to the new list */
extern list_t* list_create(void)
{
	list_t* list_ret = NULL;

	if ((list_ret = (list_t *)LIST_MALLOC(sizeof(list_t))) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}

	list_ret->len = 0;
	list_ret->head = NULL;
	list_ret->tail = NULL;
	list_ret->destroy = NULL;
	list_ret->mathc = NULL;
	list_ret->duplicate = NULL;

	return list_ret;
}

extern void list_destroy(list_t* list)
{
	if (NULL == list)
	{
		errno = EINVAL;
		return;
	}

	size_t len = list->len;;
	list_node_t* next = NULL;
	list_node_t* current = list->head;

	while (len--)
	{
		next = current->next;
		if (list->destroy)
		{
			list->destroy(current->data);
		}
		LIST_FREE(current);
		current = next;
	}
	LIST_FREE(list);
}

extern list_t* list_prepend(list_t* list, void* data)
{
	if (NULL == list || NULL == data)
	{
		errno = EINVAL; 
		return NULL;
	}

	list_node_t* new_node = NULL;
	if ((new_node = (list_node_t *)LIST_MALLOC(sizeof(list_node))) == NULL)
	{
		errno = ENOMEM;
		return NULL;

	}
	new_node->data = data;
	
	if (list->len)
	{
		new_node->next = list->head;
		node->prev = NULL;
		list->head->prev = new_node;
		list->head = new_node;
	}
	else
	{
		list->head = list->tail = new_node;
		new_node->prev = new_node->next = NULL;	
	}
	
	++list->len;

	return list;
}
	
extern list+_t* list_append(list_t* list, void* data)
{
	if (NULL == list || NULL == node)
	{
		errno = EINVAL;
		return NULL;
	}
	
	list_node_t* new_node = NULL;
	if ((new_node = (list_node_t *)LIST_MALLOC(sizeof(list_node))) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}
	new_node->data = data;

	if (list->len)
	{
		new_node->next = NULL;
		new_node->prev = list->tail;
		list->tail->next = new_node;
		list->tail = new_node;
	}
	else
	{
		list->head = list->tail = node;
		node->prev = node->next = NULL;
	}
	
	++list->len;
	
	return list;

}

/* insert data into list "list" in the order before "old_node" */
extern bool list_insert_node_at_front(list_t* list, list_node_t* old_node, const void* data)
{
	if (NULL == list || NULL == old_node || NULL == data)
	{
		errno = EINVAL;
		return false;
	}

	list_node_t* new_node = NULL;
	if ((new_node = (list_node_t *)LIST_MALLOC(list_node_t)) == NULL)
	{
		errno = ENOMEM;
		return false;
	} 
	newnode->data = data;

	new_node->next = old_node;
	new_node->prev = old_node->prev;
	if (list->head == old_node)
	{
		list->head = new_node;
	}
	if (new_node->prev != NULL)
	{
		new_node->prev->next = new_node;
	}
	++list->len;

	return true;
}

/* insert data into list "list" in the order after "old_node"*/
extern bool list_insert_node_at_after(list_t* list, list_node_t* old_node, const void* data)
{
	if (NULL == list || NULL == old_node || NULL == data)
	{
		errno = EINVAL;
		return false;
	}
	
	list_nodt_t* new_node = NULL;
	if ((new_node = (list_node_t *)LIST_MALLOC(sizeof(list_node_t))) == NULL)
	{
		errno = ENOMEM;
		return false;
	}
	new_node->data = data;

	new_node->next = old_node->next;
	new_node->prev = old_node;
	if (old_node == list->tail)
	{
		list->tail = new_node;
	}
	if (new_node->next != NULL)
	{
		new_node->next->prev = new_node;
	}

	++list->len;
	return true;
}

extern bool list_insert_node_at_index(list_t* list, size_t index, const void* data)
{
	if (NULL == list || NULL == data || index)

}
