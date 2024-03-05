#include <stdio.h>
#define MAX 32

int main(){

    char name[MAX];

    printf("Enter Name:");

    scanf("%32s", name);

    printf("Hello %s!", name);

    

    return 0;

}