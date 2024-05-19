#include <stdio.h>

void printArr(int*, int);
void selectionSort(int*, int);

int main(){
    int arr[10];

    for(int i = 0; i < 10; i++){
        printf("Enter element %d>>", i);
        scanf("%d", &arr[i]);
    }

    printf("\nArray before:");
    printArr(arr, 10);

    selectionSort(arr, 10);

    printf("\nArray after:");
    printArr(arr, 10);

    return 0;
}

void printArr(int* arr, int len){
    printf("[");
    for(int i = 0; i < len; i++){
        printf("%d,", arr[i]);
    }
    printf("]");
    return;
}

void selectionSort(int* arr, int len){
    int mindex, temp;
    for(int i = 0; i < len; i++){
        mindex = i;
        for(int j = i + 1; j < len; j++){
            if(arr[j] < arr[mindex]){
                mindex = j;
            }
        }
        if(i != mindex){
            temp = arr[i];
            arr[i] = arr[mindex];
            arr[mindex] = temp;
        }
    }
}