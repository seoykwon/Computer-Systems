#include "str_element.h"
#include <stdio.h>
#include <string.h>

/* TODO: Implement all public str_element functions, including element interface functions.

You may add your own private functions here too. */

struct str_element {
    struct element_class *class;
    char *value;
};

static void str_element_print(struct element *e){
    struct str_element *se = (struct str_element *)e;
    printf("%s", se->value);
}

static int str_element_compare(struct element *e1, struct element *e2){
    if (is_str_element(e2)){
        char *v1 = ((struct str_element *)e1)->value;
        char *v2 = ((struct str_element *)e2)->value;
        return strcmp(v1, v2);
    } else { return 1; }
}

static struct element_class str_element_class = {str_element_print, str_element_compare};

static void str_element_finalize(void* p){
    struct str_element *se = p;
    rc_free_ref(se->value);
}

struct str_element *str_element_new(char *value) {
    struct str_element *e = rc_malloc(sizeof(struct str_element), str_element_finalize);
    e->class = &str_element_class;
    int slen = strlen(value) + 1;
    e->value = rc_malloc(slen, NULL);
    memcpy(e->value, value, slen);
    return e;
}

char *str_element_get_value(struct str_element *e) {
    return e->value;
}

int is_str_element(struct element *e) {
    // compare jump table addresses
    // can do this because jump table addresses are static
    return e->class == &str_element_class;
}
