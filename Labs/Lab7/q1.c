#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_STRING 32

typedef struct employee{
    int empID;
    char name[MAX_STRING];
    char department[MAX_STRING];
    float salary;
} Employee;

void addEmployee();
void displayAllEmployees();

int employeeamount = 0;
Employee records[MAX_STRING];

int main(){

    int choice;

    while(1) {
    printf("Select an operation:\n1: Add Employee\n2: Display All Employees\n3: Exit\n>>");
    
    scanf("%d", &choice);

    switch(choice){
        case 1:
            addEmployee();
            break;
        case 2:
            displayAllEmployees();
            break;
        default:
            return 0;
    }
    }

    return 0;
}

void addEmployee(){
    int tempID;
    char tempname[MAX_STRING], tempdept[MAX_STRING];
    float tempsalary;

    printf("Enter Employee ID >>");
    scanf("%d", &tempID);

    while ((getchar()) != '\n');

    printf("Enter Employee Name >>");
    fgets(tempname, MAX_STRING, stdin);
    tempname[strcspn(tempname, "\n")] = 0;

    printf("Enter Employee Department >>");
    fgets(tempdept, MAX_STRING, stdin);
    tempdept[strcspn(tempdept, "\n")] = 0;

    printf("Enter Employee Salary >>");
    scanf(" %f", &tempsalary);

    records[employeeamount].empID = tempID;
    records[employeeamount].salary = tempsalary;
    strcpy(records[employeeamount].name, tempname);
    strcpy(records[employeeamount].department, tempdept);

    employeeamount++;

}

void displayAllEmployees(){
    if(!employeeamount){
        printf("ERROR: No records to display!\n");
        return;
    }

    for(int i = 0; i < employeeamount; i++){
        Employee current = records[i];
        printf("ID: %d | Name: %s | Department: %s | Salary: %.2f\n", current.empID, current.name, current.department, current.salary);
    }
    
    return;
}