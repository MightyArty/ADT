#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>

/*
The following functions are just for colorizing the text
So, when you will run the code, your terminal would not look to dark :)
*/
void red()
{
    printf("\033[1;31m");
}
void yellow()
{
    printf("\033[1;33m");
}
void blue()
{
    printf("\033[1;34m");
}
void green()
{
    printf("\033[1;32m");
}
void reset()
{
    printf("\033[0m");
}

// --------------------------------------THE CODE START'S HERE--------------------------------------

#define INITIAL_CAPACITY 10
#define FACTOR 2

typedef struct AdptArray_
{
    PElement *elements;
    int size;
    int capacity;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
} AdptArray;

/**
 * @brief Creates and allocates memory for the structure array
 * and initialize its fields with null values
 * @param copy_func
 * @param del_func
 * @param print_func
 * @return PAdptArray
 */
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func)
{
    PAdptArray arr = (PAdptArray)malloc(sizeof(AdptArray));
    if (arr == NULL)
    {
        red();
        printf("Error: MALLOC failed\n");
        reset();
        return NULL;
    }
    arr->elements = malloc(sizeof(PElement) * INITIAL_CAPACITY);
    if (arr->elements == NULL)
    {
        red();
        printf("Error: the array is NULL\n");
        reset();
        free(arr);
        return NULL;
    }
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->del_func = del_func;
    arr->copy_func = copy_func;
    arr->print_func = print_func;
    return arr;
}

/**
 * @brief Frees the memory allocated by the array, including the element array and any elements
 * that were copied into it
 * @param arr
 */
void DeleteAdptArray(PAdptArray arr)
{
    if (arr == NULL)
    {
        red();
        printf("Error: arr is null\n");
        reset();
        return;
    }
    if (arr->elements != NULL)
    {
        for (int i = 0; i < arr->capacity; i++)
        {
            if (arr->elements[i] != NULL)
            {
                arr->del_func(arr->elements[i]);
            }
        }
        free(arr->elements);
    }
    free(arr);
}

/**
 * @brief Saves a copy of the given element in the given index of the array
 * And frees the old element if exist
 * @param arr
 * @param index
 * @param element
 * @return Result
 */
Result SetAdptArrayAt(PAdptArray arr, int index, PElement element)
{
    if (arr == NULL || index < 0)
    {
        red();
        printf("Error: the array is null or the index is negative\n");
        reset();
        return FAIL;
    }
    if (index >= arr->size)
    {
        int new_capacity = arr->capacity * 2;
        PElement *newElements = (PElement *)realloc(arr->elements, new_capacity * sizeof(PElement));
        if (newElements == NULL)
        {
            red();
            printf("Error: realloc failed\n");
            reset();
            free(arr);
            return FAIL;
        }
        arr->elements = newElements;
        for (int i = arr->size; i < new_capacity; i++)
        {
            arr->elements[i] = NULL;
        }
        arr->capacity = new_capacity;
        arr->size = index + 1;
    }
    arr->elements[index] = arr->copy_func(element);
    return SUCCESS;
}

/**
 * @brief Returns a copy of the element in the given index of an array
 *
 * @param arr
 * @param index
 * @return PElement
 */
PElement GetAdptArrayAt(PAdptArray arr, int index)
{
    if (index < 0 || index >= arr->size || arr == NULL)
    {
        red();
        printf("Error: arr is null or index is negative or the index is greater then arr->size\n");
        reset();
        return NULL;
    }

    if (arr->elements[index] != NULL)
    {
        blue();
        return arr->copy_func(arr->elements[index]);
        reset();
    }
    else
    {
        green();
        printf("Error: the element in the given index is NULL so can't return his copy\n");
        reset();
        return NULL;
    }
}

/**
 * @brief Returns the size of the given array
 *
 * @param arr
 * @return int
 */
int GetAdptArraySize(PAdptArray arr)
{
    if (arr == NULL)
    {
        red();
        return 0;
        reset();
    }
    green();
    return arr->size;
    reset();
}

/**
 * @brief Prints to the console all the elements from the given array
 *
 * @param arr
 */
void PrintDB(PAdptArray arr)
{
    if (arr == NULL)
    {
        red();
        printf("Error: arr is null\n");
        reset();
        return;
    }
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->elements[i] == NULL)
        {
            red();
            printf("NULL pointer at the index: %d\n", i);
            reset();
            continue;
        }
        yellow();
        printf("At index %d -> ", i);
        arr->print_func(arr->elements[i]);
        reset();
        printf("\n");
    }
}