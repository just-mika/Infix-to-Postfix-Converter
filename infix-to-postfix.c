//INFIX TO POSTFIX ALGORIGHTM
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "header.h"
#include "stack.c"

	/*
	OPERATOR	ICP		ISP
	(			11		0
	!			10		9
	^			8		7
	*, /		6		6
	+, -		5		5
	>,>=,<,<=	4		4
	==,!=		3		3
	&&			2		2
	||			1		1 */

int getPriority(char Operator[3], int mode);
void clearString(char string[]){
	int i = 0, length = strlen(string);
	for(i = 0; i < length; i++)
		string[i] = '\0';
}

char * InfixToPostfix (String expression, String output) {
	Node* pTop = Initialize(); //initialize top
	String number = {};
	char Operator[3];
	
	int i = 0, j = 0, ISP, ICP;
	
	while(expression[i] != '\0'){
		//1. Get a token
		if(isdigit(expression[i])){
			while(isdigit(expression[i])){
				number[j] = expression[i];
				j++;
				i++;
			}
			number[j] = '\0';
			//2. if token is operand, goes to output
			//printf("number: %s\n", number);
			strcat(output, number);
			strcat(output, " ");
			//printf("output: %s\n", output);
			clearString(number);
			j = 0;
		}
		else {
		//	printf("Operator: %c\n", expression[i]);
			if(expression[i] != ')')
			{
				Operator[0] = expression[i];
				switch(Operator[0]){
					case '<':
					case '>':
					case '!':
						if(expression[i + 1] == '=')
							Operator[1] = '=';
						else
							Operator[1] = '\0';
						break;
					case '=':
						Operator[1] = '=';
						break;
					case '&':
						Operator[1] = '&';
						break;
					case '|':
						Operator[1] = '|';
						break;
					default:
						Operator[1] = '\0';
				}
				
				if(Operator[1] != '\0'){
					Operator[2] = '\0';
					i++;
				}
				//3. if token is operator or '('
				//	a. If ICP > ISP, push. go back to step 1
				//  b. else, pop top of stack. go back to step 3a.
				do {
					ICP = getPriority(Operator, 1);
					if(isEmpty(pTop))
						ISP = 0;
					else
						ISP = getPriority(pTop->Operator, 0);
					//printf("ICP = %d	ISP = %d\n", ICP, ISP);
					
					if(ICP > ISP){
						Push(&pTop, Operator);
						clearString(Operator);	
					}
					else {
						strcat(output, pTop->Operator);
						strcat(output, " ");
						Pop(&pTop);
					}
				//	Top(pTop);
				} while(ICP <= ISP);
			//	printf("output: %s\n", output);
			}
			//4. If token is ')'
			//	a. pop top of stack
			//	b. if current top is not correspoding '(', pop operator to output. go back to 4a.
			//	c. else, discard both parenthesis, and go back to step 1.
			else {
				do {
					strcat(output, pTop->Operator);
					strcat(output, " ");
					Pop(&pTop);
			//		Top(pTop);
				} while(strcmp(pTop->Operator, "(") != 0);
				Pop(&pTop);
			//	Top(pTop);
			//	printf("output: %s\n", output);
			}
			i++;
			//printf("\n");
		}
	}
	//5. if no more tokens, pop all elements (WORK IN PROGRESS)
	while(!isEmpty(pTop)) {
		strcat(output, pTop->Operator);
		strcat(output, " ");
		Pop(&pTop);
	//	Top(pTop);
	}
	
//	printf("output: %s\n", output);
	return output;

}

//returns the priority value of the given operator. mode 1 = get ICP, mode 0 = get ISP.
int getPriority(char Operator[3], int mode){
	char First = Operator[0];
	switch(First){
		case '(':
			if(mode)
				return 11;
			else
				return 0;
		case '!':
			if(Operator[1] == '=')
				return 3;
			else {
				if(mode)
					return 10;
				else
					return 9;
			}
		case '^':
			if(mode)
				return 8;
			else
				return 7;
		case '*':
		case '/':
			return 6;
		case '+':
		case '-':
			return 5;
		case '>':
		case '<':
			return 4;
		case '=':
			return 3;
		case '&':
			return 2;
		case '|':
			return 1;
	}
	return -1;
}
