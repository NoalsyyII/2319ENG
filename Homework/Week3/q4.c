#include <stdio.h>

int main(){

    int sum = 0;

    for(int i = 1; i <= 50; i++){
        sum += i;
    }
    
    printf("Sum of numbers from 1 to 50 = %d", sum);
    
    return 0;
}