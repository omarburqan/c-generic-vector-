
#include "test.h"


#include "vector.h"
#include <stdio.h>


void print_str(void *a){
	printf("%s, ",*(char**)(a));
}void print_int(void *a){
	printf("%d, ",*(int*)(a));
}

size_t cmp_str(void *a,void *b){
	char *X =*(char**)a;
	char* Y =*(char**)b;
	while(*X)
	{
		if (*X != *Y)
			break;
		X++;
		Y++;
	}
	return *(const unsigned char*)X - *(const unsigned char*)Y ==0;
}

size_t action_str(void *a){
	*(char**)a= "edited";
	return 0;
}
size_t action_str2(void *a){
	printf("%s, ",*(char**)(a));
	return 0;
}

void test(){
	char* a ="omar";
	char* b="omar";
	char* c="montaser";
	char* d="ibrahim";
	char* e="zaaaaraaaaa";
	
	void *res = NULL;
	void *res2 = NULL;
	Vector *v = vectorCreate(2);
	printf("\nvector after pushing new elements \n\t");

	vectorPush(v,&a);
	vectorPush(v,&b);
	vectorPush(v,&c);
	vectorPush(v,&d);
	vectorPrint(v,print_str);
	
	printf("vectors after inserting new elements\n\t");
	vectorInsert(v,&e,3);
	vectorPrint(v,print_str);
	

	vectorRemove(v,3,&res);  
	printf(" result after removing : %s\n ",*(char**)res);
	printf("vector after removing element 3\n\t");
	vectorPrint(v,print_str);

	vectorGetElement(v, 5, &res2); 
	if(res2)
		printf(" result of gett  : %s\n ",*(char**)res2);
	else
		printf("get element index out of range or null pointer\n");

	printf("vector after setting new element at index 3\n\t");
	vectorSetElement(v, 3, &c);
	vectorPrint(v,print_str);

	printf("count of value in vector is :\n\t");
	printf("%lu \n", vectorCount(v,&b,cmp_str));

	printf("calling vectorForEach when action is changing vector values :\n\t");
	vectorForEach(v,action_str); /* edit vector values for example */
	vectorForEach(v,action_str2); /* printing vector values */
	vectorDestroy(&v);


}

