/*************************************************************************
*	文件名:	list.h
*
*	文件描述: 单链表头文件
*
*	创建人:	astrol 2012-2-11 8:49:15
*
*	版本号:	1.0	 
*
*	修改记录:
**************************************************************************/

#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>	/* C99 */
#include <stddef.h>		/* size_t */

/* 链表结点定义 */
typedef struct l_node {
	void *data;
	struct _l_node *next;
}l_node_t, *p_l_node_t;

typedef struct list {
	size_t size;		/* 链表大小 */
	p_l_node_t head;	/* 头指针, 若链表为空, 指向头结点 */
	p_l_node_t tail;	/* 尾指针, 若不空, 指向结点, 若为空, 指向头结点*/
}list_t, *p_list_t;

/* 函数声明 */
p_list_t list_create(void);

void list_destroy(p_list_t list);

bool list_insert(p_list_t );
#endif	/* __LIST_H__ */

