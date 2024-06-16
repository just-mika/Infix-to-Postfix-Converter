#include <stdio.h>
#include <string.h>
#include "infix-to-postfix.c"
#include "evaluate-postfix.c"


int main() {
	String input;
	PostFixQ* postfix;
	
	do
	{
		scanf("%255s", input);
	
		if(strcmp(input, "QUIT") != 0){
			postfix = InfixToPostfix(input);
			printQueue(postfix);

			evaluatePostFix(postfix);
			printf("\n");
		}

	} while(strcmp(input, "QUIT") != 0);

	return 0;
}
