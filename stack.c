#include "stack.h"

Node* Initialize(){ //initializes node
	return NULL; //returns null since it is an empty list
}

//checks if list/stack is empty
int isEmpty(Node* pTop){
	if(pTop == NULL) //if top is null, return 1
		return 1;
	else //otherwise, return 0
		return 0;
}

//prints the data contained at the top (use for debug)
void Top(Node* pTop){
	if(!isEmpty(pTop)) //if list isnt empty, print the top operator
		printf("Top value: %s\n", (pTop)->Operator);
}

//pushes value into the stack
//needs pointer to pointer of node parameter so that the pTop node's data can be changed.
void Push(Node** pTop, char data[]) {
	Node* node = (Node*)malloc(sizeof(Node)); //allocate memory for new node
	strcpy(node->Operator, data); //copy given data and place it inside the node
	node->pNext = *pTop; //set the previous top address as the next address of the new node
	*pTop = node; //set the new top as the new node.
}

//pop value out of the stack
//needs pointer to pointer of node parameter so that the pTop node's data can be changed.
void Pop(Node** pTop) { 
	if(!isEmpty(*pTop)){ //if stack isnt empty:
		Node* temp = *pTop; //create a temporary node and place the current data of pTop in it.
		*pTop = (*pTop)->pNext; //set the new top as the address the current top node is pointing towards to
		free(temp); //free the previous top.
	}
}