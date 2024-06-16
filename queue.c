#include "queue.h"

PostFixQ* initializeQueue(){
    return NULL;
}


/*
    checks if queue is empty
    @param *pFront - first node in the queue
*/
int QisEmpty(PostFixQ* pFront){
    return pFront == NULL;

}

/*
    adds/enqueues operator to the rear of the queue
    @param **pFront - head node
    @param **pTail  - tail node, value changes to opt[]
    @param opt[]    - operator
*/
void enQueueOperator(PostFixQ** pFront, PostFixQ** pRear, char opt[]){
    PostFixQ* temp = (PostFixQ*)malloc(sizeof(PostFixQ));
    if(temp == NULL){
        printf("Memory allocation failed\n");
    }else{
        temp->dataType = OPERATOR;
        strcpy(temp->operator, opt);
        temp->next = NULL;
        if(QisEmpty(*pFront)){
            *pFront = temp;
            *pRear = temp;
            //pFront and pRear will contain the same value
            //queue will have only one element after this
        }else{
            //cases where size of queue prior to function call is > 0
            (*pRear)->next = temp; 
            *pRear = temp; //value of temp will be stored to last node/rear in queue
        }
    }

}

/*
    adds/enqueues operand to the rear of the queue
    @param **pFront - head node
    @param **pRear  - tail node, value changes to opr
    @param opr      - operand to be added to queue
*/
void enQueueOperand(PostFixQ** pFront, PostFixQ** pRear, int opr){
    PostFixQ* temp = (PostFixQ*)malloc(sizeof(PostFixQ));
    if(temp == NULL){
        printf("Memory allocation failed.\n");
    }else{
        temp->dataType = OPERAND;
        temp->operand = opr;
        temp->next = NULL;
        if(QisEmpty(*pFront)){
            *pFront = temp;
            *pRear = temp;
        }else{
            (*pRear)->next = temp;
            *pRear = temp;
        }
    }
}


/*
    removes/dequeues the first node in queue -- pFront 
    then assigns the next node to pFront
    @param **pFront - value at head, value updates to the next node
*/
void deQueue(PostFixQ** pFront){
    PostFixQ* temp = *pFront;
    //if queue is empty
    if(QisEmpty(*pFront)){
        printf("QUEUE IS EMPTY");
    }
    //if there's only one node left in the queue
    if((*pFront)->next == *pFront){
        pFront = NULL;
        //after function call, queue will be empty
    }else{
        *pFront = (*pFront)->next;
    }
    free(temp); //deallocates dynamically allocated memory
}

/*
    prints queue
    @param *pFront  - head node of queue to be printed
*/
void printQueue(PostFixQ* pFront) {
	PostFixQ* temp = pFront;
	while(temp != NULL) {
        //check if operator and operand
		if(temp->dataType == OPERATOR){
            printf("%s ", temp->operator);
        }else{
            printf("%d ", temp->operand);
        }
		temp = temp->next;  
	}
	printf("\n");
}
