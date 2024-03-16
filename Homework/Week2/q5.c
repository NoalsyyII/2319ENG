#include <stdio.h>

int main(){

    int inputnum;

    printf("Enter an integer number>>");
    scanf("%d", &inputnum);

    for(int i = 0; i < inputnum; i++){
        printf("Hello\n");
    }

}