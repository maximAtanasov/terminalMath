#include <stdio.h>
#include <stdlib.h>

//A Generic implentation of a stack using macros
//Written by Maxim Atanasoff

//Example Usage:
//
//DECLARE_STACK(int) //just replace int with your type
//Stack_int* stack = new_Stack_int(stack);
//stackPush_int(stack, 5);
//printf("%d\n", stackTop_int(stack);

#define DECLARE_STACK(TYPE)\
\
    void print_##TYPE(TYPE* a);\
    void print_##TYPE(TYPE* a);\
\
    typedef struct Stack_##TYPE\
    {                           \
        unsigned int position;  \
        size_t size;       \
        TYPE* stackArr;    \
    } Stack_##TYPE;             \
                                \
    Stack_##TYPE* new_Stack_##TYPE(Stack_##TYPE* this){\
        this = malloc(sizeof(Stack_##TYPE));\
        this->position = 0;\
        this->size = 20;\
        this->stackArr = malloc((this->size)*sizeof(TYPE));\
        return this;\
    }\
\
    void stackPush_##TYPE(Stack_##TYPE* this, TYPE k){\
        if(this->position > this->size - 1){\
            this->stackArr = realloc(this->stackArr, ((this->size + this->size/2)*sizeof( TYPE )));\
            this->size += this->size/2;\
        } \
        this->stackArr[this->position++] = k; \
    }\
    \
    int stackIsEmpty_##TYPE(Stack_##TYPE* this)\
    {\
        if(this->position == 0)\
            return 1;\
        else \
            return 0;\
    }\
    TYPE* stackPop_##TYPE(Stack_##TYPE *this)\
    {\
        if(!stackIsEmpty_##TYPE(this)){\
            TYPE* data = &this->stackArr[--this->position];\
            return data;\
        }\
        else\
            return NULL;\
    }\
    \
    TYPE* stackTop_##TYPE(Stack_##TYPE *this)\
    {\
        if(!stackIsEmpty_##TYPE(this)){\
            TYPE* data = &this->stackArr[this->position - 1];\
            return data;\
        }\
        else\
            return NULL;\
    }\
    void print_Stack_##TYPE(Stack_##TYPE* this){\
        TYPE* temp = this->stackArr;\
        int i;\
        for(i = 0; i <= this->position - 1; i++)\
            print_##TYPE(temp++);\
    }\
    void destroy_Stack_##TYPE(Stack_##TYPE* this){\
        free(this->stackArr);\
        free(this);\
    }\
\
\
//
