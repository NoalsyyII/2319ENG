#include <stdio.h>

#define PI 3.141

int main(){

    int r;

    printf("Enter integer radius of sphere: ");
    scanf("%d", &r);


    float volume = (4.0/3.0) * PI * r * r;

    printf("The volume of a sphere with radius %i is %.2f", r, volume);


    return 0;
}