#include <stdio.h>
#include <stdlib.h>

#define STRMAX 32

int main(){

    float money_in;

    printf("Input dollar/cents amount: ");
    scanf("%f", &money_in);

    float money_out = money_in * 1.05;

    printf("\nWith tax added: %.2f", money_out);
    


    return 0;
}