#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "dqueue.h"

void err_exit(char *str_err);
void print(void *data);


typedef struct example
{
	int a;
	int b;
}exam;
exam *make(int n);

int main(int argc, char *argv[])
{
	p_dqueue_t dqueue = NULL;
	dqueue = dqueue_create();
	if (NULL == dqueue)
	{
		err_exit("create error");
	}
	if (dqueue_empty(dqueue))
	{
		printf("==========>empty<============\n");
	}
	else
	{
		printf("==========>full<=============\n");
	}
	int i;

	for (i = 0; i < 10; i++)
	{
		if (!dqueue_put(dqueue, make(i)))
		{
			err_exit("put error");
		}
	}
	if (dqueue_empty(dqueue))
	{
		printf("==========>empty<============\n");
	}
	else
	{
		printf("==========>full<=============\n");
	}
	dqueue_print(dqueue, print);

	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');
	
	
//	dqueue_destroy(dqueue);
	putchar('\n');
	

	if (dqueue_pop_head(dqueue))
	{
		dqueue_print(dqueue, print);
	}
	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');
	
	
	
	if (dqueue_pop_head(dqueue))
	{
		dqueue_print(dqueue, print);
	}
	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');
	
	
	
	
	
	if (dqueue_pop_head(dqueue))
	{
		dqueue_print(dqueue, print);
	}
	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');
	
	
	
	
	
	if (dqueue_pop_head(dqueue))
	{
		dqueue_print(dqueue, print);
	}
	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');
	
	
	
	
	if (dqueue_pop_head(dqueue))
	{
		dqueue_print(dqueue, print);
	}
	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');
	
	
	
	if (dqueue_pop_head(dqueue))
	{
		dqueue_print(dqueue, print);
	}
	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');
	
	
	
	
	if (dqueue_pop_head(dqueue))
	{
		dqueue_print(dqueue, print);
	}
	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');
	
	
	if (dqueue_pop_head(dqueue))
	{
		dqueue_print(dqueue, print);
	}
	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');
	
	
	
	if (dqueue_pop_head(dqueue))
	{
		dqueue_print(dqueue, print);
	}
	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');
	
	
	
	

	if (dqueue_pop_head(dqueue))
	{
		printf("%d\n", dqueue->size);
		dqueue_print(dqueue, print);
	}
	putchar('\n');
	printf("The first element is %d\n", *(int *)dqueue_gethead(dqueue));
	putchar('\n');


	putchar('\n');

	putchar('\n');

	putchar('\n');
	return 0;
}	


void err_exit(char *str_err)
{
	perror(str_err);
	exit(EXIT_FAILURE);
}

void print(void *data)
{
	printf("%4d\n", ((exam *)data)->a);
	printf("%4d\n", ((exam *)data)->b);
}

exam *make(int n)
{
	exam *ret = (exam *)malloc(sizeof(exam));
	if (NULL == ret)
	{
		err_exit("malloc error");
	}

	ret->a = n;
	ret->b = n;

	return ret;
}
