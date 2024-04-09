#include <stdio.h>

int main(){

    int a, b;

    printf("Enter values for a and b, separated by a comma (a,b): ");
    scanf("%d,%d", &a, &b);

    int answer = a + b;

    printf("Sum of %d and %d is %d", a, b, answer);


    return 0;
}