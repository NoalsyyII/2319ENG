#include <stdio.h>
#include <strings.h>

#define MAX_STRING 32

int main(){

    char input[MAX_STRING];

    printf("Enter string >>");

    fgets(input, MAX_STRING, stdin);

    for(int i = 0; i < strlen(input); i++){
        if(input[i] == ' '){
            input[i] = '_';
        } else{
            continue;
        }
    }

    printf("Altered string: %s", input);

    return 0;
}