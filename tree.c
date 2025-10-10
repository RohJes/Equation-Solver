

//The tree that this program is built aroung is an unbalanced binary tree, hence this is what we'll be implemeniting

typedef struct Operator_Struct{
	uint16_t value;
	uint16_t id; //id is not unique, iff to branhes have the same valued children they should have the same value.
	Operator_Struct* left;
	Operator_Struct* right;
	Operator_Struct* parent; //The parent allows for faster algotithms
	uint8_t isleft; //boolean for if a left node or not, allows for faster graph traversal.
} Operator;

uint8_t Operator_isRoot(Operator* n){
	if(n->parent == NULL){
		return 1;
	else {
		return 0;
	}
}

uint8_t Operator_isEnd(Operator* n){
	if(n->left == NULL){ //if there is no left node there is no right node.
		return 1;
	} else {
		return 0;
	}
}


