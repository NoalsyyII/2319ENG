#include <stdio.h>
#include <strings.h>

void addNote(char*);
void displayAllNotes();

FILE *master;

int main(){
    int choice;

    char newnote[32];
    while(1) {
    printf("Select an operation:\n1: Add Note\n2: Display All Notes\n3: Exit\n>>");
    
    scanf("%d", &choice);
    switch(choice){
        case 1:
            while ((getchar()) != '\n');
            printf("Enter note >>");
            fgets(newnote, 32, stdin);
            addNote(newnote);
            printf("Note added successfully!\n");
            break;
        case 2:
            displayAllNotes();
            break;
        default:
            return 0;
    }
    }


    return 0;
}

void addNote(char* note){

    if((master = fopen("notes.txt", "a")) == NULL){
        printf("Error opening file!");
        return;
    }

    fprintf(master, "%s", note);

    fclose(master);

}

void displayAllNotes(){
    char onenote[32];
    char allnotes[20][32];
    int i = 0, numnotes;

    if((master = fopen("notes.txt", "r")) == NULL){
        printf("Error opening file!");
    }

    while(fgets(onenote, 32, master) != NULL){
        sscanf(onenote, "%s %*s", allnotes[i++]);
    }
    
    fclose(master);

    numnotes = i - 1;

    for(i = 0; i < numnotes; i++){
        printf("Note %d : %s\n", i, allnotes[i]);
    }

}