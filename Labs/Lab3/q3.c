#include <stdio.h>

int sumBetween(int first, int second);

int main(){
    
    int num1, num2;

    printf("Enter the first second number as an ordered pair >>");
    scanf("%d,%d", &num1, &num2);

    int result = sumBetween(num1, num2);

    if(result){
        printf("The sum of numbers between %d and %d is %d", num1, num2, result);
    } else{
        printf("Error! first number must be smaller than second number!");
    }

    return 0;
}

int sumBetween(int first, int second){
    
    int small, big;

    if(first > second){
        small = second;
        big = first;
    } else {
        small = first;
        big = second;
    }

    int out = 0;

    for(int i = small; i <= big; i++){
        out += i;
    }

    return out;
}