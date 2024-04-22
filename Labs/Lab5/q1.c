#include <stdio.h>
#include <math.h>

void statistics(float*, int, float*, float*, float*);

int main(){

    float arrcheck[5] = {1, 2, 3, 4, 5};

    float m, st, var, *mptr, *stptr, *varptr;

    mptr = &m;
    stptr = &st;
    varptr = &var;

    statistics(arrcheck, 5, mptr, stptr, varptr);

    printf("%f, %f, %f", m, st, var);


    return 0;
}

void statistics(float* arr, int len, float* mean, float* stdev, float* var){

    float sum = 0, sumsquare = 0, varsum = 0;

    for(int i = 0; i < len; i++){
        sum += *(arr + i);
        sumsquare += pow(*(arr + i), 2);
        
    }

    *mean = sum / len;
    *stdev = sqrt((sumsquare / len) - pow((sum / len), 2));

    for(int i = 0; i < len; i++){
        varsum += pow((*(arr + i) - *mean), 2);
    }

    *var = varsum / len;
}