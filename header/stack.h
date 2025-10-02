#ifndef STACK_H_
#define STACK_H_

#include "stddef.h"

typedef double stack_type;

struct stack_t
{
    int struct_kanareyka;
    double* data;
    size_t size;
    size_t capacity;
    int struct_kanareyka_right; 

    //
};

void stack_init(stack_t* stk, size_t capacity_i);

void stack_push(stack_t* stk, stack_type element);

stack_type stack_pop(stack_t* stk);

void stack_destroy(stack_t* stk);

void stack_dump(stack_t* stk, int err, const int line , const char* file);

void stack_verify(stack_t* stk, const int line, const char* file);

#endif