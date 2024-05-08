#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRLENGTH 100

int push(int);
int pop();
int display();
int resize(int);

int arrsize = -1, elements = 0;

int* arr;

int main(){
    int mainchoice;
    int mainloopflag = 1;

    printf("Enter size of array to initialise>>");
    scanf("%d", &arrsize);

    if(arrsize < 0 || arrsize > MAX_ARRLENGTH){
        return 0;
    }

    arr = (int*)(malloc(arrsize * sizeof(int)));

    while(mainloopflag){

        printf("MAIN MENU\n1: Push Value to Array\n2: Pop last value from array\n3: Print Array\n4: Resize\n5: Exit\n>>");
        scanf("%d", &mainchoice);

        switch(mainchoice){
        case 1:
            int valuetopush;

            printf("Enter value to push >>");
            scanf("%d", &valuetopush);

            push(valuetopush);
            
            break;
        case 2:
            pop();
        
            break;
        case 3:
            display();

            break;
        case 4:
            int newsize;

            printf("Enter new size >>");
            scanf("%d", &newsize);

            resize(newsize);

            break;
        default:
            mainloopflag = 0;
            break;
    }
    }

    free(arr);
}

int display(){

    printf("Size of array (elements, memory): %d, %d\n", elements, arrsize);

    for(int i = 0; i < elements; i++){
        printf("Element %d: %d\n", i, arr[i]);
    }

    return 1;

}

int pop(){
    if(elements <= 0){
        return 0;
    }

    elements--;

    if((float)elements < (1.0/4.0) * (float)arrsize){
        arrsize /= 2;
        arr = realloc(arr, arrsize * sizeof(int));
    }

    return 1;

}

int push(int topush){

    if(elements == arrsize){
        arrsize *= 2;
        arr = realloc(arr, arrsize * sizeof(int));
    }

    arr[elements++] = topush;

    return 1;
}

int resize(int newsize){

    if(elements > newsize){
        elements = newsize;
    }

    arrsize = newsize;
    
    arr = realloc(arr, arrsize * sizeof(int));

}