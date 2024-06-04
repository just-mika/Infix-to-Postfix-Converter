#include "stack.h"

OptNode* InitializeOpt(){ //initializes node for operator 
	return NULL; //returns null since it is an empty list
}

//checks if operator stack is empty
int OptisEmpty(OptNode* pTop){
	if(pTop == NULL) //if top is null, return 1
		return 1;
	else //otherwise, return 0
		return 0;
}

//prints the operator contained at the top (use for debug)
void OptTop(OptNode* pTop){
	if(!OptisEmpty(pTop)) //if list isnt empty, print the top operator
		printf("Top value: %s\n", (pTop)->Operator);
}

//pushes operator into the stack
//needs pointer to pointer of node parameter so that the pTop node's data can be changed.
void PushOperator(OptNode** pTop, char data[]) {
	OptNode* node = (OptNode*)malloc(sizeof(OptNode)); //allocate memory for new node
	strcpy(node->Operator, data); //copy given data and place it inside the node
	node->pNext = *pTop; //set the previous top address as the next address of the new node
	*pTop = node; //set the new top as the new node.
}

//pop value out of the stack
//needs pointer to pointer of node parameter so that the pTop node's data can be changed.
void PopOperator(OptNode** pTop) { 
	if(!OptisEmpty(*pTop)){ //if stack isnt empty:
		OptNode* temp = *pTop; //create a temporary node and place the current data of pTop in it.
		*pTop = (*pTop)->pNext; //set the new top as the address the current top node is pointing towards to
		free(temp); //free the previous top.
	}
}

OprNode* InitializeOpr(){ //initializes node for operand 
	return NULL; //returns null since it is an empty list
}

//checks if operand stack is empty
int OprisEmpty(OprNode* pTop){
	if(pTop == NULL) //if top is null, return 1
		return 1;
	else //otherwise, return 0
		return 0;
}

//prints the operand contained at the top (use for debug)
void OprTop(OprNode* pTop){
	if(!OprisEmpty(pTop)) //if list isnt empty, print the top operator
		printf("Top value: %d\n", (pTop)->Operand);
}

//pushes operand into the stack
//needs pointer to pointer of node parameter so that the pTop node's data can be changed.
void PushOperand(OprNode** pTop, int data) {
	OprNode* node = (OprNode*)malloc(sizeof(OprNode)); //allocate memory for new node
	node->Operand = data; //copy given data and place it inside the node
	node->pNext = *pTop; //set the previous top address as the next address of the new node
	*pTop = node; //set the new top as the new node.
}

//pop value out of the stack
//needs pointer to pointer of node parameter so that the pTop node's data can be changed.
void PopOperand(OprNode** pTop) { 
	if(!OprisEmpty(*pTop)){ //if stack isnt empty:
		OprNode* temp = *pTop; //create a temporary node and place the current data of pTop in it.
		*pTop = (*pTop)->pNext; //set the new top as the address the current top node is pointing towards to
		free(temp); //free the previous top.
	}
}