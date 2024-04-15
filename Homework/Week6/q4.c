#include <stdio.h>

void findResistance(float, float, float*, float*); // Q3


int main(){

    float first = 2.0, second = 3.0, series, parallel;

    float *pseries = &series, *pparallel = &parallel;

    findResistance(first, second, pseries, pparallel);

    printf("%f, %f", parallel, series);

    return 0;
}

void findResistance(float r1, float r2, float* ser, float* para){
    *ser = r1 + r2;
    *para = (r1 * r2) / (r1 + r2);
}
