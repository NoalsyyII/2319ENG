#include <stdio.h>

int main(){

    int input;

    printf("Enter number: ");
    scanf("%d", &input);

    if(input > 10){
        printf("Big\n");
    } else {
        printf("Little\n");
    }

    return 0;
}