#include <stdio.h>

int main(){
    
    float input1, input2;

    printf("Enter two values, seperated by a comma (a,b)>>");
    scanf("%f,%f", &input1, &input2);

    float add = input1 + input2;
    float sub = input1 - input2;
    float mul = input1 * input2;
    float div = input1 / input2;

    printf("%.2f + %.2f = %.2f\n", input1, input2, add);
    printf("%.2f - %.2f = %.2f\n", input1, input2, sub);
    printf("%.2f * %.2f = %.2f\n", input1, input2, mul);
    printf("%.2f / %.2f = %.2f\n", input1, input2, div);

    return 0;
}