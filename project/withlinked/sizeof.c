#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_STRING 100
#define MAX_ARRLEN 100
#define MAX_BORROWED 10
#define INIT_BOOK_CAPACITY 25
#define INIT_USER_CAPACITY 25

typedef struct book {
    int ISBN;
    int isborrowed;
    char title[MAX_STRING];
    char author[MAX_STRING];
    struct book* next;
} Book;

typedef struct user {
    int ID;
    char name[MAX_STRING];
    int borrowcount;
    int borrowedbooks[MAX_BORROWED];
    struct user* next;
} User;

int main(){

    printf("Book %d\nUser %d\n", sizeof(Book), sizeof(User));

    return 0;
}