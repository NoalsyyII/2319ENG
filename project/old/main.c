#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//TODO: Add strtok() functionality to loadBooks() -> super useful!

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
} Book;

typedef struct user {
    int ID;
    char name[MAX_STRING];
    int borrowcount;
    int borrowedbooks[MAX_BORROWED];
} User;

int bookcount = 0, usercount = 0, bookcapacity = INIT_BOOK_CAPACITY, usercapacity = INIT_USER_CAPACITY;
Book* books = NULL;
User* users = NULL;

//Menus
void mainMenu(int*);
void manageBooks();
void manageUsers();

//Generic Handlers
int deleteFromRecords(int, int*, char);
int findMe(int, int, char);

//Book Management
void addBook();
void viewAllBooks();
void updateBook();
void deleteBook();
void borrowBook();
void returnBook();
char* getTitleFromID(int id);

//User Management
void registerUser();
void viewAllUsers();
void updateUser();
void deleteUser();

//File I/O
int loadBooks();
int loadUsers();
int saveBook(Book);
int saveUser(User);
int deleteBookFromDisk(int);
int deleteUserFromDisk(int);

//Memory Management
void checkAndResize(char);
void freeAll();

int main(){
    
    if(!loadBooks()){
        printf("Error loading Books, exiting...");
        return 1;
    }

    if(!loadUsers()){
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

void manageUsers(){
//Handles user management menu functionality
    //system("cls");
    int userloopflag = 1, userchoice;

    void (*useroptions[4])() = {&viewAllUsers, &registerUser, &updateUser, &deleteUser};

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

void manageBooks(){
//Handles book management menu functionality
    //system("cls");
    int bookloopflag = 1, bookchoice;

    void (*bookoptions[6])() = {&viewAllBooks, &addBook, &updateBook, &deleteBook, &borrowBook, &returnBook};

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

void viewAllUsers(){
//Iterates over user arrays to print all records
    //system("cls");
    
    if(!usercount){
        printf("ERROR: No records to display!\nReturning to main menu...");
        Sleep(1500);
        return;
    }

    printf("\n");
    for(int i = 0; i < usercount; i++){
        char strID[10], strcount[3];
        itoa(users[i].ID, strID, 10);
        itoa(users[i].borrowcount, strcount, 3);
        printf("ID: %-10s | Name: %-25s | Borrow Count: %-3s | Borrowed Books: ", strID,  users[i].name, strcount);

        for(int j = 0; j < users[i].borrowcount; j++){
            printf("%s", getTitleFromID(users[i].borrowedbooks[j]));
            if(j != users[i].borrowcount - 1){
                printf(", ");
            }
        }
        printf("\n");

    }

}

void registerUser(){
//Handles addition menu AND array update for new users.
    printf("Register New User:\n");

    int tempID;
    char tempname[MAX_STRING];

    printf("Enter new ID >>");
    scanf("%d", &tempID);

    if(findMe(tempID, usercount, 'u') != -1){
        printf("User with ID %d already exists!, try again\n", tempID);
        return;
    } else if(tempID == 0){
        printf("Error, ID cannot be 0, try again\n");
    }

    while ((getchar()) != '\n'); // clear input buffer

    printf("Enter User Name >>");
    fgets(tempname, MAX_STRING - 1, stdin);
    
    tempname[strcspn(tempname, "\n")] = 0; //cuts off newline char

    checkAndResize('u');

    users[usercount].ID = tempID;
    strcpy(users[usercount].name, tempname);

    if(!saveUser(users[usercount])){
        printf("Error saving to disk\n");
        return;
    }

    printf("%s added sucessfully!\n", tempname);

    usercount++;
}

void updateUser(){
    //Handles menu and updating of user in array and files
    int searchID, index, choice;
    printf("Enter user ID to change details >>");
    scanf("%d", &searchID);
    
    if((index = findMe(searchID, usercount, 'u')) == -1){
        printf("User with ID %d not found, try again", searchID);
        return;
    }
    
    printf("User found\nID: %d | Name: %s\n", users[index].ID, users[index].name);
    printf("1: Update ID\n2: Update Name\n3: Cancel\n>>", bookcount);
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

            users[index].ID = tempID;

            printf("User ID updated successfully!");
            break;
        case 2:
            char tempname[MAX_STRING];

            printf("Enter new name >>");

            while ((getchar()) != '\n');

            fgets(tempname, MAX_STRING - 1, stdin);
            
            tempname[strcspn(tempname, "\n")] = 0;
            strcpy(users[index].name, tempname);

            printf("User name updated successfully!");
            break;
    }

    deleteUserFromDisk(searchID);
    saveUser(users[index]);

    return;
}

void deleteUser(){
//Handles delete user menu, passing values to generic handler functions for deletion.
    printf("Delete User:\n");
    int tempID;

    printf("Enter User ID >>");
    scanf(" %d", &tempID);

    if(users[findMe(tempID, usercount, 'u')].borrowcount){
        printf("Return this users books before deletion!");
        return;
    }

    if(deleteFromRecords(tempID, &usercount, 'u')){
        printf("User ID: %d deleted successfully!\n", tempID);
    }else{
        printf("User with ID %d not found!", tempID);
    }

}

void viewAllBooks(){
//Iterates over arrays to display all records
    if(!bookcount){
        printf("ERROR: No records to display!\nReturning to main menu...");
        Sleep(1500);
        return;
    }
    printf("\n");
    for(int i = 0; i < bookcount; i++){
        printf("ISBN: %d | Title: %-40s | Author: %-30s | Borrowed: %s\n", books[i].ISBN, books[i].title, books[i].author, (books[i].isborrowed ? "Yes" : "No") );
    }
}

void addBook(){
//Menu function for adding book, checks for duplicate additions before updating array.
    printf("Add New Title:\n");
    int tempISBN;
    char temptitle[MAX_STRING], tempauthor[MAX_STRING];    

    printf("Enter Book ISBN >>");
    scanf(" %d", &tempISBN);
    if(findMe(tempISBN, bookcount, 'b') != -1){
        printf("Book with ISBN %d already exists!, try again\n", tempISBN);
        return;
    } else if(tempISBN == 0){
        printf("Error, ISBN cannot be 0, try agian\n");
    }

    while ((getchar()) != '\n'); // clear input buffer

    printf("Enter Book Title >>");
    fgets(temptitle, MAX_STRING - 1, stdin);
    
    temptitle[strcspn(temptitle, "\n")] = 0; //cuts off newline char
    
    printf("Enter Book Author >>");
    fgets(tempauthor, MAX_STRING - 1, stdin);
    
    tempauthor[strcspn(tempauthor, "\n")] = 0; //cuts off newline char

    checkAndResize('b');

    books[bookcount].ISBN = tempISBN;
    strcpy(books[bookcount].title, temptitle);
    strcpy(books[bookcount].author, tempauthor);

    if(!saveBook(books[bookcount])){
        printf("Error saving to disk");
        return;
    }

    printf("%s added sucessfully!\n", temptitle);

    bookcount++;
}

void updateBook(){
    //Handles menu and updating of book in array and files
    int searchID, index, choice;
    printf("Enter book ISBN to change details >>");
    scanf("%d", &searchID);
    
    if((index = findMe(searchID, bookcount, 'b')) == -1){
        printf("Book with ISBN %d not found, try again", searchID);
        return;
    }
    
    printf("ISBN: %d | Title: %-40s | Author: %-30s | Borrowed: %s\n", books[index].ISBN, books[index].title, books[index].author, (books[index].isborrowed ? "Yes" : "No"));
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

            books[index].ISBN = tempISBN;

            printf("Book ISBN updated successfully!");
            break;
        case 2:
            char temptitle[MAX_STRING];

            printf("Enter new title >>");

            while ((getchar()) != '\n');

            fgets(temptitle, MAX_STRING - 1, stdin);
            
            temptitle[strcspn(temptitle, "\n")] = 0;
            strcpy(books[index].title, temptitle);

            printf("Book title updated successfully!");
            break;
        case 3:
            char tempauthor[MAX_STRING];

            printf("Enter new author >>");

            while ((getchar()) != '\n');

            fgets(tempauthor, MAX_STRING - 1, stdin);
            
            tempauthor[strcspn(tempauthor, "\n")] = 0;
            strcpy(books[index].author, tempauthor);

            printf("Book author updated successfully!");
            break;
        default:
            return;

    }

    deleteBookFromDisk(searchID);
    saveBook(books[index]);

    return;
} 

void deleteBook(){
//Handles delete user menu, passing values to generic handler functions for deletion.
    printf("Delete Title:\n");
    int tempISBN;

    printf("Enter Book ISBN >>");
    scanf(" %d", &tempISBN);

    if(books[findMe(tempISBN, bookcount, 'b')].isborrowed){
        printf("Book must be returned before deletion!");
        return;
    }

    if(deleteFromRecords(tempISBN, &bookcount, 'b')){
        printf("ISBN %d deleted successfully!\n", tempISBN);
    } else{
        printf("Book with ISBN %d not found!", tempISBN);
    }

}

int deleteFromRecords(int _IDtodelete, int *counter, char mode){
//Generic handler function to delete from records, takes record arrays and an ID for deletion
    int index = findMe(_IDtodelete, *counter, mode);

    if(index == -1){
        return 0;
    }

    if(mode == 'b'){
        if(!deleteBookFromDisk(_IDtodelete)){
            return 0;
        }

        for(int i = index; i < *counter - 1; i++){
        books[i] = books[i + 1];
    }
    } else{
        if(!deleteUserFromDisk(_IDtodelete)){
            return 0;
        }

        for(int i = index; i < *counter - 1; i++){
        users[i] = users[i + 1];
    }
    }

    checkAndResize(mode);

    *counter -= 1;

    return 1;
}

int findMe(int ID, int _counter, char mode){
//Returns index of a given ID for any ID list provided
    int index = -1;

    if(mode == 'b'){
        for(int i = 0; i < _counter; i++){
            if(books[i].ISBN == ID){
                index = i;
        }
    }
    } else{
        for(int i = 0; i < _counter; i++){
            if(users[i].ID == ID){
                index = i;
        }
        }
    }

    return index;

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

int saveUser(User tosave){
    FILE *userlist = NULL;

    if((userlist = fopen("users.txt", "a")) == NULL){
        return 0;
    }

    fprintf(userlist, "%d\t%s\t",tosave.ID, tosave.name);

    if(tosave.borrowcount){
        for(int i = 0; i < tosave.borrowcount; i++){
            fprintf(userlist, "%d", tosave.borrowedbooks[i]);
            if(i != tosave.borrowcount - 1){
                fprintf(userlist, "\t");
            }
        }
    }

    fprintf(userlist, "\n");

    fclose(userlist);

    return 1;
}

void borrowBook(){
    int tempID, tempISBN;

    printf("Enter borrowing user's ID >>");
    scanf("%d", &tempID);

    int userindex = findMe(tempID, usercount, 'u');
    int userborrows = users[userindex].borrowcount;

    if(userindex == -1){
        printf("No user with ID %d found!", tempID);
        return;
    } else if(userborrows + 1 > MAX_BORROWED){
        printf("Too many books already borrowed!");
        return;
    }

    printf("Enter book ISBN >>");
    scanf("%d", &tempISBN);

    int bookindex = findMe(tempISBN, bookcount, 'b');

    if(bookindex == -1){
        printf("No book with ISBN %d found!", tempISBN);
        return;
    } else if(books[bookindex].isborrowed){
        printf("Book with ISBN %d is already borrowed, return it before borrowing again", tempISBN);
        return;
    }

    users[userindex].borrowedbooks[users[userindex].borrowcount] = tempISBN;
    users[userindex].borrowcount++;
    books[bookindex].isborrowed = 1;

    printf("Book %d borrowed successfully!", users[userindex].borrowedbooks[userborrows]);


    deleteBookFromDisk(books[bookindex].ISBN);
    saveBook(books[bookindex]);
    deleteUserFromDisk(tempID);
    saveUser(users[userindex]);

    return;
}

void returnBook(){
    int tempID, tempISBN;

    printf("Enter borrowing user's ID >>");
    scanf("%d", &tempID);

    int userindex = findMe(tempID, usercount, 'u');
    int userborrows = users[userindex].borrowcount;

    if(userindex == -1){
        printf("No user with ID %d found!", tempID);
        return;
    } else if(userborrows + 1 > MAX_BORROWED){
        printf("No books borrowed!");
        return;
    }

    printf("Enter book ISBN >>");
    scanf("%d", &tempISBN);

    int bookindex = findMe(tempISBN, bookcount, 'b');

    if(bookindex == -1){
        printf("No book with ISBN %d found!", tempISBN);
        return;
    } else if(!books[bookindex].isborrowed){
        printf("Book with ISBN %d is not borrowed!", tempISBN);
        return;
    }

    int bookpresent = 0;
    for(int i = 0; i < users[userindex].borrowcount; i++){
        if(users[userindex].borrowedbooks[i] == tempISBN){
            bookpresent = 1;

            for (int j = i; j < users[userindex].borrowcount - 1; j++){
                users[userindex].borrowedbooks[j] = users[userindex].borrowedbooks[j + 1];
            }
            users[userindex].borrowcount--;
            break;
        }
    }

    if(!bookpresent){
        printf("User %d has no book with ISBN %d!", tempID, tempISBN);
        return;
    }

    books[bookindex].isborrowed = 0;

    deleteUserFromDisk(tempID);
    saveUser(users[userindex]);

    printf("Book %d returned successfully!", tempISBN);

}

int loadBooks(){
    FILE *catalogue = NULL;

    char linebuffer[MAX_STRING];

    Book tempbook;

    if((catalogue = fopen("catalogue.txt", "r")) == NULL){
        return 0;
    }

    books = (Book *)malloc(bookcapacity * sizeof(Book));

    if(books == NULL){
        return 0;
    }

    while(fgets(linebuffer, MAX_STRING, catalogue) && bookcount < MAX_ARRLEN){
        sscanf(linebuffer, "%d\t%49[^\t]\t%49[^\t]\t%d", &tempbook.ISBN, tempbook.title, tempbook.author, &tempbook.isborrowed);
        
        if(tempbook.ISBN == 0){continue;}

        checkAndResize('b');

        books[bookcount] = tempbook;
        bookcount++;
    }
    
    fclose(catalogue);

    return 1;
}

int loadUsers(){    
    FILE *userlist = NULL;

    char linebuffer[MAX_STRING];
    User tempuser;

    if((userlist = fopen("users.txt", "r")) == NULL){
        return 0;
    }

    users = (User *)malloc(usercapacity * sizeof(User));

    if(users == NULL){
        return 0;
    }


    while(fgets(linebuffer, MAX_STRING, userlist) && usercount < MAX_ARRLEN){
        //sscanf(linebuffer, "%d\t%[^\n]", &tempuser.ID, tempuser.name);
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
        
        checkAndResize('u');

        users[usercount] = tempuser;
        usercount++;
    }

    fclose(userlist);

    return 1;
}

int deleteUserFromDisk(int _IDtodelete){
//Handler function to delete user from file, returns 1 if user is found and deleted, 0 otherwise.
    FILE *userlist = NULL, *newuserlist = NULL;

    char linebuffer[MAX_STRING];
    int checkID, lineindex = 0, status = 0;

    if((userlist = fopen("users.txt", "r")) == NULL || (newuserlist = fopen("temp.txt", "w")) == NULL){
        return status;
    }

    while(fgets(linebuffer, MAX_STRING, userlist)){
        sscanf(linebuffer, "%d", &checkID);

        if(checkID == _IDtodelete){
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

int deleteBookFromDisk(int _IDtodelete){
//Handler function to delete book from file, returns 1 if book is found and deleted, 0 otherwise.
    FILE *catalogue = NULL, *newcatalogue = NULL;

    char linebuffer[MAX_STRING];
    int checkID, lineindex = 0, status = 0;

    if((catalogue = fopen("catalogue.txt", "r")) == NULL || (newcatalogue = fopen("temp.txt", "w")) == NULL){
        return status;
    }

    while(fgets(linebuffer, MAX_STRING, catalogue)){
        sscanf(linebuffer, "%d", &checkID);

        if(checkID == _IDtodelete){
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

void checkAndResize(char mode){
    if(mode == 'b'){

        if(bookcount + 1 == bookcapacity){
            bookcapacity *= 2;
            books = realloc(books, bookcapacity * sizeof(Book));

        } else if((float)bookcount < (1.0/4.0) * (float)bookcapacity){
            bookcapacity /= 2;
            books = realloc(books, bookcapacity * sizeof(Book));
        }

        if(books == NULL){
                exit(1);
            }

    } else{

        if(usercount + 1 == usercapacity){
            usercapacity *= 2;
            users = realloc(users, usercapacity * sizeof(User));

            
        } else if((float)usercount < (1.0/4.0) * (float)usercapacity){
            usercapacity /= 2;
            users = realloc(users, usercapacity * sizeof(User));
        }

        if(users == NULL){
                exit(1);
            }

    }
}

void freeAll(){
    free(books);
    free(users);
}

char* getTitleFromID(int id){
    return books[findMe(id, bookcount, 'b')].title;
}






