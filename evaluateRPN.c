#include "defs.h"

double Abs(double x);
double calculate(double operand1, double operand2, char operators);
bool isDigit(char ch);
bool isOperator(char ch);

//Math Constants
#define E  2.718281828459
#define PI 3.141592


double evaluateRPN(char* postfix)
{
    DECLARE_STACK(double)
    Stack_double* stack0 = NULL;
    stack0 = new_Stack_double(stack0);

    char buff[strlen(postfix)], ch;
    strcpy(buff, "");
    int k = 0;
    for(int i = 0; postfix[i] != 0; i++){
        ch = postfix[i];
        if(isDigit(ch) || ((ch == '-' || ch == '+') && isDigit(postfix[i+1]))){
            buff[k] = ch;
            buff[++k] = 0;
            if(postfix[i+1] == ' ' || isOperator(postfix[i+1])){
                double temp;
                sscanf(buff, "%lf", &temp);
                stackPush_double(stack0, temp);
                k = 0;
            }
        }
        else if(ch == 'e'){
            stackPush_double(stack0, E);
        }
        else if(ch == 'p'){
            stackPush_double(stack0, PI);
        }
        else if(isOperator(ch)){
            if(ch == 's'){
                if(stackIsEmpty_double(stack0)){
                    destroy_Stack_double(stack0);

                    return NAN;
                }
                double operand1 = *stackPop_double(stack0);
                double temp = sin(operand1);
                stackPush_double(stack0, temp);
            }
            else if(ch == 'c'){
                if(stackIsEmpty_double(stack0)){
                    destroy_Stack_double(stack0);
                    return NAN;
                }
                double operand1 = *stackPop_double(stack0);
                double temp = cos(operand1);
                stackPush_double(stack0, temp);
            }
            else if(ch == 't'){
                if(stackIsEmpty_double(stack0)){
                    destroy_Stack_double(stack0);

                    return NAN;
                }
                double operand1 = *stackPop_double(stack0);
                double temp = tan(operand1);
                stackPush_double(stack0, temp);
            }
            else if(ch == 'a'){
                if(stackIsEmpty_double(stack0)){
                    destroy_Stack_double(stack0);
                    return NAN;
                }
                double operand1 = *stackPop_double(stack0);
                double temp = Abs(operand1);
                stackPush_double(stack0, temp);
            }
            else {
                double operand1, operand2;
                if(!stackIsEmpty_double(stack0))
                    operand2 = *stackPop_double(stack0);
                else{
                    destroy_Stack_double(stack0);
                    return NAN;
                }
                if(!stackIsEmpty_double(stack0))
                    operand1 = *stackPop_double(stack0);
                else{
                    destroy_Stack_double(stack0);
                    return NAN;
                }
                double temp = calculate(operand2, operand1, ch);
                stackPush_double(stack0, temp);
            }
       }
    }
    if(stackIsEmpty_double(stack0)){
        destroy_Stack_double(stack0);
        return NAN;
    }
    double temp = *stackTop_double(stack0);
    destroy_Stack_double(stack0);
    return temp;
}

double Abs(double x)
{
    if(x < 0)
        return -x;
    return x;
}

double calculate(double operand2, double operand1, char operators)
{
    if(operators == '+')
        return operand1 + operand2;
    else if(operators == '-')
        return operand1 - operand2;
    else if(operators == '*')
        return operand1*operand2;
    else if(operators == '/')
        return operand1/operand2;
    else if(operators == '^')
        return pow(operand1, operand2);
    else{
        fprintf(stderr, "Error while parsing! Exiting...\n");
        exit(1);
    }
}
