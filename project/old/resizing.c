#include <stdlib.h>
#include <stdio.h>

#define MAX_STRING 100
#define MAX_ARRLEN 100

typedef struct book {
    int ISBN;
    int isborrowed;
    char title[MAX_STRING];
    char author[MAX_STRING];
} Book;

typedef struct user {
    int ID;
    char name[MAX_STRING];
    Book borrowedbooks[MAX_ARRLEN];
} User;

int bookcount = 0, usercount = 0;
Book book[];
User users[];


int main(){


    return 0;
}