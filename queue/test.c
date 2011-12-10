#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "queue.h"

void show(void *data);
int  compare(void *data1, void *data2);
void err_exit(char *str_err);
int main(void)
{
	printf("-----------------------\n");
	p_queue_t queue = NULL;
	int i;
	int *a = (int *)malloc(sizeof(int) * 10);
	for (i = 0; i < 10; i++)
	{
		a[i] = i;
	}
	for (i = 0; i < 10; i++)
	{
		printf("%4d", a[i]);
	}
	putchar('\n');
	printf("-----------------------\n");
	queue = queue_create();
	if (NULL == queue)
		err_exit("create error");
	queue_print(queue, show);
	printf("-----------------------\n");

	if (queue_empty(queue))
		printf("empty\n");
	for (i = 0; i < 10; i++)
	{
		if (!queue_put(queue, &a[i]))
			err_exit("put error");
	}
	if (!queue_empty(queue))
		printf("full\n");
	
	queue_print(queue, show);
	printf("\n%d\n", queue->size);
	printf("%d\n", *(int*)queue->head->data);
	printf("%d\n", *(int*)queue_gethead(queue));
	int *c = (int *)malloc(sizeof(int));
	*c = 4;
	if (queue_put(queue, c))
		printf("%d\n", queue->size);

	queue_print(queue, show);
	if (queue_delete(queue))
		printf("\n%d\n", queue->size);
	printf("\n%d\n", *(int*)queue->head->data);
	printf("%d\n", *(int*)queue_gethead(queue));
	queue_print(queue, show);

	putchar('\n');



	printf("****************************************************\n");
	p_queue_t queue_test = NULL;
	queue_test = queue_create();

	for (i = 0; i < 10; i++)
	{
		if (queue_insert_maxsize(queue_test, &a[i], compare) == false)
			err_exit("put error");
	}

	queue_print(queue_test, show);
	putchar('\n');


	
	printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
//	p_queue_t test = NULL;
//	test = queue_create();
//	if (NULL == test)
//		err_exit("create error");
//
	for (i = 0; i < 10; i++)
	{
		if (queue_insert_minsize(queue_test, &a[i], compare) == false)
			err_exit("put error");
	}	
	queue_print(queue_test, show);
	printf("\n\n");
	for (i = 0; i < 10; i++)
	{
		if (queue_insert_minsize(queue_test, &a[i], compare) == false)
			err_exit("put error");
	}	
	queue_print(queue_test, show);
	putchar('\n');

	
	printf("############################################################\n");
	int *p = (int *)malloc(sizeof(int)* 10);
	for (i = 0; i < 10; i++)
	{
		p[i] = i % 3;
	}

	for (i = 0; i < 10; i++)
	{
		printf("%4d", p[i]);
	}
	putchar('\n');
	p_queue_t test = NULL;
	test = queue_create();
	if (NULL == test)
		err_exit("create error");

	for (i = 0; i < 10; i++)
	{
		if (queue_insert_minsize(test, p + i, compare) == false)
			err_exit("put error");
	}
	queue_print(test, show);
	putchar('\n');
	
	printf("%4d\n", test->size);
	printf("%4d\n",*((int *)test->head->data));
	printf("%4d\n", *((int *)test->head->next->data));

	queue_destroy(test);
	putchar('\n');
	return 0;
}

void err_exit(char *str_err)
{
	perror(str_err);
	exit(EXIT_FAILURE);
}

void show(void *data)
{
	printf("%4d", *(int*)data);
}

int compare(void *data1, void *data2)
{
	int *p = (int *)data1;
	int *q = (int *)data2;

	if ((*p - *q) > 0)
		return 1;
	else if ((*p - *q) == 0) 
		return 0;
	else if ((*p - *q) < 0)
		return -1;

}
