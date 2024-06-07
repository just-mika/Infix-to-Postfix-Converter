#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPERAND 1
#define OPERATOR 2

//QUEUE
typedef struct QueueTag{
    int dataType;
    int operand;
    char operator[3];
    struct QueueTag *next;
} PostFixQ;

//PostFixQ* initializeQueue();
int QisEmpty(PostFixQ* pFront, PostFixQ* pRear);
void enQueueOperand(int x);
void enQueueOperator(char x[]);
void deQueue();
void printQueue();
