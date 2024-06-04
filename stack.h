typedef struct nodeTag
{
	char Operator[3];
	struct nodeTag *pNext;
} Node;


Node* Initialize();

int isEmpty(Node* pTop);

void Top(Node* pTop);

void Push(Node** pTop, char data[]);

void Pop(Node** pTop);