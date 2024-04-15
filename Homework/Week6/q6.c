/* 
A function pointer is a pointer that points to the address of code, instead of a variable.
Function pointers are used to pass functions as arguments to other functions, or to return function calls as arguments
from other fucntions. 
*/

int myFunction(float a, float b){
    return 1;
}

int main(){

    int (*funcPtr)(float, float);

    funcPtr = &myFunction;


    return 0;
}