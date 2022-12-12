#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

#define HALF 2;

/**
 * Removes an element from the Stack
 *
 * @param s Stack struct to remove from
 * @return  the element that was removed
 */

// pop function for stack
Element* pop(Stack* s) {
    // if Stack is empty, return null
    if(isEmpty(s)) {
        return NULL;
    }

    // if shrinkFactor is greater than 0 and shrinkFactor has been reached
    if(s->shrinkFactor > 0 && (float)s->top / (float)s->capacity 
            <= s->shrinkFactor && s->dynamic == true && s->shrinkFactor != 0) {
        // divide capacity in half
        s->capacity = s->capacity / HALF;
        // create a new array of Elements and fill in the array
        Element** newElements = (Element**)malloc(s->capacity * 
                sizeof(Element*));
        for(int i = 0; i < s->capacity; i++) {
            newElements[i] = s->elements[i];
        }
        free(s->elements);
        s->elements = newElements;
    }
    s->top--;
    // return element at the top of the Stack
    return s->elements[s->top];
}

/**
 * Pop k elements from the Stack
 *
 * @param s Stack struct to remove from
 * @param k number of elements to pop
 * @return  array with all the elements that were removed
 */

// multipop: pop multiple elements from stack
Element** multiPop(Stack* s, int k) {
    // if Stack is empty, return null
    if(isEmpty(s)) {
        return NULL;
    }

    // if k is greater than currentSize, set k to currentSize
    if(k > currentSize(s)) {
        k = currentSize(s);
    }

    // create new array and add removed elements
    Element** returnElements = (Element**)malloc(k * sizeof(Element*));
    for(int i = 0; i < k; i++) {
        returnElements[i] = pop(s);
    }
    return returnElements;
}

/**
 * Helper method to add an element
 *
 * @param s Stack struct to add to 
 * @param k key to add 
 * @param v value to add
 */

// Utility function: add element for push
void addE(Stack* s, int k, char* v) {
    // create new element
    Element* newElement = (Element*)malloc(sizeof(Element));

    // set the key and value of the new element
    newElement->key = k;
    newElement->value = v;

    free(s->elements[s->top]);
    // set the element at top to the new element
    s->elements[s->top] = newElement;
}

/**
 * Helper method to expand the Stack array
 *
 * @param s Stack struct to expand
 */

// Utility function: expandCapacity for push
void expandCapacity(Stack* s) {
    // double the capacity
    s->capacity = s->capacity * HALF;

    // create new array with new capacity and copy elements into new array
    Element** newElements = (Element**)malloc(s->capacity * sizeof(Element*));
    for(int i = 0; i < s->top; i++) {
        newElements[i] = s->elements[i];
    }
    free(s->elements);
    // set the element array to the new array
    s->elements = newElements;
}

/**
 * Adds an element into the Stack            
 *
 * @param s Stack struct to add to
 * @param k key to add
 * @param v value to add
 * @return  whether or not a new element was added
 */

// push function for stack
bool push(Stack* s, int k, char* v){
    // if Stack is full, return false
    if(isFull(s) && s->dynamic == false) {
        return false;
    }

    // growthFactor is greater than 0 and growthFactor has been reached
    if(s->growthFactor > 0 && (float)s->top / (float)s->capacity >= s->growthFactor) {
        expandCapacity(s);
    }
    
    // add new element to Stack
    addE(s,k,v);
    s->top++;
    return true;
}

/**
 * Add an element to the top of the Stack only if the current element at the
 * top is not the same as the element to be added
 *
 * @param s Stack struct to add to
 * @param k key to add
 * @param v value to add
 * @return  whether or not a new element was added
 */
// push unique function for stack
bool pushUnique(Stack* s, int k, char* v){
    // if Stack is empty, return false
    if(isFull(s)) {
        return false;
    }

    // if Stack is empty, push new element
    if(isEmpty(s)) {
        push(s,k,v);
        return true;
    }

    // peek the first element in Stack
    Element* peekedElement = peek(s);
    // if the peekedElement is the same as the element to add, return false
    if(peekedElement->key == k && peekedElement->value == v) {
        return false;
    }

    push(s,k,v);
    return true;
}

/**
 * Reverse the elements in the Stack
 *
 * @param s Stack struct to reverse 
 * @return  none
 */

// reverse the elements in stack
void reverse(Stack* s) {
    // reverse the Stack
    for(int i = 0; i < s->top / 2; i++) {
        Element* temp = s->elements[i];
        s->elements[i] = s->elements[s->top - i - 1];
        s->elements[s->top - i - 1] = temp;
    }
}

/** 
 * Returns element at the top of the Stack without removing it 
 *
 * @param s Stack struct to peek 
 * @return  element at the top of the Stack
 */

// peek function for stack
Element* peek(Stack* s) {
    // if Stack is empty, return null
    if(isEmpty(s)) {
        return NULL;
    }
    // return element at the top of the Stack
    return s->elements[s->top - 1];
}

/** 
 * Returns the distance of the element from the top of the Stack
 *
 * @param s Stack struct to search through
 * @param k key to search for 
 * @param v value to search for
 * @return  distance of the element from the top of the Stack, -1 if it
 *          doesn't exist
 */

// search for element from top of stack
int search(Stack* s, int k, char* v) {
    // if Stack is empty, return -1
    if(isEmpty(s)) {
        return -1;
    }

    // search through the Stack backwards for matching element
    for(int i = s->top - 1; i >= 0; i--) {
        if(s->elements[i]->key == k && s->elements[i]->value == v) {
            return s->top - i;
        }
    }
    return -1;
}

/**
 * Getter for capacity of the stack
 *
 * @param s Stack struct to get capacity of 
 * @return  the capacity of the stack
 */

// get current capacity of stack
int getCapacity(Stack* s) {
    return s->capacity;
}

/**
 * Whether or not the stack is full
 *
 * @param s Stack struct to get capacity of 
 * @return  whether or not the stack is full
 */

//check if stack is full
bool isFull(Stack* s){
    return s->capacity == s->top;
}

/**
 * Empty the stack
 *
 * @param s Stack struct to empty
 * @return  none
 */

// clear the stack
void clear(Stack *s) {
    s->top = 0;
}

/**
 * Deallocate unused memory in the Stack
 *
 * @param s Stack struct to deallocate memory
 * @return  none
 */

// clean the stack
void cleanStack(Stack *s) {
  for(int i = 0; i < s->capacity; i++) {
    free(s->elements[i]);
  }
	free(s->elements);
	free(s);
}

/**
 * Current size of the stack
 *
 * @param s Stack struct to check size
 * @return  current size of the Stack
 */

// current size of stack
int currentSize(Stack* s){
    return s->top;
}

/**
 * Check if Stack is empty
 *
 * @param s Stack struct to check if empty
 * @return  whether or not Stack is empty
 */

// check if stack empty
bool isEmpty(Stack* s) {
    return s->top == 0;
}

/**
 * Create a Stack
 *
 * @param cap capacity of Stack
 * @return    Stack that was created
 */

// Stack with fixed capacity
Stack* makeStack(int cap){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = cap;
    stack->top = 0;
    stack->growthFactor = 0;
    stack->shrinkFactor = 0;
    stack->dynamic = false;
    stack->elements = (Element**)malloc(stack->capacity * sizeof(Element*));
    return stack;
}

/**
 * Create a Stack
 *
 * @param cap   capacity of Stack
 * @param growF growth factor of Stack
 * @return      Stack that was created
 */

// Stack that can grow
Stack* makeStackG(int cap, float growF){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = cap;
    stack->growthFactor = growF;
    stack->shrinkFactor = 0;
    stack->top = 0;
    stack->dynamic = true;
    stack->elements = (Element**)malloc(stack->capacity * sizeof(Element*));
    return stack;
}

/**
 * Create a Stack
 *
 * @param cap     capacity of Stack
 * @param growF   growth factor of Stack
 * @param shrinkF shrink factor of Stack
 * @return        Stack that was created
 */

// Stack that can grow and shrink
Stack* makeStackGnS(int cap, float growF, float shrinkF){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = cap;
    stack->growthFactor = growF;
    stack->shrinkFactor = shrinkF;
    stack->top = 0;
    stack->dynamic = true;
    stack->elements = (Element**)malloc(stack->capacity * sizeof(Element*));
    return stack;
}
