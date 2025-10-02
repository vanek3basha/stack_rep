#include "header/stack.h"
#include "stdlib.h"
#include "stdio.h"
#include <math.h>
#define FOO(arg) printf(arg, __LINE__, __FILE__)

// 1 & 3 = 1

//0b00101101
//&
//0b11101110
//0b00000001
//

//0b00000001
//+
//0b00001000

//0b00001001
//&
//0b00000001
//0b00000001

enum ERRORS = {
    ERR_STK_NULL = 1,
    ERR_CAPASITY_LEN = 2,
    ERR_STK_DATA_NULL = 3,
    ERR_POIZON = 4,
    ERR_KANAR_LEFT_ATTACK = 5,
    ERR_KANAR_RIGHT_ATTACK = 6,
    ERR_KANAR_DATA_LEFT_ATTACK = 7,
    ERR_KANAR_DATA_RIGHT_ATTACK = 8;
}

const int KANAR_LEFT = 1234567890;

const int KANAR_RIGHT = 1234567891;

const stack_type EPS = 10e-6;

const stack_type POISON = 322322322;

const stack_type KANAR_DATA_LEFT = 1234567892;

const stack_type KANAR_DATA_RIGHT = 1234567893;

/********************************************************************************************************************************************************/

void stack_init(stack_t* stk, size_t capacity_i)
{
    if (stk == NULL)
    {
        int err = ERR_STK_NULL;
        
        stack_dump(stk, err, __LINE__, __FILE__); 
    } 

    if (capacity_i <= 0)
    {
        int err = ERR_CAPASITY_LEN;
        *
        stack_dump(stk, err, __LINE__, __FILE__);
    }

    stk->data = (stack_type*)calloc(capacity_i, sizeof(stack_type));

    for (size_t i = 0; i < capacity_i; i++)
    {
        stk->data[i] = POISON;
    }

    stk->data[0] = KANAR_DATA_LEFT;

    stk->data[capacity_i] = KANAR_DATA_RIGHT;

    stk->capacity =  capacity_i;

    stk->size = 1;

    stk->struct_kanareyka = KANAR_LEFT;

    stk->struct_kanareyka_right = KANAR_RIGHT;

    stack_verify(stk, __LINE__, __FILE__);

    return;
}

/*******************************************************************************************************************************************************/

void stack_push(stack_t* stk, double element)
{
    stack_verify(stk, __LINE__, __FILE__);
    
    stk->size = stk->size + 1;

    if (stk->size >= stk->capacity)
    {
        stack_realloc(stk, stk->capacity * 2);
    }


    stk->data[stk->size] = element;

    stack_verify(stk, __LINE__, __FILE__);
    
    return;
}

/*******************************************************************************************************************************************************/

stack_type stack_pop(stack_t* stk)
{
    err = stack_verify(stk, __LINE__, __FILE__);
    
    stack_type element = stk->data[stk->size];
    
    stk->size = stk->size - 1;

    err = stack_verify(stk, __LINE__, __FILE__);

    return element;
}

/******************************************************************************************************************************************************/

void stack_destroy(stack_t* stk)
{
    err = stack_verify(stk, __LINE__, __FILE__);
    
    free(stk->data);     
    
    stk -> capacity  = 0;
    
    stk -> size = 0;

    stk -> data = NULL;

    return err;
}

/*****************************************************************************************************************************************************/

void stack_dump(stack_t* stk, int err, const int line, const char* file)
{
    FILE *err_file;
    
    err_file = fopen("err_file.txt", "a+");
    
    fprintf(err_file, "FILE: %s\n", file);

    fprintf(err_file, "LINE: %d\n", line);

    fprintf(err_file, "ERROR_NUMBER: %d\n", err);



    fprintf(err_file, "/************************************************************************************/\n");

    fclose(err_file);
    
    return; 
}

/****************************************************************************************************************************************************/

int stack_verify(stack_t* stk, const int line, const char* file)
{
    if (stk == NULL)
    {
        //enum
        int err = ERR_STK_NULL;
        stack_dump(stk, err, line, file);
    }

    if (stk->capacity <= 0)
    {
        int err = ERR_CAPASITY_LEN;
        stack_dump(stk, err, line, file);
    }

    // if (stk->size < 0)
    // {
    //     int err = 3;
    //     stack_dump(stk, err, line, file);
    // }

    if (stk->data == NULL)
    {
        int err = ERR_STK_DATA_NULL;
        stack_dump(stk, err, line, file);
    }

    if (stk->struct_kanareyka != KANAR_LEFT)
    {
        err = ERR_KANAR_LEFT_ATTACK;

        stack_dump(stk, err, line, file);
    }

    if (stk->struct_kanareyka_right != KANAR_RIGHT)
    {
        err = ERR_KANAR_RIGHT_ATTACK;

        stack_dump(stk, err, line, file);
    }

    if (stk->data[0] != KANAR_DATA_LEFT)
    {
        err = ERR_KANAR_DATA_LEFT_ATTACK;

        stack_dump(stk, err, line, file);
    }

    if (stk->data[stk->capacity] != KANAR_DATA_RIGHT)
    {
        err = ERR_KANAR_DATA_RIGHT_ATTACK;

        stack_dump(stk, err, line, file);
    }


    for (size_t i = stk->size; i < stk->capacity; i++)
    {
        if ( fabs(stk->data[i] - POISON) < EPS )
        {
            int err = ERR_POIZON;
            
            stack_dump(stk, err, line, file);

            break;
        }
        
    } 
    return err;
}

/********************************************************************************************************************************************************/

int stack_realloc(stack_t* stk, size_t new_capasity)
{
    stack_type* zapas_data = (stack_type*)realloc(stk->data, new_capasity * sizeof(stack_type));
    
    if (zapas_data != NULL)
    {
        stk->data = zapas_data;
    }

    stk->data[stk->capacity] = POISON;

    stk->data[new_capasity] = KANAR_DATA_RIGHT;
    
    stk->capacity = new_capasity;
        
    return stack_verify(stk, __LINE__, __FILE__);
}