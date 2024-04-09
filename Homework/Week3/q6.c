#include <stdio.h>

int main(){

    int inputnum = 0;

    do{
        printf("Enter a number >>");
        scanf("%d", &inputnum);
    } while(inputnum != 7);

    printf("Goodbye");

    return 0;
}