#include <stdio.h>
  int main (void)
  { 
	 
	  int i, a[4];
	  int * p=a ;

	  for  (i=0;i<4;i++) 
          scanf(" %d", &p[i]);
          printf (" \n" );

	  

    
      	for  (i=0;i<4;i++) 
	printf (" %d\t\n", p[i]);
        printf (" %#x\n", a );

        printf (" %d\n", a[0]);
        printf (" %#x\n", a);
		 
	printf("type  int has a size of %u byte \n ", sizeof(int));
	printf("type int has a size of %u byte\n", sizeof(int));
	printf("type char has a size of %u byte \n ", sizeof(char));
   	printf("type double has a size of %u byte \n ", sizeof(double long));
   	printf("type long int has a size of %u byte \n ", sizeof(long int));
	printf("type short int has a size of %u byte\n  ", sizeof(short int));
  	printf("\n"); 
	printf("type  int has a size of %d byte \n ", sizeof(int));
	printf("type int has a size of %d byte\n", sizeof(int));
	printf("type char has a size of %d byte \n ", sizeof(char));
   	printf("type double has a size of %d byte \n ", sizeof(double long));
   	printf("type long int has a size of %d byte \n ", sizeof(long int));
	printf("type short int has a size of %d byte\n  ", sizeof(short int));
   
  	return 0;
  
  
 }

