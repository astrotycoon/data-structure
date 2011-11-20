#ifndef __LIST_H__
#ifndef __LIST_H__
/* for C++ complier */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIST_MALLOC
	#define LIST_MALLOC malloc
#endif

#ifndef LIST_FREE
	#define LIST_FREE free
#endif

#include <stddef.h>

/* list_node_t struct */
typedef struct list_node
{
	void* 		  data; /* generic pointer to data */
	struct list_node* prev;	/* link to previous node   */
	struct list_node* next; /* link to next node       */
}list_node_t;

/* list_t struct */
typedef struct list
{
	size_t len;
	list_node_t* head;
	list_node_t* tail;
	void* (*Lcreatedata)(void* data);   			/* create node              */
	void  (*Ldeletedata)(void* data);			/* delete node              */
	int   (*Lmatch)(const void* data1,const void* data2); 	/* data1 < data2, return -1 */
								/* data1 == data2, return 0 */
								/* data1 > data2, reruen 1  */
	void* (*Ldupdata)(void* data);				/* copy data                */
	void  (*Lprint)(void* data);				/* print the data           */
}list_t;

/* list_iterator_t direction */
typedef enum
{
	LIST_HEAD,
	LIST_TAIL
}list_direction_t;

/* list_iterator_t struct */
typedef list_iterator
{
	list_node_t*          next;
	list_direction_t direction;
}list_iterator_t;

/* list_node_t prototypes */
static list_node_t* list_node_create(list_t* list, void* data);

/* list_t prototypes */
extern list_t* list_create(
			void* (*createdata)(void* data),
			void  (*deletedata)(void* data),
			int   (*match)(void* data1, void* data2)
			void* (*dupdata)(void* data),
			void  (*print)(void* data));

extern void list_destroy(list_t* list);

extern bool list_prepend(list_t* list, void* data);
extern bool list_append(list_t* list, void* data);

//static bool list_insert_node_at_front(list_t* list, list_node_t* old_node, const void* data);
//static bool list_insett_node_at_later(list_t* list, list_node_t* old_node, const void* data);
extern bool list_insert_data_at_front(list_t* list, size_t index, const void* data);
extern bool list_insett_data_at_later(list_t* list, size_t index, const void* data);

//static bool list_delete_node(list_t* list, list_node_t* node);
extern bool list_delete_data_by_index(list_t* list, size_t index);
extern int list_delete_node_by_data(list_t* list, void* data);

//extern bool list_update_node(list_t* list, list_node_t* dst, list_node_t* src);
//extern bool list_update_node_at_index(list_t* list, size_t index, void * data);
//static bool list_update_node(list_t* list, list_node_t* dst, list_node_t* src);
extern bool list_update_data(list_t* list, size_t index, void* data);

extern int list_find_by_data(list_t* list, const void* data);
extern void* list_find_by_index(list_t* list, size_t index);

extern list_t* list_duplicate(list_t* list);

extern list_t* list_reversal(list_t* list);

extern void list_print(list_t* list);

/* list_iterater_t prototypes */
extern list_iterator_t* list_iterator_create(list_t* list, list_direction_t direaction);

static list_iterator_t* list_iterator_create_fome_node(list_node_t* node, list_iterator_t direction);
//extern list_node_t* list_iterator_next_node(list_iterator_t* iterator);
extern list_iterator_t* list_iterator_next_iterator(list_iterator_t* iterator);

extern void list_iterator_destroy(list_iterator_t* iterator);

#define Lhead(list)			((list)->head)
#define Ltail(list)			((list)->tail)
#define Node_Count(list) 		((list)->len)
#define Create_Data(list)		((list)->Lcreatedata)
#define Celete_Data(list)		((list)->Ldeletedata)
#define Match(list)			((list)->Lmatch)
#define Print(list)			((list)->Lprint)

#define list_iterator_node(iterator) 	((iterator)->next)
#define list_iterator_data(iterator) 	((iterator)->next->data)

#ifdef __cplusplus
}
#endif
	
#endif	/* __LIST_H__ */
