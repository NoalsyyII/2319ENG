#include <stdio.h>

int main(){

    int arr[20];

    for(int i = 0; i < 20; i++){
        arr[i] = i;
    }
    
    int* ptr = arr;

    printf("3rd: %d\n", *(ptr + 2));
    printf("5th: %d\n", *(ptr + 4));
    printf("13th: %d\n", *(ptr + 12));

    return 0;
}

