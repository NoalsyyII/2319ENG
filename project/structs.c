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

//Menu Functions
void mainMenu(int*);
void manageBooks();
void manageUsers();

//Shared Functions
int deleteFromRecords(int, int*, char);
int findMe(int, Book*, int);

//Book management deliverables
void addBook();
void viewAllBooks();
void updateBook();
void deleteBook();

// //User management deliverables
void registerUser();
void viewAllUsers();
void updateUser();
void deleteUser();

int main(){
    printf("Welcome to the library management system!\n");
    Sleep(1000);
    int mainloopflag = 1;

    while(mainloopflag){
        mainMenu(&mainloopflag);
    }

    return 0;
}

void mainMenu(int* mainloopflag){
//Handles main menu functionality, takes a pointer to the main menu loop flag as input.
    int mainchoice;
    void (*mainoptions[2])() = {&manageUsers, &manageBooks};

    while(*mainloopflag){
        //system("cls");

        printf("MAIN MENU\n1: User Management\n2: Book Management\n3: Exit\n>>");
        scanf("%d", &mainchoice);

        if(mainchoice < 1 || mainchoice > 2){
            *mainloopflag = 0;
            return;
        }

        (*mainoptions[mainchoice - 1])();

    }
}

void manageUsers(){
//Handles user management menu functionality
    //system("cls");
    printf("Managing users");
    int userloopflag = 1, userchoice;

    void (*useroptions[4])() = {&viewAllUsers, &registerUser, &updateUser, &deleteUser};

    while(userloopflag){

        //system("cls");

        printf("USER MANAGEMENT MENU\nThere are %d current users\n1: View all users\n2: Register new user\n3: Update user\n4: Delete user\n5: Back to main menu\n>>", usercount);
        scanf("%d", &userchoice);

        if(userchoice < 1 || userchoice > 4){
            userloopflag = 0;
            return;
        }

        (*useroptions[userchoice - 1])();
    }
}

void manageBooks(){
//Handles book management menu functionality
    //system("cls");
    printf("Managing Books");
    int bookloopflag = 1, bookchoice;

    void (*bookoptions[4])() = {&viewAllBooks, &addBook, &updateBook, &deleteBook};

    while(bookloopflag){

        //system("cls");

        printf("BOOK MANAGEMENT MENU\nThere are %d current titles\n1: View all titles\n2: Register new title\n3: Update book information\n4: Delete title\n5: Back to main menu\n>>", bookcount);
        scanf("%d", &bookchoice);

        if(bookchoice < 1 || bookchoice > 4){
            bookloopflag = 0;
            return;
        }

        (*bookoptions[bookchoice - 1])();
    }
}

void viewAllUsers(){
//Iterates over user arrays to print all records
    //system("cls");
    
    if(!usercount){
        printf("ERROR: No records to display!\nReturning to main menu...");
        Sleep(1500);
        return;
    }

    for(int i = 0; i < usercount; i++){
        printf("ID: %d | Name: %s", users[i].ID, users[i].name);
    }

}

void registerUser(){
//Handles addition menu AND array update for new users.
    printf("Register New User:\n");
    char tempname[MAX_STRING];

    while ((getchar()) != '\n'); // clear input buffer

    printf("Enter User Name >>");
    fgets(tempname, MAX_STRING - 1, stdin);
    
    tempname[strcspn(tempname, "\n")] = 0; //cuts off newline char

    users[usercount].ID = usercount;
    strcpy(users[usercount].name, tempname);

    printf("%s added sucessfully!\n", tempname);

    usercount++;
}

void updateUser(){
    //placeholder
    printf("Updating User");
    return;
}

void deleteUser(){
//Handles delete user menu, passing values to generic handler functions for deletion.
    printf("Delete User:\n");
    int tempID;

    printf("Enter User ID >>");
    scanf(" %d", &tempID);

    if(deleteFromRecords(tempID, &usercount, 'u')){
        printf("User ID: %d deleted successfully!\n", tempID);
    }

}

void viewAllBooks(){
//Iterates over arrays to display all records
    if(!bookcount){
        printf("ERROR: No records to display!\nReturning to main menu...");
        Sleep(1500);
        return;
    }

    for(int i = 0; i < bookcount; i++){
        printf("ISBN: %d | Title: %s | Author: %s | Borrowed? : %s", books[i].ISBN, books[i].title, books[i].author, (books[i].isborrowed ? "Yes" : "No") );
    }
}

void addBook(){
//Menu function for adding book, checks for duplicate additions before updating arrays.
    printf("Add New Title:\n");
    int tempISBN;
    char temptitle[MAX_STRING];

    printf("Enter Book ISBN >>");
    scanf(" %d", &tempISBN);
    if(findMe(tempISBN, books, bookcount) != -1){
        printf("Book with ISBN %d already exists!, try again\n", tempISBN);
        return;
    }

    while ((getchar()) != '\n'); // clear input buffer

    printf("Enter Book Title >>");
    fgets(temptitle, MAX_STRING - 1, stdin);
    
    temptitle[strcspn(temptitle, "\n")] = 0; //cuts off newline char

    bookids[bookcount] = tempISBN;
    strcpy(titles[bookcount], temptitle);

    printf("%s added sucessfully!\n", temptitle);

    bookcount++;
}





