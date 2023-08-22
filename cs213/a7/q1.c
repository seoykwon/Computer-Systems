#include <stdio.h>

int arr[10] = {0,0,0,0,0,0,0,0,0,0};

void func(int x, int y){
    arr[y] = arr[y] + x;
}

int main() {
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    func(a3, a4);
    func(a1, a2);
    for(int i =0; i < 10; i++){
        printf("%d", arr[i]);
        printf("\n");
    }
}