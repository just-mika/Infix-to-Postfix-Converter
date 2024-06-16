//FOR OPERATOR STACK
typedef struct OperatorNodeTag
{
	char Operator[3];
	struct OperatorNodeTag *pNext;
} OptNode;

OptNode* InitializeOpt();
int OptisEmpty(OptNode* pTop);
void OptTop(OptNode* pTop);
void PushOperator(OptNode** pTop, char data[]);
void PopOperator(OptNode** pTop);

//FOR OPERAND STACK
typedef struct OperandNodeTag
{
	int Operand;
	struct OperandNodeTag *pNext;
} OprNode;

OprNode* InitializeOpr();
int OprisEmpty(OprNode* pTop);
OprNode* OprTop(OprNode* pTop);
void PushOperand(OprNode** pTop, int data);
void PopOperand(OprNode** pTop);
