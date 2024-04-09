#include <stdio.h>

void display_dollar(float money){
    printf("$%.2f", money);
}

int main(){
    float a = 2.56, b = 600.03;
    display_dollar(a);
    printf("\n");
    display_dollar(b);
    return 0;
}