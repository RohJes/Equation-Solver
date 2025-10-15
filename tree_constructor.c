#include "list.h"
#include "tree.h"
#include <stdint.h>
#include <stdio.h>

typedef struct Dynamic_Tree{
	uint16_t size;
	uint16_t id;
	List list; //The list all the nodes are stored in.
} DTree;

DTree DTree_Create(){ //returns a newly configured D-Tree
	DTree t;
	t.list = List_Create(sizeof(Operator));
	t.size = 0;
	t.id = 0;
	return t;
}

Operator* Node_Get(DTree* tree, uint16_t node){
	Operator* m = (Operator*)List_Get(&tree->list, node);
}

uint16_t DTree_Add_Child(DTree* tree, uint16_t parent, uint8_t isRight, uint16_t value){  //fixed
	Operator n;
	tree->size++;
	if(tree->size == 0){
		n.parent = 0;
		n.left = 0;
		n.right = 0;
		n.direction = 0;
		n.id = tree->id;
		tree->id++;
		n.value = value;
		List_Add(&tree->list, (uint8_t*)(&n));
		uint16_t m = n.id;
		return m;
	} else {
		n.parent = parent;
		n.left = 0;
		n.right = 0;
		n.direction = isRight;
		n.id = tree->id;
		tree->id++;
		n.value = value;
		List_Add(&tree->list, (uint8_t*)(&n));
		uint16_t m = n.id;
		Operator* par = Node_Get(tree, parent);
		if(isRight == 0){
			par->left = m;
		} else {
			par->right = m;
		}
		return m;
	}
}

#define LEFT 0
#define RIGHT 1

void printLine(uint16_t n){ // this subroutine lowkey polutes the global namespace
	for(uint16_t i = 0; i < n; i++){
		printf("%s", "|  ");
	}
	printf("%s", "|--");
}

void DTree_Print(DTree* tree){  //fixed
	uint16_t walker = 0;
	uint8_t walker_last_direction = LEFT;
	uint8_t running = 1;
	uint16_t depth = 0;
	while(running == 1){
		printLine(depth);
		Operator* node  = Node_Get(tree, walker);
		printf("%d\n", node->value);
		if(Operator_isEnd(node) == 1){
			if(node->direction == RIGHT){
				while(node->direction == RIGHT){
					walker = node->parent;
					node = Node_Get(tree, walker);
					depth -= 1;
				}
				if(Operator_isRoot(node) || depth == 0){
					running = 0;
				} else {
					walker = node->parent;
					node = Node_Get(tree, walker);
					walker = node->right;
				}
			} else {  //walker->direction == LEFT
				walker = node->parent;
				node = Node_Get(tree, walker);
				walker = node->right;
			}
		} else {
			walker = node->left;
			depth++;
		}
	}
}

void DTree_Print_Blob(DTree* tree){
	for(uint16_t i = 0; i < tree->list.size; i++){
		Operator* node = (Operator*)List_Get(&tree->list, i);
		printf("%d %s: %d", i, "pointer", node);
		printf("%d %s: %d\n", i, "value:", node->value);
		printf("%d %s: %d\n", i, "id:", node->id);
		printf("%d %s: %d\n", i, "left:", node->left);
		printf("%d %s: %d\n", i, "right:", node->right);
		printf("%d %s: %d\n", i, "parent:", node->parent);
		printf("%d %s: %d\n", i, "direction:", node->direction);
	}
}

#define TRUE 1
#define FALSE 0 

uint8_t Node_Is_End(DTree* tree, uint16_t n){
	Operator* m = Node_Get(tree, n);
	return Operator_isEnd(m);
}

uint8_t Node_Is_Root(DTree* tree, uint16_t n){
	Operator* m = Node_Get(tree, n);
	return Operator_isRoot(m);
}

uint16_t Node_Get_Left(DTree* tree, uint16_t n){
	Operator* m = Node_Get(tree, n);
	return m->left;
}

uint16_t Node_Get_Right(DTree* tree, uint16_t n){
	Operator* m = Node_Get(tree, n);
	return m->right;
}

uint16_t Node_Get_Parent(DTree* tree, uint16_t n){
	Operator* m = Node_Get(tree, n);
	return m->parent;
}

uint16_t Node_Get_Value(DTree* tree, uint16_t n){
	Operator* m = Node_Get(tree, n);
	return m->value;
}

uint8_t Node_Get_Direction(DTree* tree, uint16_t n){
	Operator* m = Node_Get(tree, n);
	return m->direction;
}

uint8_t Compare_Sub_Tree(DTree* tree, uint16_t n, uint16_t m){  //finally works!!!
	uint16_t walker_m = m;
	uint16_t walker_n = n;
	uint8_t running_n = TRUE;
	uint8_t running_m = TRUE;
	while(running_n == TRUE || running_m == TRUE){
		if(Node_Get_Value(tree, walker_m) != Node_Get_Value(tree, walker_n)){
			return FALSE;
		}
		if(running_n == TRUE){
			if(Node_Is_End(tree, walker_n) == TRUE){
				if(Node_Get_Direction(tree, walker_n) == RIGHT){
					while(Node_Get_Direction(tree, walker_n) == RIGHT && walker_n != n){
						walker_n = Node_Get_Parent(tree, walker_n);
					}
					if(Node_Is_Root(tree, walker_n) || walker_n == n){
						running_n = FALSE;
					} else {
						walker_n = Node_Get_Parent(tree, walker_n);
						walker_n = Node_Get_Right(tree, walker_n);
					}
				} else { //direction must be left
					if(Node_Is_Root(tree, walker_n) == TRUE || walker_n == n){
						running_n = FALSE; // The Tree is one node big
					} else {
						walker_n = Node_Get_Parent(tree, walker_n);
						walker_n = Node_Get_Right(tree, walker_n);
					}
				}
			} else {
				walker_n = Node_Get_Left(tree, walker_n);
			}
		}
		if(running_m == TRUE){
			if(Node_Is_End(tree, walker_m) == TRUE){
				if(Node_Get_Direction(tree, walker_m) == RIGHT){
					while(Node_Get_Direction(tree, walker_m) == RIGHT && walker_m != m){
						walker_m = Node_Get_Parent(tree, walker_m);
					}
					if(Node_Is_Root(tree, walker_m) || walker_m == m){
						running_m = FALSE;
					} else {
						walker_m = Node_Get_Parent(tree, walker_m);
						walker_m = Node_Get_Right(tree, walker_m);
					}
				} else { //direction must be left
					if(Node_Is_Root(tree, walker_m) == TRUE || walker_m == m){
						running_m = FALSE; // The Tree is one node big
					} else {
						walker_m = Node_Get_Parent(tree, walker_m);
						walker_m = Node_Get_Right(tree, walker_m);
					}
				}
			} else {
				walker_m = Node_Get_Left(tree, walker_m);
			}

		}
	}
	return TRUE; //very rare to actually reach here	
}

int main(){
	DTree tree = DTree_Create();

	uint16_t root = DTree_Add_Child(&tree, 0, LEFT, 100);
	uint16_t branchOne = DTree_Add_Child(&tree, root, LEFT, 111);
	uint16_t branchTwo = DTree_Add_Child(&tree, root, RIGHT, 111);
	DTree_Add_Child(&tree, branchOne, LEFT, 112);
	DTree_Add_Child(&tree, branchOne, RIGHT, 113);
	DTree_Add_Child(&tree, branchTwo, LEFT, 112);
	DTree_Add_Child(&tree, branchTwo, RIGHT, 113);
	
	DTree_Print(&tree);

	printf("%d", Compare_Sub_Tree(&tree, branchOne, root));
}
