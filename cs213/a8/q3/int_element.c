#include "int_element.h"
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
// #include "refcount.h"

/* TODO: Implement all public int_element functions, including element interface functions.

You may add your own private functions here too. */

struct int_element {
    struct element_class *class;
    int val;
};

static void int_element_print(struct element *e) {
    struct int_element *obj = (struct int_element *)e;
    printf("%d", obj->val);
}

static int int_element_compare(struct element* e1, struct element* e2) {
    // if (is_int_element(e1) && is_int_element(e2)) {
    //     return int_element_get_value(e1) - int_element_get_value(e2);
    // }
    //return 1; //stub lol
    if (is_int_element(e2)) {
        int var1 = ((struct int_element *)e1)->val;
        int var2 = ((struct int_element *)e2)->val;

        if (var1 < var2) { return -1; }
        else if (var1 == var2) { return 0; }
        return 1;
    }else { return -1; }
}

static struct element_class int_element_class = {int_element_print, int_element_compare};

struct int_element* int_element_new(int value) {
    struct int_element *obj = rc_malloc(sizeof(struct int_element), NULL);
    obj->class = &int_element_class;
    obj->val = value;
    return obj;
}

int int_element_get_value(struct int_element *e) {
    return e->val;
}

int is_int_element(struct element* e) {
    // compare jump table addresses
    // can do this because jump table addresses are static
    return e->class == &int_element_class;
}
