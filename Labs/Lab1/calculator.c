#include <stdio.h>
#include <stdlib.h>

int main(){

    float input1, input2;
    char operation, again;
    float out;
    
    while(1){
        printf("Enter two values, seperated by a comma (a,b)>>");
        scanf("%f,%f", &input1, &input2);

        printf("Choose an operation\na: +\nb: -\nc: *\nd: /\ne: ++\nf: --\ng: exit\n>>");
        scanf(" %c", &operation);
        

        switch(operation){
            case 'a':
                out = input1 + input2;
                printf("%.2f + %.2f = %.2f", input1, input2, out);
            break;
            case 'b':
                out = input1 - input2;
                printf("%.2f - %.2f = %.2f", input1, input2, out);
            break;
            case 'c':
                out = input1 * input2;
                printf("%.2f * %.2f = %.2f", input1, input2, out);
            break;
            case 'd':
                if(!input2){
                    printf("Cannot divide by zero! Pick a new denominator>>");
                    scanf("%f", &input2);
                }
                    out = (float) input1 / input2;
                    printf("%.2f / %.2f = %.2f", input1, input2, out);
            break;
            case 'e':
                out = input1 + 1;
                printf("%.2f++ = %.2f", input1, out);
            break;
            case 'f':
                out = input1 - 1;
                printf("%.2f-- = %.2f", input1, out);
            break;
            case 'g':
                exit(0);
            break;
            default:
                printf("Invalid operator input\n");
            break;
        }

        printf("\nCalculate again? (y/n)>>");
        scanf(" %c", &again);

        if(again == 'y' || again == 'Y'){
            continue;
        } else{
            break;
        }

    }
    return 0;
}