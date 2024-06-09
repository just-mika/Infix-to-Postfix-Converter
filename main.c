#include <stdio.h>
#include <string.h>
#include "infix-to-postfix.c"
//#include "evaluate-postfix.c"


int main() {
	String input;
	
	do
	{
		scanf("%255s", input);
	
		if(strcmp(input, "QUIT") != 0){
			InfixToPostfix(input);
			printQueue(); //Print postfix
		}

	} while(strcmp(input, "QUIT") != 0);

	return 0;
}