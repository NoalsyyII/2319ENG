#include <stdio.h>


int main(){

    int input;

    printf("Input number for checking: ");
    scanf("%d", &input);

    if(input % 2 == 0){
        printf("%d is even!", input);
    } else {
        printf("%d is odd!", input);
    }

    return 0;
}