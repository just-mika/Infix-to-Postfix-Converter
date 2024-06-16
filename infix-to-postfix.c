//INFIX TO POSTFIX ALGORIGHTM
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "queue.c"
#include "header.h"
#include "stack.c"

//function that returns the priority of the given operator based on the mode
int getPriority(char Operator[3], int mode);
/*
	clears all elements inside the character array
	@param string[] - character array/string that contains characters
*/
void clearString(char string[]){
	//place the current length of the string in a variable
	int length = strlen(string);
	for(int i = 0; i < length; i++) //for loop to set all elements to '\0'
		string[i] = '\0';
}

/*
	converts a given infix expression to its equivalent postfix expresson
	@param expression - String that contains the inputted infix expression
*/
void InfixToPostfix (String expression) {
	OptNode* pTop = InitializeOpt(); //initialize top
	String number = {}; //declare a variable for the read opperands
	char Operator[3]; //declare a variable for the read operators
	
	int i = 0, j = 0, ISP, ICP; //declare variable for indices i(for expression) and j(for number string), and for the incoming priority(ICP) and in-stack priority(ISP)
	
	//loop this statement until at the end of the string
	while(expression[i] != '\0'){
		//1. Get a token
		//first, determine if the current element of the string is a digit.
		if(isdigit(expression[i])){
			//if so, execute while loop until the element is no longer a number
			while(isdigit(expression[i])){
				number[j] = expression[i]; //add the read number to the number string
				j++; //increment index j to move to the next index of the number string
				i++; ////increment index i to the move to the next index of the expression
			}
			number[j] = '\0'; //after the loop, terminate the string
			//2. if token is operand, goes to output
			enQueueOperand(atoi(number)); //use atoi to convert the number in the string to an integer, and enqueue it in the queue.
			clearString(number); //clear the number string
			j = 0; //reset the number string index count
		}
		else { //if the current token is not a number:
			if(expression[i] != ')') //if the current operator is not ')',
			{
				Operator[0] = expression[i]; //place the first symbol of the operator to the operator char array 
				switch(Operator[0]){ //switch case to determine if the operator has 2 symbols
					//for '<=', '>=', '!='
					case '<':
					case '>':
					case '!':
						//check the next element of expression to determine if the operator has '='
						if(expression[i + 1] == '=')
							Operator[1] = '='; //if it does, set 2nd element of operator to '='
						else
							Operator[1] = '\0'; //otherwise. terminate the string
						break;
					//for '=='
					case '=':
						Operator[1] = '='; //set the next element to '='
						break;
					//for '&&'
					case '&':
						Operator[1] = '&'; //set the next element to '&'
						break;
					//for '||'
					case '|':
						Operator[1] = '|'; //set the next element to '|'
						break;
					//else, terminate the string
					default:
						Operator[1] = '\0';
				}
				//if the string has not yet been terminated, terminate it and increment i to ignore the next symbol
				if(Operator[1] != '\0'){
					Operator[2] = '\0';
					i++;
				}
				//3. if token is operator or '(':
				do {
					ICP = getPriority(Operator, 1); //get the ICP of the operator in the expression
					//if the stack is empty, set ISP to 0
					if(OptisEmpty(pTop))
						ISP = 0;
					else //otherwise, get the current ISP of the top of the stack
						ISP = getPriority(pTop->Operator, 0);
						
					//	a. If ICP > ISP, push. go back to step 1	
					if(ICP > ISP){
						PushOperator(&pTop, Operator); //push the operator and set that as the top of the stack
						clearString(Operator); //after pushing, clear the operator string,
					}//  b. else, pop top of stack. go back to step 3a.
					else {
						enQueueOperator(pTop->Operator); //place the operator in the queue
						PopOperator(&pTop); //pop the top of the stack
					}
				} while(ICP <= ISP); //loop until ICP is greater than ISP
			}
			//4. If token is ')'
			else {
				do {
					enQueueOperator(pTop->Operator); //place the operator in the queue
					PopOperator(&pTop); //	a. pop top of stack
				//	b. if current top is not correspoding '(', pop operator to output. go back to 4a.
				} while(strcmp(pTop->Operator, "(") != 0);  //loop until the top node contains '('
				//	c. else, discard both parenthesis, and go back to step 1.
				PopOperator(&pTop); //pop the top to discard '('
			}
			i++; //increment to move to the next token
		}
	}
	//5. if no more tokens, pop all elements
	//execute this until the stack is empty 
	while(!OptisEmpty(pTop)) {
		enQueueOperator(pTop->Operator); //enqueue all elements in the stack
		PopOperator(&pTop); //pop all elements in the stack
	}
}

	/*
	OPERATOR	ICP		ISP
	(			11		0
	!			10		9
	^			8		7
	*, /, %		6		6
	+, -		5		5
	>,>=,<,<=	4		4
	==,!=		3		3
	&&			2		2
	||			1		1 */
/*
	determines and returns the priority value of the given operator. 
	@param Operator - string/char array that contains the given operator
	@param mode - determines if function should look for ICP or ISP. 
				- 1 = get ICP, 0 = get ISP.
*/
int getPriority(char Operator[3], int mode){
	char First = Operator[0]; //declare the first symbol of the operator
	switch(First){ //switch case to determine the ICP/ISP
		case '(': //for '('
			if(mode) //for ICP, ICP = 11
				return 11;
			else //for ISP, ISP = 0
				return 0;
		case '!': //for '!'
			if(Operator[1] == '=') //if this is the relational operator '!=', priority = 3
				return 3;
			else { //if this is the unary logical operator '!'
				if(mode) //for ICP, ICP = 10
					return 10;
				else //for ISP, ISP = 9
					return 9;
			}
		case '^': //for '^'
			if(mode) //for ICP, ICP = 8
				return 8;
			else //for ISP, ISP = 7
				return 7;
		//for '*', '/', and '%', priority is 6
		case '*':
		case '/':
		case '%':
			return 6;
		//for '+' and '-', priority is 5
		case '+':
		case '-':
			return 5;
		//for '<' and '>', priority is 4
		case '>':
		case '<':
			return 4;
		//for '==', priority is 3
		case '=':
			return 3;
		//for '&&', priority is 2
		case '&':
			return 2;
		//for '||', priority is 1
		case '|':
			return 1;
	}
	//return -1 if given operator is not an operator
	return -1;
}
