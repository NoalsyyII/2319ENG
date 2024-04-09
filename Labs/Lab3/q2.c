#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

double compute_cap_reactance(double cap, double freq);

int main(){

    double cap, freq;

    printf("Enter capacitance and frequency, seperated by a comma >>");

    scanf("%lf,%lf", &cap, &freq);

    printf("The reactance of the capacitor is %.2f Ohm", compute_cap_reactance(cap, freq));

    return 0;
}

double compute_cap_reactance(double cap, double freq){

    double out = 1 / (2 * M_PI * freq * cap);

    return out;
}