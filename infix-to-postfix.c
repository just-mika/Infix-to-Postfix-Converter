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
	OptNode* pTop = InitializeOpt(); //initialize top
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
			strcat(output, number);
			strcat(output, " ");
			clearString(number);
			j = 0;
		}
		else {
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
					if(OptisEmpty(pTop))
						ISP = 0;
					else
						ISP = getPriority(pTop->Operator, 0);
						
					if(ICP > ISP){
						PushOperator(&pTop, Operator);
						clearString(Operator);	
					}
					else {
						strcat(output, pTop->Operator);
						strcat(output, " ");
						PopOperator(&pTop);
					}
				} while(ICP <= ISP);
			}
			//4. If token is ')'
			//	a. pop top of stack
			//	b. if current top is not correspoding '(', pop operator to output. go back to 4a.
			//	c. else, discard both parenthesis, and go back to step 1.
			else {
				do {
					strcat(output, pTop->Operator);
					strcat(output, " ");
					PopOperator(&pTop);
				} while(strcmp(pTop->Operator, "(") != 0);
				PopOperator(&pTop);
			}
			i++;
		}
	}
	//5. if no more tokens, pop all elements
	while(!OptisEmpty(pTop)) {
		strcat(output, pTop->Operator);
		strcat(output, " ");
		PopOperator(&pTop);
	}
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
