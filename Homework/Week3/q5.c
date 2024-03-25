#include <stdio.h>

float power(float num, int pow){
    
    float out = 1; // multiplication only so its calm
    
    int i = 0;
    while(i < pow){
        out = out * num;
        i++;
    }

    return out;
}

int main(){

    float a = 2.00, b = 4.00;

    int c = 2;
    
    printf("%f, %f", power(a, c), power(b, c));


    return 0;
}