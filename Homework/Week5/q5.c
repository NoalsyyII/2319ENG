#include <stdio.h>
#include <strings.h>



int main(){

    char str[20];

    printf("Enter a word >>");
    fgets(str, 20, stdin);

    printf("Length of word: %d characters", (strlen(str) - 1));

    return 0;
}