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

int bookcount = 0, usercount = 0;
Book* bookhead = NULL;
User* userhead = NULL;

//Main Menu
void mainMenu(int*);

//Book Management Menu
void manageBooks();

//User Management Menu
void manageUsers();

//Book Management
void addBookMenu();
void updateBookMenu();
void borrowBookMenu();
void returnBookMenu();
void deleteBookMenu();
void viewAllBooks();
Book* createNewBook(Book**, int, int, char*, char*);
int deleteBook(Book**, int);
char* getTitleFromID(int id);
Book* findBookInList(int);

//User Management
void addUserMenu();
void updateUserMenu();
void deleteUserMenu();
void viewAllUsers();
User* createNewUser(User**, int, char*, int, int*);
int deleteUser(User**, int);
User* findUserInList(int);

//File I/O
//NOTE: Disk deletion occurs in management functions
int loadBooks(Book**);
int loadUsers(User**);
int saveBook(Book*);
int saveUser(User*);
int deleteUserFromDisk(int);
int deleteBookFromDisk(int);

void freeAll(); // free all memory before exit


int main(){
    
    if(!loadBooks(&bookhead)){
        printf("Error loading Books, exiting...");
        return 1;
    }

    if(!loadUsers(&userhead)){
        printf("Error loading users, exiting...");
        return 1;
    }
    
    printf("Welcome to the library management system!\n");
    int mainloopflag = 1;

    while(mainloopflag){
        mainMenu(&mainloopflag);
    }

    freeAll();

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



Book* createNewBook(Book** headptr, int ISBN, int isborrowed, char* title, char* author){

    Book* newbook = malloc(sizeof(Book));

    newbook->ISBN = ISBN;
    newbook->isborrowed = isborrowed;
    strcpy(newbook->title, title);
    strcpy(newbook->author, author);
    
    newbook->next = *headptr;
    *headptr = newbook;

    return newbook;

}

User* createNewUser(User** headptr, int ID, char* name, int borrowcount, int* borrowedbooks){

    User* newuser = malloc(sizeof(User));

    if(newuser == NULL){
        return NULL;
    }

    newuser->ID = ID;
    strcpy(newuser->name, name);
    newuser->borrowcount = borrowcount;
    newuser->next = NULL;

    for(int i = 0; i < borrowcount; i++){
        newuser->borrowedbooks[i] = borrowedbooks[i];
    }

    newuser->next = *headptr;
    *headptr = newuser;
    
    return newuser;
}

void manageUsers(){
//Handles user management menu functionality
    //system("cls");
    int userloopflag = 1, userchoice;

    void (*useroptions[4])() = {&viewAllUsers, &addUserMenu, &updateUserMenu, &deleteUserMenu};

    while(userloopflag){

        //system("cls");

        printf("\nUSER MANAGEMENT MENU\nThere are %d current users\n1: View all users\n2: Register new user\n3: Update user\n4: Delete user\n5: Back to main menu\n>>", usercount);
        scanf("%d", &userchoice);

        if(userchoice < 1 || userchoice > 4){
            userloopflag = 0;
            return;
        }

        (*useroptions[userchoice - 1])();
    }
}

void addUserMenu(){
    printf("Register New User:\n");

    int tempID;
    char tempname[MAX_STRING];

    printf("Enter new ID >>");
    scanf("%d", &tempID);

    if(findUserInList(tempID) != NULL){
        printf("User with ID %d already exists!, try again\n", tempID);
        return;
    }
    
    if(tempID == 0){
        printf("Error, ID cannot be 0, try again\n");
        return;
    }

    while ((getchar()) != '\n'); // clear input buffer

    printf("Enter User Name >>");
    fgets(tempname, MAX_STRING - 1, stdin);
    
    tempname[strcspn(tempname, "\n")] = 0; //cuts off newline char

    int tempborrowcount = 0;
    int tempborrows[MAX_BORROWED];

    createNewUser(&userhead, tempID, tempname, tempborrowcount, tempborrows);

    if(!saveUser(userhead)){
        printf("Error saving to disk\n");
        return;
    }

    printf("%s added sucessfully!\n", tempname);

    usercount++;
}

void updateUserMenu(){
    int searchID, choice;
    User* usertoupdate;

    printf("Enter user ID to change details >>");
    scanf("%d", &searchID);
    
    if((usertoupdate = findUserInList(searchID)) == NULL){
        printf("User with ID %d not found, try again", searchID);
        return;
    }
    
    printf("User found\nID: %d | Name: %s\n", usertoupdate->ID, usertoupdate->name);
    printf("1: Update ID\n2: Update Name\n3: Cancel\n>>");
    scanf("%d", &choice);

    switch(choice){
        case 1: 
            int tempID;

            printf("Enter new ID >>");
            scanf("%d", &tempID);

            if(tempID == 0){
                printf("Error: ID cannot be 0\nReturning to parent menu...\n");
                return;
            }

            usertoupdate->ID = tempID;

            printf("User ID updated successfully!");
            break;
        case 2:
            char tempname[MAX_STRING];

            printf("Enter new name >>");

            while ((getchar()) != '\n');

            fgets(tempname, MAX_STRING - 1, stdin);
            
            tempname[strcspn(tempname, "\n")] = 0;
            strcpy(usertoupdate->name, tempname);

            printf("User name updated successfully!");
            break;
    }

    deleteUserFromDisk(usertoupdate->ID);
    saveUser(usertoupdate);

    return;
}

void deleteUserMenu(){
    printf("Delete User:\n");
    int tempID;
    User* todelete;

    printf("Enter User ID >>");
    scanf(" %d", &tempID);

    if((todelete = findUserInList(tempID))->borrowcount){
        printf("Return this users books before deletion!");
        return;
    }

    if(deleteUser(&userhead, tempID) && deleteUserFromDisk(tempID)){
        printf("User ID: %d deleted successfully!\n", tempID);
    }else{
        printf("User with ID %d not found!", tempID);
    }
}


void viewAllUsers(){
//Iterates over user linked list to print all records
    //system("cls");
    
    if(!usercount){
        printf("ERROR: No records to display!\nReturning to main menu...");
        Sleep(1500);
        return;
    }

    printf("\n");

    User* current = userhead;
    while(current != NULL){
        User currentuser = *current;
        char strID[10], strcount[3];

        itoa(currentuser.ID, strID, 10);
        itoa(currentuser.borrowcount, strcount, 3);
        printf("ID: %-10s | Name: %-25s | Borrow Count: %-3s | Borrowed Books: ", strID,  currentuser.name, strcount);

        for(int j = 0; j < currentuser.borrowcount; j++){
            printf("%s", getTitleFromID(currentuser.borrowedbooks[j]));
            if(j != currentuser.borrowcount - 1){
                printf("+ ");
            }
        }
        printf("\n");
        
        current= current->next;
    }

}

int deleteUser(User** head, int IDtodelete){

    User* current = *head;
    User* prev = NULL;
    
    if(current == NULL){
        return 0;
    }

    if(current->ID == IDtodelete){
        *head = current->next;
        free(current);
        usercount--;
        return 1;
    }

    while(current != NULL){

        if(current->ID == IDtodelete){
            prev->next = current->next;
            free(current);
            usercount --;
            return 1;
        } else{
            prev = current;
            current = current->next;
        }
    }

    return 0;
}

User* findUserInList(int IDtofind){

    User* current = userhead;

    if(current->ID == IDtofind){
        return current;
    }

    while(current != NULL){
        if(current->ID == IDtofind){
            return current;
        } else{
            current = current->next;
        }
    }

    return NULL;

}

int loadUsers(User** head){ 
    FILE *userlist = NULL;

    char linebuffer[MAX_STRING];
    User tempuser;

    if((userlist = fopen("users.txt", "r")) == NULL){
        return 0;
    }

    while(fgets(linebuffer, MAX_STRING, userlist) && usercount < MAX_ARRLEN){
        char* token = strtok(linebuffer, "\t"); // Splits linebuffer by tab-delimiter!!!
        
        tempuser.ID = atoi(token); // read first token into ID

        if(tempuser.ID == 0){
            continue;
        }

        token = strtok(NULL, "\t"); // returns the next token found before the next tab character

        strncpy(tempuser.name, token, MAX_STRING - 1); // copy MAX_STRING - 1 chars into user name
        tempuser.name[strcspn(tempuser.name, "\n")] = 0;
        tempuser.name[MAX_STRING - 1] = '\0'; // need to append null char

        tempuser.borrowcount = 0;
        while((token = strtok(NULL, "\t")) != NULL && tempuser.borrowcount < MAX_BORROWED){
            tempuser.borrowedbooks[tempuser.borrowcount] = atoi(token);
            tempuser.borrowcount++;
        }

        createNewUser(head, tempuser.ID, tempuser.name, tempuser.borrowcount, tempuser.borrowedbooks);
        usercount++;

    }

    fclose(userlist);

    return 1;
}

int saveUser(User* tosave){
    FILE *userlist = NULL;

    if((userlist = fopen("users.txt", "a")) == NULL){
        return 0;
    }

    fprintf(userlist, "%d\t%s",tosave->ID, tosave->name);

    if(tosave->borrowcount){
        fprintf(userlist, "\t");
        for(int i = 0; i < tosave->borrowcount; i++){
            fprintf(userlist, "%d", tosave->borrowedbooks[i]);
            if(i != tosave->borrowcount - 1){
                fprintf(userlist, "\t");
            }
        }
    }

    fprintf(userlist, "\n");

    fclose(userlist);

    return 1;
}

int deleteUserFromDisk(int IDtodelete){
    //Handler function to delete user from file, returns 1 if user is found and deleted, 0 otherwise.
    FILE *userlist = NULL, *newuserlist = NULL;

    char linebuffer[MAX_STRING];
    int checkID, lineindex = 0, status = 0;

    if((userlist = fopen("users.txt", "r")) == NULL || (newuserlist = fopen("temp.txt", "w")) == NULL){
        return status;
    }

    while(fgets(linebuffer, MAX_STRING, userlist)){
        sscanf(linebuffer, "%d", &checkID);

        if(checkID == IDtodelete){
            status = 1;
            continue;
        }

        fprintf(newuserlist, "%s", linebuffer);
    }

    fclose(userlist);
    fclose(newuserlist);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    return status;

}


void manageBooks(){
//Handles book management menu functionality
    //system("cls");
    int bookloopflag = 1, bookchoice;

    void (*bookoptions[6])() = {&viewAllBooks, &addBookMenu, &updateBookMenu, &deleteBookMenu, &borrowBookMenu, &returnBookMenu};

    while(bookloopflag){

        //system("cls");

        printf("\nBOOK MANAGEMENT MENU\nThere are %d current titles\n1: View all titles\n2: Register new title\n3: Update book information\n4: Delete title\n5: Borrow book\n6: Return book\n7: Back to main menu\n>>", bookcount);
        scanf("%d", &bookchoice);

        if(bookchoice < 1 || bookchoice > 6){
            bookloopflag = 0;
            return;
        }

        (*bookoptions[bookchoice - 1])();
    }
}

void addBookMenu(){
    //Menu function for adding book, checks for duplicate additions before updating.
    printf("Add New Title:\n");
    int tempISBN;
    char temptitle[MAX_STRING], tempauthor[MAX_STRING];    

    printf("Enter Book ISBN >>");
    scanf(" %d", &tempISBN);
    if(findBookInList(tempISBN) != NULL){
        printf("Book with ISBN %d already exists!, try again\n", tempISBN);
        return;
    } else if(tempISBN == 0){
        printf("Error, ISBN cannot be 0, try agian\n");
        return;
    }

    while ((getchar()) != '\n'); // clear input buffer

    printf("Enter Book Title >>");
    fgets(temptitle, MAX_STRING - 1, stdin);
    
    temptitle[strcspn(temptitle, "\n")] = 0; //cuts off newline char
    
    printf("Enter Book Author >>");
    fgets(tempauthor, MAX_STRING - 1, stdin);
    
    tempauthor[strcspn(tempauthor, "\n")] = 0; //cuts off newline char

    createNewBook(&bookhead, tempISBN, 0, temptitle, tempauthor);

    if(!saveBook(bookhead)){
        printf("Error saving to disk");
        return;
    }

    printf("%s added sucessfully!\n", temptitle);

    bookcount++;
}

void updateBookMenu(){
    //Handles menu and updating of boooks
    int searchID, choice;
    Book* booktoupdate;

    printf("Enter book ISBN to change details >>");
    scanf("%d", &searchID);
    
    if((booktoupdate = findBookInList(searchID)) == NULL){
        printf("Book with ISBN %d not found, try again", searchID);
        return;
    }
    
    printf("ISBN: %d | Title: %-40s | Author: %-30s | Borrowed: %s\n", booktoupdate->ISBN, booktoupdate->title, booktoupdate->author, (booktoupdate->isborrowed ? "Yes" : "No") );
    printf("1: Update ISBN\n2: Update Title\n3: Update Author\n4: Exit\n>>", bookcount);
    scanf("%d", &choice);

    switch(choice){
        case 1: 
            int tempISBN;

            printf("Enter new ISBN >>");
            scanf("%d", &tempISBN);

            if(tempISBN == 0){
                printf("Error: ISBN cannot be 0\nReturning to parent menu...\n");
                return;
            }

            booktoupdate->ISBN = tempISBN;

            printf("Book ISBN updated successfully!");
            break;
        case 2:
            char temptitle[MAX_STRING];

            printf("Enter new title >>");

            while ((getchar()) != '\n');

            fgets(temptitle, MAX_STRING - 1, stdin);
            
            temptitle[strcspn(temptitle, "\n")] = 0;
            strcpy(booktoupdate->title, temptitle);

            printf("Book title updated successfully!");
            break;
        case 3:
            char tempauthor[MAX_STRING];

            printf("Enter new author >>");

            while ((getchar()) != '\n');

            fgets(tempauthor, MAX_STRING - 1, stdin);
            
            tempauthor[strcspn(tempauthor, "\n")] = 0;
            strcpy(booktoupdate->author, tempauthor);

            printf("Book author updated successfully!");
            break;
        default:
            return;

    }

    deleteBookFromDisk(booktoupdate->ISBN);
    saveBook(booktoupdate);

    return;
}

void deleteBookMenu(){
//Handles delete user menu, passing values to generic handler functions for deletion.
    printf("Delete Title:\n");
    int tempISBN;

    printf("Enter Book ISBN >>");
    scanf(" %d", &tempISBN);

    Book* todelete = findBookInList(tempISBN);

    if(todelete == NULL){
        printf("Book with ISBN %d not found!", tempISBN);
        return;
    }else if(todelete->isborrowed){
        printf("Book must be returned before deletion!");
        return;
    }

    if(deleteBook(&bookhead, tempISBN) && deleteBookFromDisk(tempISBN)){
        printf("ISBN %d deleted successfully!\n", tempISBN);
    }

}

void borrowBookMenu(){
    int tempID, tempISBN;

    printf("Enter borrowing user's ID >>");
    scanf("%d", &tempID);

    User* borrower = findUserInList(tempID);

   if(borrower == NULL){
        printf("No user with ID %d found!", tempID);
        return;
    } else if(borrower->borrowcount == MAX_BORROWED){
        printf("Too many books already borrowed!");
        return;
    }

    printf("Enter book ISBN >>");
    scanf("%d", &tempISBN);

    Book* booktoborrow = findBookInList(tempISBN);

    if(booktoborrow == NULL){
        printf("No book with ISBN %d found!", tempISBN);
        return;
    } else if(booktoborrow->isborrowed){
        printf("Book with ISBN %d is already borrowed, return it before borrowing again", tempISBN);
        return;
    }

    borrower->borrowedbooks[borrower->borrowcount] = tempISBN;
    borrower->borrowcount++;
    booktoborrow->isborrowed = 1;

    printf("Book %d borrowed successfully!", borrower->borrowedbooks[borrower->borrowcount - 1]); // Debugging step, struct access not necessary


    deleteBookFromDisk(booktoborrow->ISBN);
    saveBook(booktoborrow);
    deleteUserFromDisk(borrower->ID);
    saveUser(borrower);

    return;

}

void returnBookMenu(){
    int tempID, tempISBN;

    printf("Enter borrowing user's ID >>");
    scanf("%d", &tempID);

    User* borrower = findUserInList(tempID);

   if(borrower == NULL){
        printf("No user with ID %d found!", tempID);
        return;
    } else if(!borrower->borrowcount){
        printf("User %d has no books borrowed!", tempID);
        return;
    }

    printf("Enter book ISBN >>");
    scanf("%d", &tempISBN);

    Book* booktoreturn = findBookInList(tempISBN);

    if(booktoreturn == NULL){
        printf("No book with ISBN %d found!", tempISBN);
        return;
    } else if(!booktoreturn->isborrowed){
        printf("Book with ISBN %d is not borrowed, borrow it before returning", tempISBN);
        return;
    }

    int bookpresent = 0;
    for(int i = 0; i < borrower->borrowcount; i++){
        if(borrower->borrowedbooks[i] == tempISBN){
            bookpresent = 1;

            for (int j = i; j < borrower->borrowcount - 1; j++){
                borrower->borrowedbooks[j] = borrower->borrowedbooks[j + 1];
            }
            borrower->borrowcount--;
            break;
        }
    }

    if(!bookpresent){
        printf("User %d has no book with ISBN %d!", tempID, tempISBN);
        return;
    }

    booktoreturn->isborrowed = 0;

    printf("Book %d returned successfully!", booktoreturn->ISBN); //debugging step!


    deleteBookFromDisk(booktoreturn->ISBN);
    saveBook(booktoreturn);
    deleteUserFromDisk(borrower->ID);
    saveUser(borrower);

    return;
}

void viewAllBooks(){
//Iterates over arrays to display all records
    if(!bookcount){
        printf("ERROR: No records to display!\nReturning to main menu...");
        Sleep(1500);
        return;
    }
    printf("\n");

    Book* current = bookhead;

    while(current != NULL){
        printf("ISBN: %d | Title: %-40s | Author: %-30s | Borrowed: %s\n", current->ISBN, current->title, current->author, (current->isborrowed ? "Yes" : "No") );

        current = current->next;
    }
}

int deleteBook(Book** head, int ISBNtodelete){
    Book* current = *head;
    Book* prev = NULL;

    if(current == NULL){
        return 0;
    }

    if(current->ISBN == ISBNtodelete){
        *head = current-> next;
        free(current);
        bookcount--;
        return 1;
    }

    while(current != NULL){

        if(current->ISBN == ISBNtodelete){
            prev->next = current->next;
            free(current);
            bookcount--;
            return 1;
        } else{
            prev = current;
            current = current->next;
        }
    }

    return 0;
}

Book* findBookInList(int ISBNtofind){

    Book* current = bookhead;

    if(current->ISBN == ISBNtofind){
        return current;
    }

    while(current != NULL){
        if(current->ISBN == ISBNtofind){
            return current;
        } else{
            current = current->next;
        }
    }

    return NULL;

}

int loadBooks(Book** head){
    FILE *catalogue = NULL;

    char linebuffer[MAX_STRING];
    Book tempbook;

    if((catalogue = fopen("catalogue.txt", "r")) == NULL){
        return 0;
    }

    while(fgets(linebuffer, MAX_STRING, catalogue) && bookcount < MAX_ARRLEN){
        char* token = strtok(linebuffer, "\t"); // Splits linebuffer by tab-delimiter!!!
        
        tempbook.ISBN = atoi(token); // read first token into ID

        if(tempbook.ISBN == 0){
            continue;
        }

        token = strtok(NULL, "\t"); // returns the next token found before the next tab character

        strncpy(tempbook.title, token, MAX_STRING - 1);
        tempbook.title[strcspn(tempbook.title, "\n")] = 0;
        tempbook.title[MAX_STRING - 1] = '\0'; // need to append null char

        token = strtok(NULL, "\t"); // returns the next token found before the next tab character

        strncpy(tempbook.author, token, MAX_STRING - 1); 
        tempbook.author[strcspn(tempbook.author, "\n")] = 0;
        tempbook.author[MAX_STRING - 1] = '\0'; // need to append null char

        token = strtok(NULL, "\t");

        tempbook.isborrowed = atoi(token);

        createNewBook(head, tempbook.ISBN, tempbook.isborrowed, tempbook.title, tempbook.author);
        bookcount++;

    }

    fclose(catalogue);

    return 1;
}

int saveBook(Book* tosave){
    FILE *catalogue = NULL;

    if((catalogue = fopen("catalogue.txt", "a")) == NULL){
        return 0;
    }

    fprintf(catalogue, "%d\t%s\t%s\t%d\n",tosave->ISBN, tosave->title, tosave->author, tosave->isborrowed);

    fclose(catalogue);

    return 1;
}

int deleteBookFromDisk(int IDtodelete){
//Handler function to delete book from file, returns 1 if book is found and deleted, 0 otherwise.
    FILE *catalogue = NULL, *newcatalogue = NULL;

    char linebuffer[MAX_STRING];
    int checkID, lineindex = 0, status = 0;

    if((catalogue = fopen("catalogue.txt", "r")) == NULL || (newcatalogue = fopen("temp.txt", "w")) == NULL){
        return status;
    }

    while(fgets(linebuffer, MAX_STRING, catalogue)){
        sscanf(linebuffer, "%d", &checkID);

        if(checkID == IDtodelete){
            status = 1;
            continue;
        }

        fprintf(newcatalogue, "%s", linebuffer);
    }

    fclose(catalogue);
    fclose(newcatalogue);

    remove("catalogue.txt");
    rename("temp.txt", "catalogue.txt");

    return status;

}

char* getTitleFromID(int id){
    return findBookInList(id)->title;
}

void freeAll(){
    Book* currentbook = bookhead;
    Book* nextbook = NULL;

    while(currentbook!=NULL){
        nextbook = currentbook->next;
        free(currentbook);
        currentbook = nextbook;
    }

    User* currentuser = userhead;
    User* nextuser = NULL;

    while(currentuser!=NULL){
        nextuser = currentuser->next;
        free(currentuser);
        currentuser = nextuser;
    }
}













