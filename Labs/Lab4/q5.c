#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_STUDENTS 50
#define MAX_STRING 100

int studentcount = 0, ids[MAX_STUDENTS];

char grades[MAX_STUDENTS], names[MAX_STUDENTS][MAX_STRING];

void addStudent();
void displayAllStudents();
void searchByID(int);

int main(){

    printf("Welcome to the student management system! Make a selection below:\n");

    int choice, searchID;

    while(1){

    printf("MAIN MENU\n1: Add student\n2: Display all student records\n3: Search student by ID\n4: Exit\n>>");

    scanf("%d", &choice);

    if(choice == 1){
        addStudent();
    } else if(choice == 2){
        displayAllStudents();
    } else if(choice == 3){
        printf("Enter student ID >>");
        scanf("%d", &searchID);
        searchByID(searchID);
    } else{
        break;
    }
    }
    return 0;
}

void addStudent(){
    system("cls");
    int tempID;
    char tempname[MAX_STRING];
    char tempgrade;

    printf("Enter Student ID >>");
    scanf(" %d", &tempID);

    while ((getchar()) != '\n'); // clear input buffer

    printf("Enter Student Name >>");
    fgets(tempname, MAX_STRING - 1, stdin);
    
    tempname[strcspn(tempname, "\n")] = 0; //cuts off newline char

    printf("Enter Student Grade >>");
    scanf(" %c", &tempgrade); // no need to clear buffer here

    ids[studentcount] = tempID;
    strcpy(names[studentcount], tempname);
    grades[studentcount] = tempgrade;

    printf("%s added sucessfully!\n", tempname);

    studentcount++;
    
}

void displayAllStudents(){
    system("cls");

    if(!studentcount){
        printf("ERROR: No records to display!\n");
        return;
    }

    for(int i = 0; i < studentcount; i++){
        printf("Name: %s | ID: %d | Grade: %c\n", names[i], ids[i], grades[i]);
    }
    
    return;
}

void searchByID(int _id){

    for(int i = 0; i < studentcount; i++){
        if(ids[i] == _id){
            printf("Student found:\n");
            printf("Name: %s | ID: %d | Grade: %c\n", names[i], ids[i], grades[i]);
            return;
        }
    }

    printf("No student with ID %d found :(, try again\n", _id);
    return;
}