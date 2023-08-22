#include <stdlib.h>
#include <stdio.h>
#include "refcount.h"
#include "stack.h"


int main(int argc, char **arvc) {
    struct stack_element *first = push(1357);
    // struct stack_element *first = push(1357, malloc(sizeof(struct stack_element)));
    rc_keep_ref(first);
    pop();

    push(2468);
    // push(2468, malloc(sizeof()));
    int second = pop();

    //first is still pointing, but the element is freed.

    printf("%d %d\n", get_value(first), second);
    rc_free_ref(firt);
}
