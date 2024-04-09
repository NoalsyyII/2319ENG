#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>

float compute_sphere_volume(float radius);

int main(){

    float inprad;

    printf("Enter radius of sphere in m >>");
    scanf("%f", &inprad);

    printf("The volume of the sphere is %.2fm^3", compute_sphere_volume(inprad));

    return 0;
}

float compute_sphere_volume(float radius){

    float out = 4.0 / 3.0 * M_PI * pow(radius, 3);

    return out;
}


