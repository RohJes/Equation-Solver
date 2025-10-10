#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	uint8_t* elements;
	uint16_t size;
	uint16_t elementSize;
} List;

List List_Create(uint16_t eS);

void List_Add(List* l, uint8_t* data);

uint8_t*  List_Get(List* l, uint16_t i);

void List_Remove(List* l, uint16_t t);

void List_Insert(List* l, uint16_t index, uint8_t* data);
