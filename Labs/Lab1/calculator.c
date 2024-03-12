#include <stdio.h>
#include <stdlib.h>

int main(){

    float input1, input2;
    char choice;
    float out;
    while(1){
    printf("Enter two values, seperated by a comma (a,b)>>");
    scanf("%f,%f", &input1, &input2);

    printf("Choose an operation\na: +\nb: -\nc: *\nd: /\ne: ++\nf: --\ng: exit\n>>");
    scanf(" %c", &choice);
    

    switch(choice){
        case 'a':
        out = input1 + input2;
        printf("%f + %f = ", input1, input2);
        break;
        case 'b':
        out = input1 - input2;
        printf("%f - %f = ", input1, input2);
        break;
        case 'c':
        out = input1 * input2;
        printf("%f * %f = ", input1, input2);
        break;
        case 'd':
        if(input2){
            out = (float) input1 / input2;
            printf("%f / %f = ", input1, input2);
        }
        break;
        case 'e':
        out = input1++;
        printf("%f++ = ", input1);
        break;
        case 'f':
        out = input1--;
        printf("%f-- = ", input1);
        break;
        case 'g':
        exit(0);
        break;
    }
    
    printf("%.2f\n", out);

    char again;
    printf("Calculate again? (y/n)>>");
    scanf(" %c", &again);

    if(again == 'y' || again == 'Y'){
        continue;
    } else{
        break;
    }

    }
    return 0;
}