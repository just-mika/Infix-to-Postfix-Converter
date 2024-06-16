#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "header.h"
#include <math.h>

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
}

int evaluatePostFix(PostFixQ* pFront){
    OprNode* pTop = InitializeOpr();
    int opr1, opr2, result;
    int finalResult;
    while(!QisEmpty(pFront)){
        result = 0;
        opr1 = 0;
        opr2 = 0;
        if(pFront->dataType == OPERAND){
            PushOperand(&pTop, pFront->operand);
        }else{
            if(strcmp(pFront->operator, "!") ==0){
                opr1 = OprTop(pTop);
                result = !opr1; //evaluates pTop
                PopOperand(&pTop);
                PushOperand(&pTop, result);
            }
            else{
                opr2 = OprTop(pTop);
                PopOperand(&pTop);
                opr1 = OprTop(pTop);
                PopOperand(&pTop);
                if(strcmp(pFront->operator,"/") == 0){
                    if(opr2 == 0){
                        printf("Division by zero error!");
                        return 0;
                    }
                }
                result = solve(pFront->operator, opr1, opr2);
                PushOperand(&pTop, result);
            }
        }
        deQueue(&pFront);
    }
    finalResult = OprTop(pTop);
    return finalResult;
}
