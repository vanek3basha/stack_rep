#include <stdio.h>

#include "header/stack.h"


int main()
{
    // int err = 0;

    size_t capacity_i = 0;

    scanf("%zu", &capacity_i);
    
    stack_t stk1 = {};
    
    stack_init(&stk1, capacity_i);

    //size = 5

    //stk->data[7] = 619
    //

    // printf("%d\n", stk1.capacity);
    
    stack_push(&stk1, 10);

    stack_type last_element_stack = stack_pop(&stk1);

    printf("%g\n", last_element_stack);

    // stack_dump(&stk1, err, __LINE__, __FILE__);

    stack_destroy(&stk1);

}
