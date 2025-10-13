#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Operator_Struct{
	uint16_t value;
	uint16_t id;
	struct Operator_Struct* left;
	struct Operator_Struct* right;
	struct Operator_Struct* parent;
	uint8_t direction;
} Operator;

uint8_t Operator_isRoot(Operator* n);
uint8_t Operator_isEnd(Operator*n);

uint8_t Operator_Compare(Operator* n, Operator* m);
