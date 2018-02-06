#include "defs.h"

void preProcess(char* s);
int checkPrecedence(char a, char b);
bool checkAssociation(char a, char b);
const char* charToString(char a);
bool isSpecialNumber(char ch);
bool isDigit(char ch);
bool isOperator(char ch);

DECLARE_STACK(char)

int convertToRPN(char* infix, char* result, int buffer_size)
{
    char ch = 0;
    char postfix[buffer_size];
    memset(postfix , 0 , sizeof(postfix));
    Stack_char* stack0 = NULL;
    stack0 = new_Stack_char(stack0);
    preProcess(infix);
    for(int i = 0; infix[i] != 0; i++){
        ch = infix[i];
        if(isOperator(ch)){ //if symbol is an operator
            if(i == 0 || isOperator(infix[i-1]) || infix[i - 1] == '('){
                if(ch == '-' || ch == '+'){
                    strcat(postfix, charToString(ch));
                    continue;
                }
	        }
            if(!stackIsEmpty_char(stack0) && *stackTop_char(stack0)!= '(')
            {
                if(checkPrecedence(ch, *stackTop_char(stack0)) == 1){
                    stackPush_char(stack0, ch);
                }
                else if(checkPrecedence(ch, *stackTop_char(stack0)) == 0){
                    if(!checkAssociation(ch, *stackTop_char(stack0)))
                        strcat(postfix, charToString(*stackPop_char(stack0)));
                    stackPush_char(stack0, ch);
                }
                else if(checkPrecedence(ch, *stackTop_char(stack0)) == -1){
                        strcat(postfix, charToString(*stackPop_char(stack0)));
                        --i;
                }
                else if(checkPrecedence(ch, *stackTop_char(stack0)) == 2){
                    stackPush_char(stack0, ch);
                }
            }
            else if(stackIsEmpty_char(stack0) || *stackTop_char(stack0) == '('){//If stack is empty, push operator to stack
                    stackPush_char(stack0, ch);
            }
            strcat(postfix, " ");
        }
        else if(ch == '('){
                    stackPush_char(stack0, ch);
        }
        else if(ch == ')'){
                while(*stackTop_char(stack0) != '(')
                    strcat(postfix, charToString(*stackPop_char(stack0)));
                stackPop_char(stack0);
            }
        else if(isDigit(ch) || isSpecialNumber(ch)){
            //if symbol is an operand - print
            strcat(postfix, charToString(ch));
        }
        else if(ch !=16){
            destroy_Stack_char(stack0);
            return -1;
        }
    }
    //Pop Stack and print
    while(!stackIsEmpty_char(stack0))
        strcat(postfix, charToString(*stackPop_char(stack0)));
    strncpy(result, postfix, buffer_size-1);
    destroy_Stack_char(stack0);
    return 0;
}

void preProcess(char* s){
    int n;
    for(n = 0; s[n] != 0; ++n);
    for(int i = 0; i<n; i++){
        if(s[i] == 'c'){
           if(i+1 < n && i+2 < n && s[i+1] == 'o' && s[i+2] == 's')
                for(int j = i+1; j < n-1; j++)
                    s[j] = s[j+2];
        }
    }
    for(n = 0; s[n] != 0; ++n);
        for(int i = 0; i<n; i++){
            if(s[i] == 'p'){
               if(i+1 <= n && s[i+1] == 'i')
                    for(int j = i+1; j < n; j++)
                        s[j] = s[j+1];
            }
        }
    for(n = 0; s[n] != 0; ++n);
    for(int i = 0; i<n; i++){
        if(s[i] == 's'){
           if(i+2 < n && s[i+1] == 'i' && s[i+2] == 'n')
                for(int j = i+1; j < n-1; j++)
                    s[j] = s[j+2];
        }
    }
    for(n = 0; s[n] != 0; ++n);
    for(int i = 0; i<n; i++){
        if(s[i] == 't'){
           if(i+1 < n && i+2 < n && s[i+1] == 'a' && s[i+2] == 'n')
                for(int j = i+1; j < n-1; j++)
                    s[j] = s[j+2];
        }
    }
    for(n = 0; s[n] != 0; ++n);
    for(int i = 0; i<n; i++){
        if(s[i] == 'a'){
           if(i+1 < n && i+2 < n && s[i+1] == 'b' && s[i+2] == 's')
                for(int j = i+1; j < n-1; j++)
                    s[j] = s[j+2];
        }
    }
}

bool isDigit(char ch){
    if(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5'
        || ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '.')
        return true;
    else
        return false;
}

bool isOperator(char ch){
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/'
    || ch == '^' || ch == 's' || ch == 'c' || ch == 't' || ch == 'a')
        return true;
    else
        return false;
}

bool isSpecialNumber(char ch){
    if(ch == 'p' || ch == 'e')
        return true;
    else
        return false;
}

const char* charToString(char a)
{
    static char buff[2];
    buff[0] = a;
    buff[1] = '\0';
    return buff;
}

bool checkAssociation(char a, char b)
{
    if(b == '^')
        return true;
    else
        return false;
}

int checkPrecedence(char a, char b)
{
    int comp1 = 0, comp2 = 0;

    if(a == b)
        return 2;
    if(a == '+' || a == '-')
        comp1 = 0;
    else if(a == '*' || a == '/' )
        comp1 = 1;
    else if(a == '^' )
        comp1 = 2;
    else if( a == 's' || a == 'c' || a == 't' || a == 'a')
        comp1 = 3;

    if(b == '+' || b == '-')
        comp2 = 0;
    else if(b == '*' || b == '/' )
        comp2 = 1;
    else if(b == '^' )
        comp2 = 2;
    else if( b == 's' || b == 'c' || b == 't' || b == 'a')
        comp2 = 3;

    if(comp1 == comp2)
        return 0;
    else if(comp1 > comp2)
        return 1;
    else if(comp1 < comp2)
        return -1;

    else{
        fprintf(stderr, "Error while parsing!\n");
        exit(1);
    }
}
