#include <stdio.h>
#include <strings.h>

#define MAX_STRING 100

int main(){
    
    char first[MAX_STRING], second[MAX_STRING];

    printf("Enter first word >>");
    fgets(first, MAX_STRING - 1, stdin);

    printf("Enter second word >>");
    fgets(second, MAX_STRING - 1, stdin);

    printf("First string is %d characters long\nSecond string is %d characters long\n", strlen(first) - 1, strlen(second) - 1);

    if(!strcmp(first, second)){
        printf("The strings are equal!");
    } else{
        printf("The strings are not equal :(");
    }

    return 0;
}