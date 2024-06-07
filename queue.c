#include "queue.h"

//global variables to store addresses of front and rear nodes
PostFixQ* pFront = NULL;
PostFixQ* pRear = NULL;

/*
PostFixQ* initializeQueue(){
    return NULL;
}
*/

/*
    checks if queue is empty
    @param *pFront - first node in the queue
    @param *pRear` - last node in the queue
*/
int QisEmpty(PostFixQ* pFront, PostFixQ* pRear){
    return pFront == NULL && pRear == NULL;

}

/*
    adds/enqueues operator to the rear of the queue
    @param opt[] - operator
*/
void enQueueOperator(char opt[]){
    PostFixQ* temp = (PostFixQ*)malloc(sizeof(PostFixQ));
    if(temp == NULL){
        printf("Memory allocation failed\n");
    }else{
        temp->dataType = OPERATOR;
        strcpy(temp->operator, opt);
        temp->next = NULL;
        if(QisEmpty(pFront, pRear)){
            pFront = temp;
            pRear = temp;
            //pFront and pRear will contain the same value
            //queue will have only one element after this
        }else{
            //cases where size of queue prior to function call is > 0
            pRear->next = temp; 
            pRear = temp; //value of temp will be stored to last node/rear in queue
        }
    }

}

/*
    adds/enqueues operand to the rear of the queue
    @param opr  - operand
*/
void enQueueOperand(int opr){
    PostFixQ* temp = (PostFixQ*)malloc(sizeof(PostFixQ));
    if(temp == NULL){
        printf("Memory allocation failed.\n");
    }else{
        temp->dataType = OPERAND;
        temp->operand = opr;
        temp->next = NULL;
        if(QisEmpty(pFront, pRear)){
            pFront = temp;
            pRear = temp;
        }else{
            pRear->next = temp;
            pRear = temp;
        }
    }
}


/*
    removes/dequeues the first node in queue -- pFront 
    then assigns the next node to pFront
*/
void deQueue(){
    PostFixQ* temp = pFront;
    //if queue is empty
    if(QisEmpty(pFront, pRear)){
        printf("QUEUE IS EMPTY");
    }
    //if there's only one node left in the queue
    if(pFront == pRear){
        pFront = NULL;
        pRear = NULL;
        //after function call, queue will be empty
    }else{
        pFront = pFront->next;
    }
    free(temp); //deallocates dynamically allocated memory
}

/*
    prints queue
*/
void printQueue() {
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


/*
in case you want to recheck
int main(){
    char input[3];
    int isOperand;
    int operand;
    char operator[3];
    while(strcmp(input, "x") != 0){
        printf("try:");
        scanf("%s", input);
        isOperand = atoi(input);
        if(input == 0 || isOperand){
            printf("Operand");
            operand = isOperand;
            printf("\n%d", operand);
            enQueueOperand(operand);
            printf("\n");
            printQueue();
        }else if(strcmp(input,"d") == 0){
            deQueue();
            printQueue();
        }
        else if(!isOperand && (strcmp(input,"d") != 0)){
            printf("Operator\n");
            strcpy(operator, input);
            printf("%s\n", operator);
            enQueueOperator(operator);
            printQueue();
        }
    }
    printQueue();

    return 0;
}
*/
