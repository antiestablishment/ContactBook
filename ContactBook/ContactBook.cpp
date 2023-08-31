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
};

bool directoryExists(const char*);
char displayMenu();
void performAction(char choiceChar);
void generateFile();
void fetchContact();
void addContact();
void listAllContacts();
void clearInputBuffer();
void editContact();
void deleteContact();
void exportContact();

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
    system("cls");
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
    case('4'):
        system("cls");
        editContact();
        choiceChar = ' ';
        break;
    case('5'):
        system("cls");
        deleteContact();
        choiceChar = ' ';
        break;
    case('6'):
        system("cls");
        exportContact();
        choiceChar = ' ';
        break;
    case('Q'):
    case('q'):
        printf("\n\n    Exiting...");
        exit(0);
    }
}


void generateFile() {
    FILE* contactFile = fopen("contacts.bin", "ab");
    if (contactFile == NULL) {
        fprintf(stderr, "\nError opening file.\n");
        printf("\n\n    Could not open a file or generate one.");
        printf("\n    Make sure a file exists and isn't broken.");
        printf("\n\n    Closing program...");
        exit(0);
    }
    fclose(contactFile);
}

void fetchContact() {
    char searchName[64];
    printf("\n\n    Please enter the name of the contact you would like to see:  ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    FILE* contactFile = fopen("contacts.bin", "rb");
    if (contactFile == NULL) {
        fprintf(stderr, "\nError opening file.\n");
        return;
    }
    struct aContact fetchedContact {};
    while (fread(&fetchedContact, sizeof(fetchedContact), 1, contactFile)) {
        if (strcmp(fetchedContact.contactName, searchName) == 0) {
            printf("\n\n");
            printf("    Contact Name: %s\n", fetchedContact.contactName);
            printf("    Contact Email: %s\n", fetchedContact.emailAddress);
            printf("    Contact Phone Number: %s\n", fetchedContact.phoneNumber);
            printf("    Contact Home Address: %s\n", fetchedContact.homeAddress);
            break;
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
    printf("\n\n    Please enter the name of the contact:  ");
    fgets(newContact.contactName, sizeof(newContact.contactName), stdin);
    newContact.contactName[strcspn(newContact.contactName, "\n")] = '\0';
    printf("\n");
    printf("    Please enter the email address of the contact:  ");
    fgets(newContact.emailAddress, sizeof(newContact.emailAddress), stdin);
    newContact.emailAddress[strcspn(newContact.emailAddress, "\n")] = '\0';
    printf("\n");
    printf("    Please enter the phone number of the contact:  ");
    fgets(newContact.phoneNumber, sizeof(newContact.phoneNumber), stdin);
    newContact.phoneNumber[strcspn(newContact.phoneNumber, "\n")] = '\0';
    printf("\n");
    printf("    Please enter the home address of the contact:  ");
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
        return;
    }

    struct aContact listedContact {};
    printf("\n\n");
    while (fread(&listedContact, sizeof(listedContact), 1, contactFile)) {
            printf("    Contact: %s\n", listedContact.contactName);
    }
    fclose(contactFile);
}

void editContact() {
    FILE* contactFile;
    contactFile = fopen("contacts.bin", "rb+");
    if (contactFile == NULL) {
        fprintf(stderr, "\nError opening file.\n");
        return;
    }

    struct aContact toEdit {};
    bool foundContact = false;
    char contactID[64];
    printf("\n\n    Enter the name of the contact you would like to edit:  ");
    fgets(contactID, sizeof(contactID), stdin);
    contactID[strcspn(contactID, "\n")] = '\0';

    while (fread(&toEdit, sizeof(toEdit), 1, contactFile)) {
        if (strcmp(toEdit.contactName, contactID) == 0) {
            foundContact = true;
            printf("\n\n  Contact Found!\n");
            printf("\n  Editing contact: %s\n", contactID);
            printf("\n\n  Enter the new contact name (re-enter the current one if it hasn't changed):  ");
            fgets(toEdit.contactName, sizeof(toEdit.contactName), stdin);
            toEdit.contactName[strcspn(toEdit.contactName, "\n")] = '\0';
            printf("\n    Contact Name Successfully edited!");
            printf("\n\n    Enter the new contact email (re-enter the current one if it hasn't changed):  ");
            fgets(toEdit.emailAddress, sizeof(toEdit.emailAddress), stdin);
            toEdit.emailAddress[strcspn(toEdit.emailAddress, "\n")] = '\0';
            printf("\n    Contact Email Address Successfully edited!");
            printf("\n\n    Enter the new contact phone number (re-enter the current one if it hasn't changed):  ");
            fgets(toEdit.phoneNumber, sizeof(toEdit.phoneNumber), stdin);
            toEdit.phoneNumber[strcspn(toEdit.phoneNumber, "\n")] = '\0';
            printf("\n    Contact Phone Number Successfully edited!");
            printf("\n\n    Enter the new contact home address (re-enter the current one if it hasn't changed):  ");
            fgets(toEdit.homeAddress, sizeof(toEdit.homeAddress), stdin);
            toEdit.homeAddress[strcspn(toEdit.homeAddress, "\n")] = '\0';
            printf("\n    Contact Home Address Successfully edited!");
            fseek(contactFile, -(long)sizeof(toEdit), SEEK_CUR);
            fwrite(&toEdit, sizeof(toEdit), 1, contactFile);
            printf("\n\n    Contact edit saved successfully!");
            break;
        }
    }
    if (!foundContact) {
        printf("\n  Contact Not Found.");
    }
    fclose(contactFile);
}

void deleteContact() {
    FILE* contactFile;
    contactFile = fopen("contacts.bin", "rb");
    if (contactFile == NULL) {
        fprintf(stderr, "\nError opening the contact file.\n");
        return;
    }

    FILE* tempFile;
    tempFile = fopen("contactTempStore.bin", "wb");
    if (tempFile == NULL) {
        fprintf(stderr, "\nError opening temporary contact storage file.\n");
        return;
    }

    struct aContact tempStruct {};
    bool foundContact = false;
    char contactID[64];
    char decisionCheck[3] = {};
    const char* fileContacts = "contacts.bin";
    const char* fileTemp = "contactTempStore.bin";

    printf("\n\n    Enter the name of the contact you would like to delete:  ");
    fgets(contactID, sizeof(contactID), stdin);
    clearInputBuffer();
    contactID[strcspn(contactID, "\n")] = '\0';


    while (fread(&tempStruct, sizeof(aContact), 1, contactFile)) {
        if (strcmp(tempStruct.contactName, contactID) != 0) {
            fwrite(&tempStruct, sizeof(aContact), 1, tempFile);
        }
    }
    printf("\n\n    Ready to delete %s...", contactID);
    fclose(contactFile);
    fclose(tempFile);

    if (remove(fileContacts) == 0) {
        if (rename(fileTemp, fileContacts) == 0) {
            printf("\n\n    Contact %s has been deleted!", contactID);
        }
        else {
            fprintf(stderr, "\nError renaming the temporary contact storage file.\n");
        }
    }
    else {
        fprintf(stderr, "\nError deleting the original contact storage file.\n");
    }
}

void exportContact() {
    char contactID[64];
    bool foundContact = false;

    FILE* contactFile;
    contactFile = fopen("contacts.bin", "rb+");
    if (contactFile == NULL) {
        fprintf(stderr, "\nError opening contacts.bin for reading.\n");
        return;
    }

    FILE* exportDest;
    exportDest = fopen("exportedContact.txt", "w");
    if (exportDest == NULL) {
        fprintf(stderr, "\nError opening exportedContact.txt for writing.\n");
        return;
    }

    struct aContact toExport {};

    printf("\n\n    Enter the name of the contact you would like to export:  ");
    fgets(contactID, sizeof(contactID), stdin);
    contactID[strcspn(contactID, "\n")] = '\0';
    while (fread(&toExport, sizeof(toExport), 1, contactFile)) {
        if (strcmp(toExport.contactName, contactID) == 0) {
            foundContact = true;
            printf("\n\n    Contact found! \n");
            printf("\n\n    Exporting contact to text file now... \n");
            fprintf(exportDest, "\n\n  -- Contact Exported from ant1terrorists CLI contact book --\n\n");
            fprintf(exportDest, "       Contact name: %s\n", toExport.contactName);
            fprintf(exportDest, "       Contact name: %s\n", toExport.contactName);
            fprintf(exportDest, "       Contact name: %s\n", toExport.contactName);
            fprintf(exportDest, "       Contact name: %s\n", toExport.contactName);
        }
    }
    if (!foundContact) {
        printf("\n\n    Contact not found.");
    }
    else {
        printf("\n\n    Contact exported succesfully!");
    }

    fclose(contactFile);
    fclose(exportDest);
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
