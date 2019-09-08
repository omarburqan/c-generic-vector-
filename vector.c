#include "vector.h"

struct Vector {
    void** items;
    size_t capacity;
    size_t total; /* number of items */

};

Vector* vectorCreate(size_t size){ 
    Vector *v = malloc(sizeof(Vector));
    if(!v)
    	return NULL;
    v->capacity = size;
    v->total = 0;
    v->items = malloc(sizeof(void*) * v->capacity);
   	if (!v->items)
   		return NULL;
    return v;
}

ErrorCode vectorDestroy(Vector **vector){
	if ( !vector ) /*  if vector is null do nothing just return */
		return E_NULL_PTR;
	if ( !(*vector)->items ){ /* vector->items is null as you have to free the vector and return */ 
		free(*vector);
		return E_NULL_PTR;	
	}					
	/* else free everything :P */
	free((*vector)->items);
	free(*vector);
	return E_OK;
}
ErrorCode vectorPush(Vector *vector, void *value){
	if (!vector){
		return E_NULL_PTR;
	}
	if (vector->capacity == vector->total){ /* when realloc() fails in allocating memory, original pointer is lost */
		void *res = realloc(vector->items,sizeof(void*) * vector->capacity * 2);
    	if (res) {
        	vector->capacity *= 2;
        	vector->items = res;
        }
        else {
        	return E_ALLOCATION_ERROR;
        }
    }    

	vector->items[vector->total++] = value;
    return E_OK;
}
ErrorCode vectorInsert(Vector *vector, void* value, size_t index){
	size_t i ;
	if (!vector){
		return E_NULL_PTR;
	}
	if( vector->total+1 == index ){
		return vectorPush(vector,value);
	}
	if ( index > (vector->total) || index == 0){
		return E_BAD_INDEX;
	}
	/* validate overflow. IF full re-allocate */
	if (vector->capacity == vector->total){ /* when realloc() fails in allocating memory, original pointer is lost */
		void *res = realloc(vector->items,sizeof(void*) * vector->capacity * 2);
    	if (res) {
        	vector->capacity *= 2;
        	vector->items = res;
        }
        else {
        	return E_ALLOCATION_ERROR;
        }
    } 
	/* Shifting */
	vector->total++;
	for (i = vector->total-1; i >= index; i--){
		vector->items[i] = vector->items[i-1];
	}
    vector->items[index-1] = value;
	return E_OK;


}
ErrorCode vectorPop(Vector *vector, void **res){
	return vectorRemove(vector,1,res);
}

ErrorCode vectorRemove(Vector *vector, size_t index, void **res){
	size_t i ;
	if ( index > (vector->total) || index == 0){
		return E_BAD_INDEX;
	}
	if (!vector){
		return E_NULL_PTR;
	}
	
	*res = vector->items[index-1] ;	
    for (i = index-1; i <= vector->total -2 ; i++){
  			vector->items[i] = vector->items[i+1];
	}

	vector->total--;
	return E_OK;
}


ErrorCode vectorGetElement(const Vector *vector, size_t index, void **res){
	if ( index > (vector->total) || index == 0){
		return E_BAD_INDEX;
	}
	if (!vector){
		return E_NULL_PTR;
	}
	*res = vector->items[index-1];
	return E_OK;
}
ErrorCode vectorSetElement(Vector *vector, size_t index, void* value){
	if ( index > (vector->total) || index == 0){
		return E_BAD_INDEX;
	}
	if (!vector){
		return E_NULL_PTR;
	}
	vector->items[index-1]=value;
	return E_OK;
}

size_t vectorGetSize(const Vector *vector){
	if (vector)
		return vector->total;
	return E_NULL_PTR;
}
size_t vectorGetCapacity(const Vector *vector){
	if (vector)
		return vector->capacity;
	return E_NULL_PTR;
}

size_t vectorCount(const Vector *vector, void* value,CmpFunc cf){
	size_t i,count=0;
	for (i=0;i < vector->total;i++){
		if (cf(vector->items[i],value)){
			++count;
		}
	}
	return count;

}
void vectorPrint(Vector *vector,PrintFunc pf){
	if(vector){
		size_t i ;
    	for (i=0 ; i < vector->total; i++) {
    		pf(vector->items[i]);

    	}
    	printf("\n");
	}
}

size_t vectorForEach(Vector *vector,actionFunc aF){
	size_t i,target=0 ;
	if(vector){

		for (i=0 ; i < vector->total; i++) {
			
			target = aF(vector->items[i]) ? i:target;

		}
	    	printf("\n");
	}
	return target;

}


