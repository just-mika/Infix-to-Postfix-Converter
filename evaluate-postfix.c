#include <stdio.h>
#include "queue.h"
#include "header.h"
#include <math.h>

/*
    evaluates the operation based on given operator and returns result
    @param opt[]    - operator that will determine the type of operation to solve
    @param opr1    - left-hand operand or base
    @param opr2    - right-hand operand, or exponent
    @return results depending on the operation made
*/
int solve(char opt[], int opr1, int opr2){
    switch(opt[0]){
        //arithmetic
        case '+':
            return opr1 + opr2;
        case '-':
            return opr1 - opr2;
        case '*':
            return opr1 * opr2;
        case '/':
            return opr1/opr2;
        case '%':
            return opr1/opr2;
        case '^':
            return pow(opr1, opr2);
        //relational
        case '>':
            if(opt[1] == '='){
                if(opr1>opr2 || opr1==opr2){
                    return 1;
                }
                return 0;
            }else{
                if(opr1>opr2){
                    return 1;
                }
                return 0;
            }
        case '<':
            if(opt[1] == '='){
                if(opr1<opr2 || opr1==opr2){
                    return 1;
                }
                return 0;
            }else{
                if(opr1<opr2){
                    return 1;
                }
                return 0;
            }
        case '=':
            if(opr1==opr2){
                return 1;
            }
            return 0;
        //logical
        case '!':
            if(opr1!=opr2){
                return 1;
            }
            return 0;
        case '&':
            if(opr1 != 0 && opr2 != 0){
                return 1;
            }
            return 0;
        case '|':
            if(opr1 == 1 || opr2 == 1){
                return 1;
            }
            return 0;
    }
    return 0;
}

/*
    evaluate postfix until queue is empty, then prints the result or the error message in cases of division by zero
    @param *pFront - queue to be evaluated
*/
void evaluatePostFix(PostFixQ* pFront){
    OprNode* pTop = InitializeOpr();
    int opr1, opr2, result;
    int finalResult;
    int isValid = 1; //remains one if there is no division by zero
    while(!QisEmpty(pFront)){
        result = 0;
        opr1 = 0;
        opr2 = 0;
        if(pFront->dataType == OPERAND){
            PushOperand(&pTop, pFront->operand);
        }else{
            //for unary operators, specifically NOT, pop once
            if(strcmp(pFront->operator, "!") ==0){
                opr1 = OprTop(pTop);
                result = !opr1; //evaluates pTop
                PopOperand(&pTop);
                PushOperand(&pTop, result);
            }
            else{
                //other operators, pop twice
                opr2 = OprTop(pTop);
                PopOperand(&pTop);
                opr1 = OprTop(pTop);
                PopOperand(&pTop);
                //checks if there is division of 0
                if(strcmp(pFront->operator,"/") == 0 || strcmp(pFront->operator,"%") == 0){
                    if(opr2 == 0){
                        printf("Division by zero error!\n");
                        return;
                    }
                }
                result = solve(pFront->operator, opr1, opr2);
                PushOperand(&pTop, result);
            }
        }
        deQueue(&pFront);
    }
    if(isValid == 1){ //for valid equations -- equations without division of 0
        finalResult = OprTop(pTop);
        printf("%d\n", finalResult);
    }
}
