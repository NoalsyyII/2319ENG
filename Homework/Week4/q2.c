#include <stdio.h>
int is_vowel(char input){

    char vowels[6] = "aeiou";

    for(int i = 0; i < 6; i++){
        if(input == vowels[i]){
            return 1;
        }
    }

    return 0;
}

int main(){

    if (is_vowel('a') && !is_vowel('b')){
        printf("Yippee!");
    }
    return 0;
}