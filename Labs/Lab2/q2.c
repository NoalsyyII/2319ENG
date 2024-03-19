#include <stdio.h>

int main(){

    int input, sum = 0;

    do{
        printf("Enter a number >>");
        scanf("%d", &input);
        sum += input;
    } while(input);

    printf("The sum of all inputs = %d", sum);

    return 0;
}