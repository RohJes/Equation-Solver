

//The tree that this program is built aroung is an unbalanced binary tree, hence this is what we'll be implemeniting

typedef struct Operator_Struct{
	uint16_t value;
	uint16_t id; //id is not unique, iff to branhes have the same valued children they should have the same value.
	Operator_Struct* left;
	Operator_Struct* right;
	Operator_Struct* parent; //The parent allows for faster algotithms
	uint8_t direction; //boolean for if a left node or not, allows for faster graph traversal.
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

#define LEFT 0
#define RIGHT 1

uint8_t Operator_Compare(Operator* n, Operator* m){
	uint8_t is_n_end = Operator_isEnd(n);
	uint8_t is_m_end = Operator_isEnd(m);
	if(is_n_end && is_m_end){
		if(m->value == n->value){
			return 1;
		} else {
			return 0;
		}
	}
	if(is_n_end){
		return 0;
	}
	if(is_m_end){
		return 0;
	}

	Operator* walker_n = n;
	Operator* walker_m = m;
	uint8_t walker_n_last_direction = LEFT;
	uint8_t walker_m_last_direction = RIGHT;

	uint8 running = 1;
	while(running == 1){
		if(walker_m->value != walker_n->value){
			return 0;
		}
		if(Operator_isEnd(walker_n) == 1){
			if(walker_n_last_direction == LEFT){
				walker_n = walker_n->parent;
				walker_n = walker_n->right;
				walker_n_last_direction == RIGHT;
			}
			if(walker_n_last_direction == RIGHT){
				uint8_t direction = RIGHT;
				while(direction == RIGHT){
					walker_n = walker_n->parent;
					direction = walker_n->direction;
				}
				if(Operator_isRoot(walker_n) == 0){
					walker_n = walker_n->parent;
					walker_n = walker_n->right;
					walker_n_last_direction = RIGHT;
				} else {
					running == 0;
				}
			}
		} else {
			walker_n->left;
			walker_n_direction = LEFT;
		}
		if(Operator_isEnd(walker_m) == 1){
			if(walker_m_last_direction == LEFT){
				walker_m = walker_m->parent;
				walker_m = walker_m->right;
				walker_m_last_direction == RIGHT;
			}
			if(walker_m_last_direction == RIGHT){
				uint8_t direction = RIGHT;
				while(direction == RIGHT){
					walker_m = walker_m->parent;
					direction = walker_m->direction;
				}
				if(Operator_isRoot(walker_m) == 0){
					walker_m = walker_m->parent;
					walker_m = walker_m->right;
					walker_m_last_direction = RIGHT;
				} else {
					running == 0;
				}
			}
		} else {
			walker_m->left;
			walker_m_direction = LEFT;
		}	
	}
	return 1; //basically never reaches though it kind of needs too sometimes;
}

uint8_t Operators_Pattern_Match(Operator* pattern, Operator* n){

}
