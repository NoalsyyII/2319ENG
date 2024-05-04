#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>

#define MAX_STRING 50
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
Book books[MAX_ARRLEN];
User users[MAX_ARRLEN];


//File I/O
int loadBooks();
int loadUsers();
int saveBook(Book);
int saveUser(User);


int main(){
    // Book testbook, testbook1;
    // testbook.ISBN = 1234;
    // testbook.isborrowed = 0;
    // strcpy(testbook.title, "The Adventures of Soah Nimpson");
    // strcpy(testbook.author, "N.T Simpson");
    // books[0] = testbook;

    // testbook1.ISBN = 5678;
    // testbook1.isborrowed = 0;
    // strcpy(testbook1.title, "Shartmeister");
    // strcpy(testbook1.author, "Noah TS");
    // books[1] = testbook1;

    // for(int i = 0; i < 2; i++){
    //     if(saveBook(books[i])){
    //         printf("Book %d saved successfully\n", books[i].ISBN);
    //     }
    // }

    loadBooks();

    printf("Count: %d\n", bookcount);
    for(int i = 0; i < bookcount; i++){
    printf("%d | %s | %s | %s\n", books[i].ISBN, books[i].title, books[i].author, books[i].isborrowed? "Yes":"No");
    }

}

int saveBook(Book tosave){
    FILE *catalogue = NULL;

    if((catalogue = fopen("catalogue.txt", "a")) == NULL){
        return 0;
    }

    fprintf(catalogue, "%d\t%s\t%s\t%d\n",tosave.ISBN, tosave.title, tosave.author, tosave.isborrowed);

    fclose(catalogue);

    return 1;

}

int loadBooks(){
    FILE *catalogue = NULL;
    int tempISBN, tempisborrowed;
    char temptitle[MAX_STRING], tempauthor[MAX_STRING];
    Book tempbook;

    if((catalogue = fopen("catalogue.txt", "r")) == NULL){
        return 0;
    }
    while(!feof(catalogue)){
        fscanf(catalogue, "%d\t%s\t%s\t%d", &tempbook.ISBN, tempbook.title, tempbook.author, &tempbook.isborrowed);
        books[bookcount] = tempbook;
        bookcount++;
    }

    return 1;


}