#include <stdio.h>

float average(float nums[], int len);

int main(){

    float testnums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    float realmean = (1 + 1.5 + 2 + 2.5 + 3) / 5.0;

    printf("Expected: %f\nActual: %f", realmean, average(testnums, 10));

    return 0;
}

float average(float nums[], int len){

    float sum = 0;

    for(int i = 0; i < len; i++){
        sum += nums[i];
    }

    return sum / len;
}