#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void makeContactDirectory() {
    // Runs first to:
        // 1. Check to see if a directory exists.
        // 2. If not, make one.
}

void addContact() {


    char first_Name[128];
    char last_Name[128];
    char email_Address[256];
    char phone_Number[20];
    char home_Address[256];
    char whole_Name[257];

    printf("Please enter the first name of the contact: ");
    scanf_s("%s", first_Name, 128);
    printf("\n");

    printf("Please enter the last name of the contact: ");
    scanf_s("%s", last_Name, 128);
    printf("\n");

    printf("Please enter the email address of the contact: ");
    scanf_s("%s", email_Address, 256);
    printf("\n");

    printf("Please enter the phone number of the contact: ");
    scanf_s("%s", phone_Number, 20);
    printf("\n");

    printf("Please enter the home address of the contact: ");
    scanf_s("%s", home_Address, 256);
    printf("\n");

    strcat_s(whole_Name, last_Name);
    strcat_s(whole_Name, first_Name);
    char buffer[257];
    snprintf(buffer, sizeof(buffer), "%s.txt", whole_Name);

    FILE* contact_File;
    fopen_s(&contact_File, buffer, "w+");
    if (contact_File == NULL) {
        fprintf(contact_File, "First Name: %s\n", first_Name);
        fprintf(contact_File, "Last Name: %s\n", last_Name);
        fprintf(contact_File, "Email Address: %s\n", email_Address);
        fprintf(contact_File, "Phone Number: %s\n", phone_Number);
        fprintf(contact_File, "Home Address: %s\n", home_Address);
    }

}

int main()
{
    addContact();
}
