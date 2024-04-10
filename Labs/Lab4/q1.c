#include <stdio.h>
#include <stdlib.h>

int main(){

    int count = 0, input, nums[5];

    while(count <= 5){
        printf("Enter number >>");
        scanf("%d", &input);
        
        if(input){
            nums[count] = input;
        } else {
            break;
        }
        count++;
    }

    system("cls");

    for(int i = 0; i < count; i++){
        printf("Number %d: %d\n", i + 1, nums[i]);
    }

    return 0;
}