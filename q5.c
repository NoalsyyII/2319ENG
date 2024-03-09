#include <stdio.h>
#include <math.h> // For the pow() function, this program sucks without it

int main(){

    int x;

    printf("Enter an integer value for x: ");
    scanf("%d", &x);

    float answer = 3 * pow(x, 5) + 2 * pow(x, 4) + 5 * pow(x, 3) - pow(x, 2) + 7 * x - 6;

    printf("At x=%d, y=%.2f", x, answer);

    return 0;
}
