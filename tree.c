#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//The tree that this program is built aroung is an unbalanced binary tree, hence this is what we'll be implemeniting

uint8_t Operator_isRoot(Operator* n){
	if(n->id == 0){
		return 1;
	} else {
		return 0;
	}
}

uint8_t Operator_isEnd(Operator* n){
	if(n->left == 0){ //if there is no left node there is no right node.
		return 1;
	} else {
		return 0;
	}
}

#define LEFT 0
#define RIGHT 1


//uint8_t Operators_Pattern_Match(Operator* pattern, Operator* n){
	
//}
