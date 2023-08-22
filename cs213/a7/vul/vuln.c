#include <unistd.h>

int str1 = 30;
char* _str1 = "Welcome! Please enter a name:\n";
int str2 = 11;
char* _str2 = "Good luck, ";

int main() {
    char* buf[128];
    print(_str1, str1);
    int s = read(0, buf, 256);
    print(_str2, str2);
    write(1, buf, s);
}

void print(char* string, int i) {
    write(1, string, i);
}