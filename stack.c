#include "stack.h"

#include <assert.h>
#include <stdlib.h>

typedef struct node NODE;

struct stack {
  NODE *top;
};

struct node {
  int value;
  NODE *next;
};

STACK *stack_create(void) {
  STACK *stack = (STACK *)malloc(sizeof(STACK));
  assert(stack != NULL);

  stack->top = NULL;

  return stack;
}

void stack_destroy(STACK *stack) {
  for (NODE *node = stack->top; node != NULL;) {
    NODE *tmp = node->next;
    free(node);
    node = tmp;
  }
  free(stack);
}

bool stack_isEmpty(const STACK *stack) { return stack->top == NULL; }

int stack_top(const STACK *stack) {
  assert(!stack_isEmpty(stack));
  return stack->top->value;
}

void stack_push(STACK *stack, int element) {
  NODE *tmp = stack->top;

  stack->top = (NODE *)malloc(sizeof(NODE));
  assert(stack->top);

  stack->top->value = element;
  stack->top->next = tmp;
}

void stack_pop(STACK *stack) {
  assert(!stack_isEmpty(stack));

  NODE *tmp = stack->top->next;
  free(stack->top);
  stack->top = tmp;
}
