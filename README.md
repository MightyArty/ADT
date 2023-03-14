# General Adaptive Array

> An adaptive array is an array that changes its size so that any reference to a negative index is valid.

> When you refer to an index where no value has been placed then `NULL` is returned

## ADT functions definition:

- </b>`CreateAdptArray()` Creates and allocates memory for the structure array
- </b>`DeleteAdptArray()` Frees the memory allocated by the array, including the element array and any elements that were copied into it
- </b>`SetAdptArrayAt()` Saves a copy of the given element in the given index of the array and frees the old element if exist
- </b>`GetAdptArrayAt()` Returns a copy of the element in the given index of an array
- </b>`GetAdptArraySize()` Returns the size of the given array
- </b>`PrintDB()` Prints to the console all the elements from the given array

## Running the program:

```bash
# Clone the repository
# Open the rerminal
$ Run "make demo"
$ Run "make run"
# For memory leaks
$ Run "make mem_test"
```
