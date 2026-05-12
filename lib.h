#include "stack.h"
// IntStack function prototypes
void createStack(struct Stack *stack, int capacity);
void destroyStack(struct Stack *stack);
void push(struct Stack *stack, float item);
float pop(struct Stack *stack, float *item);
void printStack(struct Stack *stack);

// CharStack function prototypes
void createCharStack(struct CharStack *stack, int capacity);
void destroyCharStack(struct CharStack *stack);
void pushChar(struct CharStack *stack, char item);
int popChar(struct CharStack *stack, char *item);
void printCharStack(struct CharStack *stack);

// give op's precedence
int precedence(char op);

// calculate n2 op n1 and push result back to stack
void calculate(struct Stack *stack, char op);

// adding number to stack and resetting number and flag
void addNumberToStack(struct Stack *stack, int *is_number_in_progress, float *number, int *sign,int *expect_unary);

// pop operator from charStack, calculate and print the popped operator
void calcAndPopChar(struct Stack *stack, struct CharStack *charStack);