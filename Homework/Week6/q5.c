#include <stdio.h>

void my_strcpy(char* source, char* destination){
    
    int i = 0;

    while(*(source + i) != '\0'){
        *(destination + i) = *(source + i);
        i++;
    }
    
}

int main(){

    char first[32] = "Noah Simpson";
    char second[32];

    printf("First: %s, Second: %s\n", first, second);

    my_strcpy(first, second);

    printf("First: %s, Second: %s", first, second);

}