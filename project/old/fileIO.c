#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int deleteUserFromDisk(int);
int deleteBookFromDisk(int);


int main(){
    loadBooks();
    loadUsers();

    // printf("Count: %d\n", bookcount);
    // for(int i = 0; i < bookcount; i++){
    // printf("%d | %s | %s | %s\n", books[i].ISBN, books[i].title, books[i].author, books[i].isborrowed? "Yes":"No");
    // }

    deleteBookFromDisk(100020);

    return 0;

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

    fprintf(userlist, "%d\t%s\n",tosave.ID, tosave.name);

    fclose(userlist);

    return 1;
}

int loadBooks(){
    FILE *catalogue = NULL;

    char linebuffer[MAX_STRING];

    Book tempbook;

    if((catalogue = fopen("catalogue.txt", "r")) == NULL){
        return 0;
    }

    while(fgets(linebuffer, MAX_STRING, catalogue) && bookcount < MAX_ARRLEN){
        sscanf(linebuffer, "%d\t%49[^\t]\t%49[^\t]\t%d", &tempbook.ISBN, tempbook.title, tempbook.author, &tempbook.isborrowed);
        
        if(tempbook.ISBN == 0){continue;}

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

    while(fgets(linebuffer, MAX_STRING, userlist) && usercount < MAX_ARRLEN){
        sscanf(linebuffer, "%d\t%[^\n]", &tempuser.ID, tempuser.name);
        
        if(tempuser.ID == 0){continue;}

        users[usercount] = tempuser;
        usercount++;
    }

    fclose(userlist);

    return 1;
}

int deleteUserFromDisk(int _IDtodelete){
    FILE *userlist = NULL, *newuserlist = NULL;

    char linebuffer[MAX_STRING];
    int checkID, lineindex = 0;

    if((userlist = fopen("users.txt", "r")) == NULL || (newuserlist = fopen("temp.txt", "w")) == NULL){
        return 0;
    }

    while(fgets(linebuffer, MAX_STRING, userlist)){
        sscanf(linebuffer, "%d", &checkID);

        if(checkID == _IDtodelete){
            continue;
        }

        fprintf(newuserlist, "%s", linebuffer);
    }

    fclose(userlist);
    fclose(newuserlist);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    return 1;

}

int deleteBookFromDisk(int _IDtodelete){
    FILE *catalogue = NULL, *newcatalogue = NULL;

    char linebuffer[MAX_STRING];
    int checkID, lineindex = 0;

    if((catalogue = fopen("catalogue.txt", "r")) == NULL || (newcatalogue = fopen("temp.txt", "w")) == NULL){
        return 0;
    }

    while(fgets(linebuffer, MAX_STRING, catalogue)){
        sscanf(linebuffer, "%d", &checkID);

        if(checkID == _IDtodelete){
            continue;
        }

        fprintf(newcatalogue, "%s", linebuffer);
    }

    fclose(catalogue);
    fclose(newcatalogue);

    remove("catalogue.txt");
    rename("temp.txt", "catalogue.txt");

    return 1;

}