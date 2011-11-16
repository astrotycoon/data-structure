#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* on error, NULL is returned. Othersize the pointer to the new list_node */
extern list_node_t* list_node_create(list_t* list, void* data)
{
	list_node_t* node_ret = NULL;

	if ((node_ret =(list_node_t *)LIST_MALLOC(sizeof(list_node_t))) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}

	node_ret->prev = NULL;
	node_ret->next = NULL;
	if (list->createnode)
	{
		node_ret->data = list->createnode(data);
		if (NULL == node_ret->data)
		{
			LIST_FREE(node_ret);
			return NULL;
		}
	}	

	return node_ret;
}

/* on error, NULL is returned. Othersize the pointer to the new list */
extern list_t* list_create(
					void* (*createnode)(void* data),
					void  (*dstroy)(void* data),
					int (*match)(void* data1, void* data2))
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
	list_ret->Lcreatenode = createnode;
	list_ret->Ldestroy = destroy;
	list_ret->Lmatch = match;

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
	
extern list_t* list_append(list_t* list, void* data)
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
	if (NULL == list || 0 == list->len ||  NULL == data)
	{
		errno = EINVAL;
		return false;
	}

	list_node_t* new_node = NULL;
	if ((new_node = (list_node_t *)LIST_MALLOC(sizeof(list_node_t))) == NULL)
	{
		errno = ENOMEM;
		return false;
	}
	new_node->data = data;

	if (index < 0) //after tne reciprocal index
	{
		if (-1 == index)
		{
			LIST_FREE(new_node);
			list_append(list, data);
			return true;
		}
		
		list_node_t* current = list->tail;
		while (index < -1)
		{
			current = current->prev;
			++index;
		}
		
		new_node->prev = current;
		new_node->next = current->next;
		current->next->prev = new_node;
		current->next = new_node;
		++list->len;
	}
	else if (index == 1)
	{
		LIST_FREE(new_node);
		list_prepeng(list, data);
		return true;
	}
	else
	{
		list_node_t* current = list->head;
		while (index > 1)
		{
			current = current->next;
			--index;
		}
		new_node->next = current;
		new_node-prev = current->prev;
		current->prev->next = new_node;
		current->prev = new_node;
		++list->len;
	}
	return true;	
}

extern bool list_delete_node(list_t* list, list_node_t* node)
{
	if (NULL == list || NULL == node)
	{
		errno = EINVAL;
		return false;
	}

	if (NULL != node->prev)
		node->prev->next = node->next;
	else
		list->head = node->next;

	if (NULL != node->next)
		node->next->prev = node->prev;
	else
		list->tail = node->prev;
	if (list->destroy)
		list->destroy(node->data);

	LIST_FREE(node);
	--list->len;
	
	return true;	
}

extern bool list_delete_at_index(list_t* list, size_t index)
{
	if (NULL == list)
	{
		errno = EINVAL;
		return false;
	}

	list_node_t* current = NULL;
	if (index < 0)
	{
		current = list->tail;
		
		while (index < -1)
		{
			current = current->prev;
			++index;
		}
		
		if (current == list->tail)
		{
			current->prev->next = NULL;
			list->tail = current->prev;
			if (list->destroy)
				list->destroy(current->data);
			LIST_FREE(current);
			--list->len;
			return true;
		}
	}
	else
	{
		current = list->head;

		while (index > 1)
		{
			current = current->next;
			--index;
		}
		
		if (current == list->head)
		{
			current->next->prev = NULL;
			list->head = current->next;
			if (list->destroy)
				list->destroy(current->data);
			LIST_FREE(current);
			--list->len;
			return true;
		}
	}

	current->prev->next = current->next;
	current->next->prev = current->prev;
	if (list->destroy)
		list->destroy(current->data);
	LIST_FREE(curent);
	--list->len;
	return true;
}	

/* On error, 0 is returnd, or a non-zere is returnd */
extern int list_delete_node_by_data(list_t* list, void* data)
{
	if (NULL == list || NULL == data)
	{
		errno = EINVAL;
		return 0;
	}

	int index = 0;
	list_iterator_t* iterator = NULL;
	list_node_t* node = NULL;
	
	iterator = list_iterator_create(list);	
	
	while ((node = list_iterator_next(iterator)) != NULL)
	{
		++index;
		if (node->match)
		{
			if (0 == node->match(node->data, data))
			{
				list_delete_node(list, node);
			}
		}
		else
		{
			if (node->data == data)
			{
				list_delete_node(list, node);
			}
		}
	}
	list_iterator_destroy(itrator);
	return index;
}

static list_iterator_t* list_iterater_create(list_t* list, list_direction_t direction)
{
	list_node_t* node = direction == LIST_HEAD
	? list->head
	: list->tail;

	return list_iteraror_create_from_node(node, direction);	
}

static list_iterator_t* list_iterator_create_frome_node(list_node_t* node, list_iterator_t direction)
{
	list_iterator_t* iterator = NULL;
	if ((iterator = (list_iterator_t *)LIST_MALLOC(sizeof(list_iterator_t))) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}
	iterator->direction = direction;
	iterator->next = node;
	
	return iterator;
}

static list_node_t* list_iterator_next(list_iterator_t* iterator)
{
	list_node_t* node = NULL;
	
	node = iterator->direction == LIST_HEAD
	? iterator->next->next
	: iterator->next->prev;

	return node;
}
	
static void list_iterator_destroy(list_iterator_t* iterator)
{
	LIST_FREE(iterator);
}

extern bool list_update_node(list_t* list, list_node_t* dst, list_node_t* src)
{
	if (NULL == list || NULL == dst || NULL == src)
	{
		errno = EINVAL;
		return NULL;
	}
	
	src->next = dst->next;
	src->prev = dst->prev;
	dst->prev->next = src;
	dst->next->prev = src;

	if (dst->destroy)
		dst->destroy(dst->destroy);
	LIST_FREE(dst);
	
	return true;
}

extern bool list_update_node_at_index(list_t* list, size_t index, void* data)
{
	if (NULL == list || NULL == data)
	{
		errno = EINVAL;
		return NULL;
	}

	list_node_t* current = NULL;
	if (index < 0)
	{
		current = list->tail;
		while (index < -1)
		{
			current = current->prev;
			++index;
		}
	}
	else
	{
		current = list->head;
		while (index > 1)
		{
			current = current->next;
			--index;
		}
	}

	current->data = data;
	
	return true;
}

extern list_node_t* list_find_by_data(list_t* list, void* data)
{
	if (NULL == list || NULL == data)
	{
		errno = EINVAL;
		return NULL;
	}

	list_node_t* node = NULL;
	list_iterator_t* iterator = NULL;
	iterator = list_iterator_create(list, LIST_HEAD);
	while ((node = list_iterator_next(iterator)) != NULL)
	{
		if (list->match)
		{
			if (0 == list->match(node->data, data))
				return node;
		}
		else
		{
			if (node->data == data)
			{
				return node;
			}
		}
	}
	
	return NULL;
}

extern list_node_t* list_find_by_index(list_t* list, size_t index)
{
	if (NULL == list)
	{
		errno = EINVAL;
		return NULL;
	}
	
	list_node_t* current = NULL;
	if (index < 0)
	{
		current = list->tail;
		while (index < -1)
		{
			current = current->prev;
			++index;
		}
	}
	else
	{
		current = list->head;
		while (index > 1)
		{
			current = current->next;
			--index;
		}
	}
	
	return current;
}

extern list_t* list_duplicate(list_t* list)
{
	if (NULL == list)
	{
		errno = EINVAL;
		return NULL;
	}
	list_t* copy_list = NULL;
	list_iterator_t* iterator = NULL;
	list_node_t* node = NULL;

	if ((copy_list = (list_t *)LIST_MALLOC(sizeof(list_t))) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}
	copy_list->destroy = list->destroy;
	copy_list->match = list->match;
	copy_list->duplicate = list->duplicate;

	iterator = list_iterator_create(list, LIST_HEAD);
	while ((node = list_iterator_next(iterator)) != NULL)
	{
		void* data;
		
		if (list->duplicate)
		{
			data = list->duplicate(node->data);
			if (NULL == data)
			{
				list_destroy(copy_list);
				list_iterator_destroy(iterator);
				return NULL;
			}
		}
		else
		{
			data = node->data;
		}

		if (NULL == list_append(copy_list, data))
		{
			
			list_destroy(copy_list);
			list_iterator_destroy(iterator);
			return NULL;
		}
	}

	list_iterator_destroy(iterator);
	
	return copy_list;
}

extern list_t* list_reversal(list_t* list)
{
	if (NULL == list)
	{
		errno = EINVAL;
		return NULL;
	}

	list_node_t* top = list->head;
	list_node_t* end = list->tail;

	while (top != end)
	{
		list_node_t* next = top->next;
		list_node_t* prev = end->prev;

		top->next = NULL;
		top->prev = prev;
		end->next = next;
		end->prev = NULL;
		next->prev = end;
		prev->next = top;

		top = next;
		end = prev;
	}

	return list;
}	
