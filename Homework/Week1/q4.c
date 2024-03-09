#include <stdio.h>

int main(){

    int a, b;

    printf("Enter values for a and b, separated by a comma (a,b): ");
    scanf("%d,%d", &a, &b);

    int remainder = a % b;

    printf("Remainder of %d / %d is %d", a, b, remainder);

    return 0;
}