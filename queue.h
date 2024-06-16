#ifndef QUEUE_H
#define QUEUE_H

#define OPERAND 1
#define OPERATOR 2

//QUEUE
typedef struct QueueTag{
    int dataType;
    int operand;
    char operator[3];
    struct QueueTag *next;
} PostFixQ;

PostFixQ* initializeQueue();
int QisEmpty(PostFixQ* pFront);
void enQueueOperand(PostFixQ** pFront, PostFixQ** pRear, int opr);
void enQueueOperator(PostFixQ** pFront, PostFixQ** pRear, char opt[]);
void deQueue(PostFixQ** pFront);
void printQueue(PostFixQ* pFront);

#endif
