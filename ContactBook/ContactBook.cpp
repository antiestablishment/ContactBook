#pragma warning(disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <tchar.h>

struct aContact {
    char contactName[64];
    char emailAddress[128];
    char phoneNumber[16];
    char homeAddress[128];
    bool isDeleted = false;
};

bool directoryExists(const char*);
char displayMenu();
void performAction(char choiceChar);
void generateFile();
void fetchContact();
void addContact();
void listAllContacts();
void clearInputBuffer();

void clearInputBuffer() {
    int i;
    while ((i = getchar()) != '\n' && i != EOF);
}

bool directoryExists(const char* absolutePath) {
    if (_access(absolutePath, 0) == 0) {
        struct stat status;
        stat(absolutePath, &status);
        return (status.st_mode & S_IFDIR) != 0;
    }
    return false;
}

char displayMenu() {
    // system("cls");
    int choiceChar;
    printf(" \n\n   Welcome to ant1terrorist's contact app!\n\n");
    printf("    Options:\n\n");
    printf("    1. Add a contact.\n\n");
    printf("    2. List all contacts.\n\n");
    printf("    3. View a specific contact.\n\n");
    printf("    4. Edit a contact.\n\n");
    printf("    5. Delete a contact.\n\n");
    printf("    6. Export a contact to a text file.\n\n");
    printf("    Press Q to Exit\n\n");
    choiceChar = getchar();
    clearInputBuffer();
    return(choiceChar);
}

void performAction(char choiceChar) {
    switch (choiceChar) {
    case('1'):
        system("cls");
        addContact();
        choiceChar = ' ';
        break;
    case('2'):
        system("cls");
        listAllContacts();
        choiceChar = ' ';
        break;
    case('3'):
        system("cls");
        fetchContact();
        choiceChar = ' ';
        break;
    case('Q'):
        printf("\n\n    Exiting...");
        exit(0);
    case('q'):
        printf("\n\n    Exiting...");
        exit(0);
    }
}


void generateFile() {
    FILE* contactFile = fopen("contacts.bin", "ab");
    if (contactFile == NULL) {
        fprintf(stderr, "\nError opening file.\n");
    }
    fclose(contactFile);
}

void fetchContact() {
    char searchName[64];
    printf("\n\n");
    printf("    First name of who would you like to search for: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    FILE* contactFile = fopen("contacts.bin", "rb");
    if (contactFile == NULL) {
        fprintf(stderr, "\nError opening file.\n");
    }
    struct aContact fetchedContact {};
    while (fread(&fetchedContact, sizeof(fetchedContact), 1, contactFile)) {
        if (strcmp(fetchedContact.contactName, searchName) == 0) {
            if (fetchedContact.isDeleted == false) {
                printf("\n\n");
                printf("    Contact Name: %s\n", fetchedContact.contactName);
                printf("    Contact Email: %s\n", fetchedContact.emailAddress);
                printf("    Contact Phone Number: %s\n", fetchedContact.phoneNumber);
                printf("    Contact Home Address: %s\n", fetchedContact.homeAddress);
            }
        }
        else {
             printf("\n\n    No such contact. Try again.");
        }
    }
    fclose(contactFile);
 }


void addContact() {
    struct aContact newContact {};
    char firstName[32] = {};
    char lastName[32] = {};
    printf("    Please enter the name of the contact: ");
    fgets(newContact.contactName, sizeof(newContact.contactName), stdin);
    newContact.contactName[strcspn(newContact.contactName, "\n")] = '\0';
    printf("\n");
    printf("    Please enter the email address of the contact: ");
    fgets(newContact.emailAddress, sizeof(newContact.emailAddress), stdin);
    newContact.emailAddress[strcspn(newContact.emailAddress, "\n")] = '\0';
    printf("\n");
    printf("    Please enter the phone number of the contact: ");
    fgets(newContact.phoneNumber, sizeof(newContact.phoneNumber), stdin);
    newContact.phoneNumber[strcspn(newContact.phoneNumber, "\n")] = '\0';
    printf("\n");
    printf("    Please enter the home address of the contact: ");
    fgets(newContact.homeAddress, sizeof(newContact.homeAddress), stdin);
    newContact.homeAddress[strcspn(newContact.homeAddress, "\n")] = '\0';
    printf("\n");
    FILE* contactFile;
    contactFile = fopen("contacts.bin", "ab");
    if (contactFile == NULL) {
        fprintf(stderr, "\nError opening file.\n");
    }
    fwrite(&newContact, sizeof(newContact), 1, contactFile);
    fclose(contactFile);
    
}

void listAllContacts() {
    FILE* contactFile;
    contactFile = fopen("contacts.bin", "rb");
    if (contactFile == NULL) {
        fprintf(stderr, "\nError opening file.\n");
    }
    struct aContact listedContact {};
    printf("\n\n");
    while (fread(&listedContact, sizeof(listedContact), 1, contactFile)) {
        printf("    Contact: %s\n", listedContact.contactName);
    }
    fclose(contactFile);
}

int main()
{  
    generateFile();
    while (1) {
        char cmdChoice = displayMenu();
        performAction(cmdChoice);
        printf("\n\n    Press ENTER to go back to the menu");
        clearInputBuffer();
        getchar();
    }
  
    return 0;
}
