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
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->elements = (PElement *)malloc(sizeof(PElement) * arr->capacity);
    if (arr->elements == NULL)
    {
        red();
        printf("Error: malloc failed\n");
        reset();
        free(arr);
        return NULL;
    }
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
    int size = GetAdptArraySize(arr);
    DEL_FUNC del = arr->del_func;
    for (int i = 0; i < size; i++)
    {
        PElement value = GetAdptArrayAt(arr, i);
        if (value != NULL)
        {
            del(value);
        }
        else
            continue;
    }
    free(arr->elements);
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
    if (index >= arr->capacity)
    {
        int new_capacity = arr->capacity * 2;
        PElement *newElements = (PElement *)realloc(arr->elements, new_capacity * sizeof(PElement));
        if (newElements == NULL)
        {
            red();
            printf("Error: realloc failed\n");
            reset();
            return FAIL;
        }
        arr->capacity = new_capacity;
        arr->elements = newElements;
    }
    if (index >= arr->size)
    {
        arr->size = index + 1;
    }
    PElement newElement = arr->copy_func(element);
    if (newElement == NULL)
    {
        red();
        printf("Error: copy func is null\n");
        reset();
        return FAIL;
    }
    if (arr->elements[index] != NULL && arr->del_func != NULL)
    {
        arr->del_func(arr->elements[index]);
    }
    arr->elements[index] = newElement;
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
    blue();
    return arr->elements[index];
    reset();
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
    int size = GetAdptArraySize(arr);
    for (int i = 0; i < size; i++)
    {
        PElement value = GetAdptArrayAt(arr, i);
        if (value == NULL)
        {
            red();
            printf("NULL pointer at the index: %d\n", i);
            reset();
            continue;
        }
        yellow();
        printf("At index %d -> ", i);
        arr->print_func(value);
        reset();
        printf("\n");
    }
}