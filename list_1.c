#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* on error, NULL is returned. Othersize the pointer to the new list_node */
static list_node_t* list_node_create(list_t* list, void* data)
{
	list_node_t* node_ret = NULL;

	if ((node_ret =(list_node_t *)LIST_MALLOC(sizeof(list_node_t))) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}

	node_ret->prev = NULL;
	node_ret->next = NULL;
	node_ret->data = list->createdata(data);
	if (NULL == node_ret->data)
	{
		LIST_FREE(node_ret);
		return NULL;
	}

	return node_ret;
}

/* on error, NULL is returned. Othersize the pointer to the new list */
extern list_t* list_create(
			void* (*createdata)(void* data),
			void  (*deletedata)(void* data),
			int   (*match)(void* data1, void* data2),
			void* (*dupdata)(void* data),
			void  (*print)(void* data),
			void* data)
{
	list_t* list_ret = NULL;

	if ((list_ret = (list_t *)LIST_MALLOC(sizeof(list_t))) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}

	list_ret->len = 1;
	list_ret->Lcreatedata = createdata;
	list_ret->Ldeletedata = deletedata;
	list_ret->Lmatch = match;
	list_ret->Ldupdata = dupdata;
	list_ret->Lprint = print;
	list_ret->head = list_node_create(list_ret, data);
	if (NULL == list_ret->head)
	{
		LIST_FREE(list_ret);
		return NULL;
	}
	list_ret->tail = list_ret->head;

	return list_ret;
}

/* destroy the list*/
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

/* insert data into the list head */
extern bool list_prepend(list_t* list, void* data)
{
	if (NULL == list || NULL == data)
	{
		errno = EINVAL; 
		return false;
	}

	list_node_t* new_node = NULL;
	if ((new_node = list_node_create(list, data)) == NULL)
	{
		errno = ENOMEM;
		return false;
	}
	
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

	return true;
}

/* insert data into the end of list */	
extern bool list_append(list_t* list, void* data)
{
	if (NULL == list || NULL == node)
	{
		errno = EINVAL;
		return false;
	}
	
	list_node_t* new_node = NULL;
	if ((new_node = list_node_create(list, data)) == NULL)
	{
		errno = ENOMEM;
		return false;
	}

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
	
	return true;
}

/* insert node into list "list" in the order before "old_node" */
static bool list_insert_node_at_front(list_t* list, list_node_t* old_node, const void* data)
{
	list_node_t* new_node = NULL;
	if ((new_node = list_node_create(list, data)) == NULL)
	{
		errno = ENOMEM;
		return false;
	} 

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

/* insert node into list "list" in the order after "old_node"*/
static bool list_insert_node_at_after(list_t* list, list_node_t* old_node, const void* data)
{
	list_nodt_t* new_node = NULL;
	if ((new_node = list_node_create(list, data)) == NULL)
	{
		errno = ENOMEM;
		rturn false;
	}

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

extern bool list_insert_data_at_front(list_t* list, size_t index, const void* data)
{
	if (NULL == list || NULL == data || 0 == index
	|| index > list->len || index < ~list->len)
	{
		errno = EINVAL;
		rturn false;
	}
	
	list
	if (index < 0)
	{
		list_node_t* current = list->tail;
		while (index < -1)
		{
			current = current->prev;
			++index;
		}
		list_insert_node_at_front(list, current, data);
	}
	else
	{
		list_node_t* current = list->head;
		while (index > 1)
		{
			current = current->next;
			--index;
		}
		list_insert_node_at_front(list, current, data);
	}
	
	return true;
}

extern bool list_insert_data_at_after(list_t* list, size_t index, const void* data)
{
	if (NULL == list || NULL == data || 0 == index
 	|| index > list->len || index < ~(list->len))
	{
		errno = EINVAL;
		return false;
	}
	
	if (index < 1)
	{
		list_node_t* current = list->tail;
		while (index++ < -1)
		{
			current = current->prev;
		}
		list_insert_node_at_after(list, current, data);
	}	
	else
	{
		list_node_t* current = list->head;
		while (index-- > 1)
		{
			current = current->next;
		}
		list_insert_node_at_after(list, current, data);
	}

	return true;
}	

static bool list_delete_node(list_t* list, list_node_t* node)
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

extern bool list_delete_data_by_index(list_t* list, size_t index)
{
	if (NULL == list || 0 == index
	|| index > list->len || index < ~list->len)
	{
		errno = EINVAL;
		return false;
	}

	if (index < 0)
	{
		lsit_node_t* current = list->tail;

		while (index++ < -1)
		{
			current = current->prev;
		}
		list_delete_node(list, current);
	}
	else
	{
		list_node_t* current = list->head;

		while (index-- > 1)
		{
			current = current->next;
		}
		list_delete_node(list, current);
	}
	
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
	
	iterator = list_iterator_create(list, LIST_HEAD);	
	
	while (list_iterator_node(iterator) != NULL)
	{
		if (list->match)
		{
			index++;
			if (0 == list->match(list_iterator_data(iterator), data))
			{
				list_delete_node(list, list_iterator_node(iteraor));
				list_iterator_destroy(iterator);
				return index;
			}
		}
		else
		{
			index++;
			if (list_iterator_data(iterator) == data)
			{
				list_delete_node(list, list_iterator_node(iterator));
				list_iterator_destroy(iterator);
				return index;
			}
		}
		iterator = list_iterator_next_iterator(iterator);
	}
	list_iterator_destroy(itrator);
	return index;
}

/* create list iterator */
extern  list_iterator_t* list_iterater_create(list_t* list, list_direction_t direction)
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

/*	the classical usage pattern is:
 *
 *	iterator = list_iterator_create(list);
 *	while (list_iterator_null(iterator) != NULL)
 *	{
 *		doSomethingWith(list_iterator_data(iterator));
 *		iterator = list_iterator_next_iterator(iterator);
 *	}
 *
 */
extern list_iterator_t* list_iterator_next_iterator(list_iterator_t* iterator)
{
	iterator->next = iterator->direction == LIST_HEAD
	? iterator->next->next
	: iterator->next->prev;

	return iterator;
}
	
extern void list_iterator_destroy(list_iterator_t* iterator)
{
	LIST_FREE(iterator);
}

extern bool list_update_data(list_t* list, size_t index, void* data)
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
		while (index++ < -1)
		{
			current = current->prev;
		}
	}
	else
	{
		current = list->head;
		while (index-- > 1)
		{
			current = current->next;
		}
	}

	if (list->deletedata)
	{
		list->deletedata(data);
	}
	current->data = data;

	return true;
}

/* on error, 0 is returned. Otherwise the index of data id returned */
extern int list_find_by_data(list_t* list, void* data)
{
	if (NULL == list || NULL == data)
	{
		errno = EINVAL;
		return 0;
	}

	int index = 0;
	list_iterator_t* iterator = NULL;
	iterator = list_iterator_create(list, LIST_HEAD);
	while (list_iterator_node(iterator) != NULL)
	{
		++index;
		if (list->match)
		{
			if (0 == list->match(list_iterator_data(iterator), data))
				return index;
		}
		else
		{
			if (list_iterator_data(iterator) == data)
			{
				return index;
			}
		}
		iterator = list_iterator_next_iterator(iterator);
	}
	return 0;;
}

extern void* list_find_by_index(list_t* list, size_t index)
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
		while (index++ < -1)
		{
			current = current->prev;
		}
	}
	else
	{
		current = list->head;
		while (index-- > 1)
		{
			current = current->next;
		}
	}
	
	return current->data;
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

	if ((copy_list = list_create(
			list->Lcreatedata,
			list->Ldeletedate,
			list->Lmatch,
			list->Ldupdata,
			list->Lprint)) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}
	iterator = list_iterator_create(list, LIST_HEAD);
	while (list_iterator_node(iterator) != NULL)
	{
		void* data;
		
		if (list->duplicate)
		{
			data = list->duplicate(list_iterator_data(iterator));
			if (NULL == data)
			{
				list_destroy(copy_list);
				list_iterator_destroy(iterator);
				return NULL;
			}
		}
		else
		{
			data = list_iterator_data(iterator);
		}

		if (NULL == list_append(list_iterator_data(iterator), data))
		{
			
			list_destroy(copy_list);
			list_iterator_destroy(iterator);
			return NULL;
		}
		iterator = list_iterator_next_iterator(iterator);
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

extern void list_print(list_t* list)
{
	if (NULL == list)
	{
		errno = EINVAL;
		return;
	}

	iterator = list_iterator_create(list, LIST_HEAD);
	
	while (list_iterator_node(iterator) != NULL)
	{
		if (list->Lprint)
		{
			list->Lprint(list_iterator_data(iterator));
		}

		iterator = list_iterator_next_iterator(iterator);
	}
}	
