Author: Julian Yan  
Date: 5/15/2019  
Title: Stack in C  
Summary: This program implements a stack in C.

Contents: 
* stack.c
  * This file implements a stack in C.
    * Element* pop(Stack* s)
    * Element** multiPop(Stack* s, int k)
    * void addE(Stack* s, int k, char* v) 
    * void expandCapacity(Stack* s)
    * bool push(Stack* s, int k, char* v)
    * bool pushUnique(Stack* s, int k, char* v)
    * void reverse(Stack* s)
    * Element* peek(Stack* s)
    * int search(Stack* s, int k, char* v)
    * int getCapacity(Stack* s)
    * bool isFull(Stack* s)
    * void clear(Stack *s)
    * void cleanStack(Stack *s)
    * int currentSize(Stack* s)
    * bool isEmpty(Stack* s)
    * Stack* makeStack(int cap)
    * Stack* makeStackG(int cap, float growF)
    * Stack* makeStackGnS(int cap, float growF, float shrinkF)
* stack.h
  * This file contains the header file for stack.c.
* test_stack.c
  * This file contains test cases for the stack. 