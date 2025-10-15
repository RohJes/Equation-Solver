#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Operator_Struct{
	uint16_t value;
	uint16_t id;
	uint16_t left; //should be pointers but it didn't work out.
	uint16_t  right;
	uint16_t  parent;
	uint8_t direction;
} Operator;

uint8_t Operator_isRoot(Operator* n);
uint8_t Operator_isEnd(Operator* n);
