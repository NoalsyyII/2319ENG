/* No, a C function cannot modify the values of the input arguments. 
    See the example function increment() below, where an input int
    is increased by 1 but this is not reflected in the main subroutine*/

#include <stdio.h>

void increment(int a){
    a++;
}


//You can cheat using pointers...
void increment_properly(int* aptr){
    int num = *aptr;
    num++;
    *aptr = num;
}

int main(){

    int b = 2;

    printf("%d\n", b);

    increment(b);

    printf("%d\n", b);

    increment_properly(&b);

    printf("%d\n", b);


    return 0;
}



