#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

void *p;

int main() {
    void *v = malloc (1024 * 1024 * 1024);
    printf("%p\n", v);

    int *i = v;
    printf("%p\n", &i[0]); //i[0] = *. so &* cancel out.
    // i and v are the same. &i[0] == i
    //&i the address of i (pointer)

    int d = &i[1]  - &i[0]; //number of indices
    printf("%d\n", d);

    char *c = v;
    *i = 0x12345678;
    for (int k = 0; k<4; k++){
        printf("%d: 0x%x\n", k, c[k]));
    }
}