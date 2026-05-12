#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "lib.h"
#include "stack.h"
int main()
{
    int capacity = 100;
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    struct CharStack *charStack = (struct CharStack *)malloc(sizeof(struct CharStack));

    if (stack == NULL || charStack == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    createStack(stack, capacity);
    createCharStack(charStack, capacity);

    // user input for infix expression
    /*     char *expression = (char *)malloc(capacity * sizeof(char));
        if (expression == NULL)
        {
            printf("Memory allocation failed\n");
            free(expression);
            expression = NULL;
            exit(1);
        }
        printf("Enter an infix expression: ");
        fgets(expression, capacity, stdin);
        printf("Infix expression: %s\n", expression); */

    char expression[] = "(2 ^ -3) ^ 2";
    printf("Infix expression: %s\n", expression);
    int i = 0;
    float number = 0;
    int is_number_in_progress = 0;
    int sign = 1;         // 1 for positive, -1 for negative
    int expect_unary = 1; // flag to indicate if we are expecting a unary operator, 1: negative sign, 0: subtract operator
    while (expression[i] != '\0')
    {
        if (isdigit(expression[i]))
        {
            printf("Digit: %c\n", expression[i]);
            number = number * 10 + (expression[i] - '0');
            is_number_in_progress = 1;
        }
        else if (isspace(expression[i]))
        {
            addNumberToStack(stack, &is_number_in_progress, &number, &sign, &expect_unary);
        }
        else if (expression[i] == '(')
        {
            pushChar(charStack, expression[i]);
            printf("Pushed operator: %c\n", expression[i]);
        }
        else if (expression[i] == ')')
        {
            addNumberToStack(stack, &is_number_in_progress, &number, &sign, &expect_unary);

            char op;
            while (charStack->top != -1 && charStack->arr[charStack->top] != '(')
            {
                popChar(charStack, &op);
                calculate(stack, op);
                printf("Popped operator: %c\n", op);
            }
            if (charStack->top != -1 && charStack->arr[charStack->top] == '(')
            {
                popChar(charStack, &op); // pop the '('
                printf("Popped operator: %c\n", op);
            }
        }
        else
        {
            addNumberToStack(stack, &is_number_in_progress, &number, &sign, &expect_unary);

            if (expect_unary && expression[i] == '-')
            {
                // handle unary operator
                sign = -1;
                i++;
                continue;
            }

            if (charStack->top == -1)
            {
                // if charStack is empty, push the operator
                pushChar(charStack, expression[i]);
                printf("Pushed operator: %c\n", expression[i]);
            }

            else
            {
                // if charStack is not empty, pop operators with higher or equal precedence and calculate until we find an operator with lower precedence or charStack becomes empty
                while (stack->top != -1 && precedence(expression[i]) <= precedence(charStack->arr[charStack->top]) && expression[i] != '^')
                {
                    calcAndPopChar(stack, charStack);
                }
                pushChar(charStack, expression[i]);
                printf("Pushed operator: %c\n", expression[i]);
            }
            expect_unary = 1; // after processing an operator, we are expecting a unary operator
        }
        i++;
    }
    if (is_number_in_progress)
    {
        push(stack, number);
    }
    while (charStack->top != -1) // required popChar
    {
        calcAndPopChar(stack, charStack);
    }

    printStack(stack);
    printCharStack(charStack);

    destroyStack(stack);
    destroyCharStack(charStack);
    stack = NULL;     // avoid dangling pointer
    charStack = NULL; // avoid dangling pointer

    return 0;
}

// IntStack funtions
void createStack(struct Stack *stack, int capacity)
{
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (float *)malloc(stack->capacity * sizeof(float));
    if (stack->arr == NULL)
    {
        printf("Memory allocation failed\n");
        free(stack);
        stack = NULL;
        exit(1);
    }
}
void destroyStack(struct Stack *stack)
{
    free(stack->arr);
    stack->arr = NULL;
    free(stack);
    stack = NULL;
}
void push(struct Stack *stack, float item)
{
    if (stack->top == stack->capacity - 1)
    {
        float *temp_ptr = (float *)realloc(stack->arr, stack->capacity * 2 * sizeof(float));
        if (temp_ptr == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }
        stack->arr = temp_ptr;
        stack->capacity *= 2;
    }
    stack->arr[++stack->top] = item;
}
float pop(struct Stack *stack, float *item)
{
    if (stack->top == -1)
    {
        printf("Stack is empty\n");
        return 0;
    }
    *item = stack->arr[stack->top];
    stack->top--;
    return 1;
}
void printStack(struct Stack *stack)
{
    if (stack->top == -1)
    {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("%g ", stack->arr[i]);
    }
    printf("\n");
    printf("Stack size: %d\n", stack->top + 1);
}

// CharStack funtions

void createCharStack(struct CharStack *stack, int capacity)
{
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (char *)malloc(stack->capacity * sizeof(char));
    if (stack->arr == NULL)
    {
        printf("Memory allocation failed\n");
        free(stack);
        stack = NULL;
        exit(1);
    }
}

void destroyCharStack(struct CharStack *stack)
{
    free(stack->arr);
    stack->arr = NULL;
    free(stack);
    stack = NULL;
}

void pushChar(struct CharStack *stack, char item)
{
    if (stack->top == stack->capacity - 1)
    {
        char *temp_ptr = (char *)realloc(stack->arr, stack->capacity * 2 * sizeof(char));
        if (temp_ptr == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }
        stack->arr = temp_ptr;
        stack->capacity *= 2;
    }
    stack->arr[++stack->top] = item;
}

int popChar(struct CharStack *stack, char *item)
{
    if (stack->top == -1)
    {
        printf("Stack is empty\n");
        return 0;
    }
    *item = stack->arr[stack->top];
    stack->top--;
    return 1;
}
void printCharStack(struct CharStack *stack)
{
    if (stack->top == -1)
    {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("%c ", stack->arr[i]);
    }
    printf("\n");
    printf("Stack size: %d\n", stack->top + 1);
}

int precedence(char op)
{
    switch (op)
    {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    case '(':
        return 0;
    default:
        break;
    }
    return 0;
}

void calculate(struct Stack *stack, char op)
{
    float n1;
    float n2;
    pop(stack, &n1);
    pop(stack, &n2);
    switch (op)
    {
    case '^':
        push(stack, pow(n2, n1));
        break;
    case '*':
        push(stack, n2 * n1);
        break;
    case '/':
        push(stack, n2 / n1);
        break;
    case '+':
        push(stack, n2 + n1);
        break;
    case '-':
        push(stack, n2 - n1);
        break;
    default:
        break;
    }
}
void addNumberToStack(struct Stack *stack, int *is_number_in_progress, float *number, int *sign, int *expect_unary)
{
    if (*is_number_in_progress)
    {
        // adding number to stack and resetting number and flag
        push(stack, *number * *sign);
        *number = 0;
        *sign = 1; // reset sign to positive after pushing the number
        *is_number_in_progress = 0;
        *expect_unary = 0; // after pushing a number, we are expecting a unary operator
    }
}

void calcAndPopChar(struct Stack *stack, struct CharStack *charStack)
{
    char op;
    popChar(charStack, &op);
    calculate(stack, op);
    printf("Popped operator: %c\n", op);
}