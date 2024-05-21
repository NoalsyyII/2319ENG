#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100

typedef struct contact{
    char name[MAX_STRING];
    char phone[MAX_STRING];
    char email[MAX_STRING];

    struct contact* next; //ptr to next node

} Contact;

Contact* createNewContact(char*, char*, char*);
void addContactToList(Contact**);
void deleteContact(Contact**);
void searchContact(Contact*);
void displayAllContacts(Contact*);
void freeContacts(Contact*);
Contact* findInList(Contact*, char*, Contact**);

int main(){
    Contact* head = NULL;
    int loopflag = 1, choice;

    while(loopflag){
        printf("\nMAIN MENU\n1: Add Contact\n2: Delete Contact\n3: Search by name\n4: Display all contacts\n5: Exit\n>>");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                addContactToList(&head);
                break;
            case 2:
                deleteContact(&head);
                break;
            case 3:
                searchContact(head);
                break;
            case 4:
                displayAllContacts(head);
                break;
            default:
                loopflag = 0;
                break;

        }
    }
    freeContacts(head);
}

Contact* createNewContact(char* name, char* phone, char* email){
    Contact* newcontact = (Contact*)malloc((sizeof(Contact)));
    
    strcpy(newcontact->name, name);
    strcpy(newcontact->phone, phone);
    strcpy(newcontact->email, email);
    newcontact->next = NULL;

    return newcontact;
}

void addContactToList(Contact** headptr){
    char tempname[MAX_STRING], tempphone[MAX_STRING], tempemail[MAX_STRING];

    while((getchar() != '\n'));

    printf("Enter name >>");
    fgets(tempname, MAX_STRING - 1, stdin);
    tempname[strcspn(tempname, "\n")] = 0;

    printf("Enter phone >>");
    fgets(tempphone, MAX_STRING - 1, stdin);
    tempphone[strcspn(tempphone, "\n")] = 0;

    printf("Enter email >>");
    fgets(tempemail, MAX_STRING - 1, stdin);
    tempphone[strcspn(tempphone, "\n")] = 0;

    Contact* newcontact = createNewContact(tempname, tempphone, tempemail);

    if(*headptr == NULL){
        *headptr = newcontact;
        return;
    }

    Contact* current = *headptr;
    Contact* prev = NULL;

    while(current != NULL){
        prev = current;
        current = current->next;
    }

    prev->next = newcontact;
    newcontact->next = NULL;

}

Contact* findInList(Contact* head, char* targetname, Contact** prev){
    Contact* current = head;
    *prev = NULL;

    while(current != NULL){
        if(!strcmp(current->name, targetname)){
            return current;
        }
        *prev = current;
        current = current->next;
    }

    return NULL;

}

void deleteContact(Contact** head){
    char tempname[MAX_STRING];

    while((getchar() != '\n'));

    printf("Enter name to delete >>");
    fgets(tempname, MAX_STRING - 1, stdin);
    tempname[strcspn(tempname, "\n")] = 0;

    Contact* prev = NULL;

    Contact* todelete = findInList(*head, tempname, &prev);

    if(todelete == NULL){
        printf("Contact not found!");
        return;
    }

    if(prev == NULL){
        *head = todelete->next;
    }else{
        prev->next = todelete->next;
    }

    free(todelete);
    printf("Contact deleted successfully!\n");

}

void searchContact(Contact* head){
    char tempname[MAX_STRING];

    while((getchar() != '\n'));

    printf("Enter name to search >>");
    fgets(tempname, MAX_STRING - 1, stdin);
    tempname[strcspn(tempname, "\n")] = 0;

    Contact* found = findInList(head, tempname, NULL);

    if(found == NULL){
        printf("Contact not found!");
        return;
    }

    printf("Contact found:\nName: %-30s | Phone: %-15s | Email: %-20s\n", found->name, found->phone, found->email);

    return;
}

void displayAllContacts(Contact* head){
    Contact* current = head;

    while(current != NULL){
        printf("Name: %-20s | Phone: %-15s | Email: %-20s", current->name, current->phone, current->email);
        current = current->next;
    }
    
}

void freeContacts(Contact* head){
    Contact* current = head;
    Contact* next = NULL;

    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }

}
