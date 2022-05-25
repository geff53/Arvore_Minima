#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct stack STACK;

STACK *stack_create(void);

void stack_destroy(STACK *stack);

bool stack_isEmpty(const STACK *stack);

int stack_top(const STACK *stack);

void stack_push(STACK *stack, int element);

void stack_pop(STACK *stack);

#endif // STACK_H
