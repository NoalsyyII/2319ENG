#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

long long factorial(int num);
float taylorSine(float x, int termcount);
float preciseTaylorSine(float x, double precision)

int main(){

    // for(int i = 0; i <= 4; i++){
    //     printf("%dpi/2, %f\n", i, taylorSine(i * M_PI / 2, 6));
    // }

    float xin;
    int terms;

    printf("Enter x and the number of terms, separated by a comma >>");
    scanf("%f,%d", &xin, &terms);
    printf("Native Sine: %f\n", sin(xin));
    printf("Taylor sine: %f", taylorSine(xin, terms));

    return 0;
}

long long factorial(int num){
    long long out = 1;

    for(int i = 0; i < num; i++){
        out *= num - i;
    }

    return out;
}

float taylorSine(float x, int termcount){
    float out;

    for(int i = 1; i <= termcount; i++){
        
        int expo = (i * 2) - 1;

        out += pow(-1, i + 1) * pow(x, expo) / factorial(expo);
    }
    
    return out;
}

float preciseTaylorSine(float x, double precision){
    float out;
    
    int i = 0;

    while(i < 10){
        
        int expo = (i * 2) - 1;

        out += pow(-1, i + 1) * pow(x, expo) / factorial(expo);

        
    }

}