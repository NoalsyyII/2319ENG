#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>

#define MAX_STRING 50
#define MAX_ARRLEN 100

int bookcount = 0, usercount = 0, bookids[MAX_ARRLEN], userids[MAX_ARRLEN];

char titles[MAX_ARRLEN][MAX_STRING], usernames[MAX_ARRLEN][MAX_STRING];

//Menu Functions
void mainMenu(int*);
void manageBooks();
void manageUsers();

//Shared Functions
int deleteFromRecords(int, int*, char[][MAX_STRING], int*);
int findMe(int, int*, int);

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

    void (*mainselection)();

    while(*mainloopflag){
        //system("cls");

        printf("MAIN MENU\n1: User Management\n2: Book Management\n3: Exit\n>>");
        scanf("%d", &mainchoice);

        switch(mainchoice){
            case 1:
                mainselection = &manageUsers;
                break;
            case 2:
                mainselection = &manageBooks;
                break;
            default:
                *mainloopflag = 0;
                return;
        }
        (*mainselection)();
    }
}

void manageUsers(){
//Handles user management menu functionality
    //system("cls");
    
    int userloopflag = 1, userchoice;

    void (*userselection)();

    while(userloopflag){

        //system("cls");

        printf("USER MANAGEMENT MENU\nThere are %d current users\n1: View all users\n2: Register new user\n3: Update user\n4: Delete user\n5: Back to main menu\n>>", usercount);
        scanf("%d", &userchoice);

        switch(userchoice){
            case 1:
                userselection = &viewAllUsers;
                break;
            case 2:
                userselection = &registerUser;
                break;
            case 3:
                userselection = &updateUser;
                break;
            case 4:
                userselection = &deleteUser;
                break;
            default:
                userloopflag = 0;
                return;
        }

        (*userselection)();
    }
}

void manageBooks(){
//Handles book management menu functionality
    //system("cls");
    
    int bookloopflag = 1, bookchoice;

    void (*bookselection)();

    while(bookloopflag){

        //system("cls");

        printf("BOOK MANAGEMENT MENU\nThere are %d current titles\n1: View all titles\n2: Register new title\n3: Update book information\n4: Delete title\n5: Back to main menu\n>>", bookcount);
        scanf("%d", &bookchoice);

        switch(bookchoice){
            case 1:
                bookselection = &viewAllBooks;
                break;
            case 2:
                bookselection = &addBook;
                break;
            case 3:
                bookselection = &updateBook;
                break;
            case 4:
                bookselection = &deleteBook;
                break;
            default:
                bookloopflag = 0;
                return;
        }
        (*bookselection)();
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
        printf("Name: %s | ID: %d\n", usernames[i], userids[i]);
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

    userids[usercount] = usercount;
    strcpy(usernames[usercount], tempname);

    printf("%s added sucessfully!\n", tempname);

    usercount++;
}

void updateUser(){
//Handles menu for updating user, passing to appropriate functions where necessary.
    int searchID, index, choice;
    printf("Enter user ID to change details >>");
    scanf("%d", &searchID);
    
    if((index = findMe(searchID, userids, usercount)) == -1){
        printf("User with ID %d not found, try again", searchID);
        return;
    }
    
    printf("User found\nprintf(Name: %s | ID: %d\n", usernames[index], userids[index]);
    printf("1: Update ID\n2: Update Name\n3: Cancel\n>>", bookcount);
    scanf("%d", &choice);

    switch(choice){
            case 1:
                userselection = &viewAllUsers;
                break;
            case 2:
                userselection = &registerUser;
                break;
            case 3:
                userselection = &updateUser;
                break;
            case 4:
                userselection = &deleteUser;
                break;
            default:
                return;
        }


}

void deleteUser(){
//Handles delete user menu, passing values to generic handler functions for deletion.
    printf("Delete User:\n");
    int tempID;

    printf("Enter User ID >>");
    scanf(" %d", &tempID);

    if(deleteFromRecords(tempID, userids, usernames, &usercount)){
        printf("ISBN %d deleted successfully!\n", tempID);
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
        printf("Title: %s | ISBN: %d\n", titles[i], bookids[i]);
    }
}

void addBook(){
//Menu function for adding book, checks for duplicate additions before updating arrays.
    printf("Add New Title:\n");
    int tempISBN;
    char temptitle[MAX_STRING];

    printf("Enter Book ISBN >>");
    scanf(" %d", &tempISBN);
    if(findMe(tempISBN, bookids, bookcount) != -1){
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

void updateBook(){
    printf("Updating book!\n");
}

void deleteBook(){
//Handles delete user menu, passing values to generic handler functions for deletion.
    printf("Delete Title:\n");
    int tempISBN;

    printf("Enter Book ISBN >>");
    scanf(" %d", &tempISBN);

    if(deleteFromRecords(tempISBN, bookids, titles, &bookcount)){
        printf("ISBN %d deleted successfully!\n", tempISBN);
    }

}

int deleteFromRecords(int _IDtodelete, int* idlist, char namelist[][MAX_STRING], int* counter){
//Generic handler function to delete from records, takes record arrays and an ID for deletion
    int index = findMe(_IDtodelete, idlist, *counter);

    if(index == -1){
        return 0;
    }

    for(int i = index; i < *counter - 1; i++){
        idlist[i] = idlist[i + 1];
        strcpy(namelist[i], namelist[i + 1]);
    }

    *counter -= 1;

    return 1;
}

int findMe(int ID, int* idlist, int _counter){
//Returns index of a given ID for any ID list provided
    int index = -1;
    for(int i = 0; i < _counter; i++){
        if(idlist[i] == ID){
            index = i;
        }
    }
    return index;

}