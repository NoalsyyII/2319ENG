#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
int main(){
    int guess, counter = 0;

    srand(time(NULL));
    
    int secret = rand() % 100 + 1;

    printf("The number exists between 0 and %d\n", RAND_MAX % 100 + 1);

    do{
        printf("Take a guess >>");
        scanf("%d", &guess);

        if(guess > secret){
            printf("Lower!\n");
        } else{
            printf("Higher!\n");
        }
        counter++;
    } while(guess != secret);

    printf("Correct! You got it in %d guesses!", counter);

    return 0;
}