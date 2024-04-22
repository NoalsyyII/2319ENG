#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>

#define MAX_STRING 50
#define MAX_ARRLEN 100

int bookcount = 0, usercount = 0, bookids[MAX_ARRLEN], userids[MAX_ARRLEN];

char titles[MAX_ARRLEN][MAX_STRING], usernames[MAX_ARRLEN][MAX_STRING];

//Menu Functions
void manageBooks();
void manageUsers();

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
    int mainloopflag = 1, mainchoice;
    Sleep(1000);

    while(mainloopflag){
        system("cls");

        printf("MAIN MENU\n1: User Management\n2: Book Management\n3: Exit\n>>");
        scanf("%d", &mainchoice);

        switch(mainchoice){
            case 1:
                manageUsers();
                break;
            case 2:
                manageBooks();
                break;
            default:
                mainloopflag = 0;
                break;
        }
    }

}

void manageUsers(){
    system("cls");
    
    int userloopflag = 1, userchoice;

    while(userloopflag){

        system("cls");

        printf("USER MANAGEMENT MENU\nThere are %d current users\n1: View all users\n2: Register new user\n3: Update user\n4: Delete user\n5: Back to main menu\n>>", usercount);
        scanf("%d", &userchoice);

        switch(userchoice){
            case 1:
                viewAllUsers();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                deleteUser();
                break;
            default:
                system("cls");
                userloopflag = 0;
                break;
        }
    }
}

void manageBooks(){
    system("cls");
    
    int bookloopflag = 1, bookchoice;

    while(bookloopflag){

        system("cls");

        printf("BOOK MANAGEMENT MENU\nThere are %d current titles\n1: View all titles\n2: Register new title\n3: Update book information\n4: Delete title\n5: Back to main menu\n>>", bookcount);
        scanf("%d", &bookchoice);

        switch(bookchoice){
            case 1:
                viewAllBooks();
                break;
            case 2:
                addBook();
                break;
            case 3:
                updateBook();
                break;
            case 4:
                deleteBook();
                break;
            default:
                system("cls");
                bookloopflag = 0;
                break;
        }
    }
}

void viewAllUsers(){
    system("cls");
    
    if(!usercount){
        printf("ERROR: No records to display!\nReturning to main menu...");
        Sleep(1500);
        return;
    }

    for(int i = 0; i < usercount; i++){
        printf("Name: %s | ID: %d\n", usernames[i], userids[i]);
    }
    




}

void registerUser(){
    printf("Registering user!\n");
}

void updateUser(){
    printf("Updating user!\n");
}

void deleteUser(){
    printf("Deleting user!\n");
}

void viewAllBooks(){
    printf("Viewing all books!\n");
}

void addBook(){
    printf("Adding Book!\n");
}

void updateBook(){
    printf("Updating book!\n");
}

void deleteBook(){
    printf("Deleting book!\n");
}