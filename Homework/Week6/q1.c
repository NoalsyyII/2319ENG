#include <stdio.h>

int main(){

    int a, *p;

    p = &a;

    *p = 10;

    printf("%d, %p", a, p);

    return 0;
}