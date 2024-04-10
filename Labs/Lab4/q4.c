#include <stdio.h>
#include <strings.h>
#include <ctype.h>

#define MAX_STRING 100

int isVowel(char);

int main(){

    char input[MAX_STRING];

    int spaces = 0, vowels = 0, digits = 0;

    printf("Enter string >>");
    fgets(input, MAX_STRING, stdin);

    for(int i = 0; i < strlen(input); i++){

        if(isdigit(input[i])){
            digits++;
        }

        if(isVowel(input[i])){
            vowels++;
        }

        if(input[i] == ' '){
            spaces++;
        }

    }

    printf("Spaces: %d\nVowels: %d\nDigits: %d", spaces, vowels, digits);

    return 0;
}

int isVowel(char input){

    char vowels[6] = "aeiou";

    for(int i = 0; i < 6; i++){
        if(input == vowels[i]){
            return 1;
        }
    }

    return 0;
}

