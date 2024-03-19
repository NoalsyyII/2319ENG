#include <stdio.h>
#include <math.h>

int main(){

    int a, b, c, d, e, f, g, h;
    float guess;

    printf("Enter 8 values, seperated by a comma >>");
    scanf("%d,%d,%d,%d,%d,%d,%d,%d", &a, &b, &c, &d, &e, &f, &g, &h);

    float answer = a * ++b + c / d - e * (f + g) / h++;

    printf("Have a guess >>");
    scanf("%f", &guess);

    if(fabs(guess - answer) < 0.0001){
        printf("Hooray! %.2f is the correct answer!", answer);
    } else{
        printf("Incorrect! %.2f is the correct answer", answer);
    }
    
    return 0;
}