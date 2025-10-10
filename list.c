#include "list.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// All the nonsense in this is because the list uses generic types, 
// it does this by typecasting any pointer into a list of uin18_t

List List_Create(uint16_t eS){
	List l;
	l.elements = NULL;
	l.size = 0;	
	l.elementSize = eS;
	return l;
}

void List_Add(List* l, uint8_t* data){
	if(l->size == 0){
		l->elements = malloc(l->elementSize);
		for(uint16_t i = 0; i < l->elementSize; i++){
			*(l->elements + i) = *(data + i);
		}
	} else {
		uint8_t *n = malloc(l->elementSize * (l->size + 1));
		for(int i = 0; i < (l->size)*(l->elementSize); i++){
			*(n + i) = *(l->elements + i);
		}
		for(int i = 0; i < l->elementSize; i++){
			*(n + (l->size)*(l->elementSize) + i) = *(data + i);
		}
		free(l->elements);
		l->elements = n;
	}
	l->size += 1;
}

uint8_t* List_Get(List* l, uint16_t i){
	return (l->elements) + i*l->elementSize;
}

void List_Remove(List* l, uint16_t t){
	if(l->size < 2){
		free(l->elements);
		l->elements = NULL;
	} else {
		uint8_t* n = malloc(l->elementSize * (l->size - 1));
		uint16_t count = 0;
		for(uint16_t i = 0; i < t*l->elementSize; i++){
			*(n + count) = *(l->elements + i);
		       	count++;	
		}
		for(uint16_t i = l->elementSize*(t+1); i < l->elementSize*l->size; i++){
			*(n + count) = *(l->elements + i);
			count++;
		}
		free(l->elements);
		l->elements = n;
		l->size -= 1;
	}
}

void List_Insert(List*l, uint16_t index, uint8_t* data){
	if(l->size == 0){
		List_Add(l, data);
	} else {
		uint8_t* n = malloc(l->elementSize*(l->size + 1));
		uint16_t count = 0;
		for(int i = 0; i < index*l->elementSize; i++){
			*(n + count) = *(l->elements + i);
			count++;
		}
		for(int i = 0; i < l->elementSize; i++){
			*(n + count) = *(data + i);
			count++;
		}
		for(int i = l->elementSize*(index); i < l->elementSize*l->size; i++){
			*(n + count) = *(l->elements + i);
			count++;
		}
		free(l->elements);
		l->elements = n;
		l->size += 1;
	}
}

