#include <stdio.h>
#include <math.h>

int main(){

    float a, b, c, d, e, f, g, h, guess;

    printf("Enter 8 values, seperated by a comma >>");
    scanf("%f,%f,%f,%f,%f,%f,%f,%f", &a, &b, &c, &d, &e, &f, &g, &h);

    float answer = a * ++b + c / d - e * (f + g) / h++;

    printf("Have a guess >>");
    scanf(" %f", &guess);

    if(fabs(guess - answer) < 0.0001){
        printf("Hooray! %.4f is the correct answer!", answer);
    } else{
        printf("Incorrect! %.4f is the correct answer", answer);
    }
    
    return 0;
}