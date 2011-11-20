#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int* createdata(int* data);
void deletedata(int* data);
int match(int* data1, int* data2);
int* dupdata(int* data);
void print(int* data);
void err_exit(char* err_str);

int main(int argc, char* argv[])
{
	int i = 10;
	list_t* list = NULL;

	list = list_create(
		createdata,
		deletedata,
		match,
		dupdata,
		print,
		&i);



}

int* createdata(int * data)
{
	int* element = NULL;
	element = (int *)malloc(sizeof(int));
	if (NULL == element)
	{
		err_exit("create element error");
	}	
	element = data;
	return element;
}


