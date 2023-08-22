#include <stdlib.h>
#include <stdio.h>
#include "refcount.h"
#include "stack.h"

struct stack_element {
    int val;
    struct stack_element *next;
} *head = 0;

struct stack_element *push(int val) {
    struct stack_element *e = malloc(sizeof(*e));
    e->val = val;
    e->next = head;
    head = e;
    return e;
}

int pop() {
    if (head) {
        int val = head->val;
        struct stack_element* old_head = head;
        //free(old_head);
        //dangling pointer
        head = head->next;
        free(old_head);
        return val;
    } else
        return -1;
}

int get_value(struct stack_element* e) {
    return e->val;
}