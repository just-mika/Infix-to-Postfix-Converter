#include <stdio.h>
#include <string.h>
#include "infix-to-postfix.c"
//include evaluate.c here


int main() {
	String expression;
	String PostFix = {};
	
	do
	{
		scanf("%255s", expression);
	
		if(strcmp(expression, "QUIT") != 0){
				printf("%s\n", InfixToPostfix(expression, PostFix)); //postfix
			printf("\n"); //place evaluation here
			clearString(PostFix); //clear output string each iteration!
		}
	} while(strcmp(expression, "QUIT") != 0);

	return 0;
}