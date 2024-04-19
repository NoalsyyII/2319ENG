#include <stdio.h>
#include <stdlib.h>


float add(float, float);
float subtract(float, float);
float multiply(float, float);
float divide(float, float);

int main(){
    
    float num1, num2, result;
    int choice, cont = 1;
    char contchoice;

    float (*operation)(float, float);

    while(cont){
        printf("Enter two numbers, seperated by a comma >>");
        scanf("%f, %f", &num1, &num2);
        printf("Select an operation:\n1: Add\n2: Subtract\n3: Multiply\n4: Divide\n>>");
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                operation = &add;
                break;
            case 2:
                operation = &subtract;
                break;
            case 3:
                operation = &multiply;
                break;
            case 4:
                operation = &divide;
                break;
            default:
                return 0;
        }
        result = (*operation)(num1, num2);
        printf("Result: %.2f\n", result);
        
        printf("Calculate again (y/n) >>");
        scanf(" %c", &contchoice);

        if(!(contchoice == 'y' || contchoice == 'Y')){
            cont = 0;
        }
    }




    return 0;
}

float add(float a, float b){
    return a + b;
}

float subtract(float a, float b){
    return a - b;
}

float multiply(float a, float b){
    return a * b;
}

float divide(float a, float b){
    return a / b;
}