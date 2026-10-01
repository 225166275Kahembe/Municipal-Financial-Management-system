#include <stdio.h>
#include <string.h>
#include "suppliers.h"

int supplierID[20];
char supplierName[20][100];
char supplierEmail[20][100];
char supplierPhone[20][30];
char supplierTown[20][50];

int supplierCount = 0;

void supplierMenu(void)
{
    int choice;

    do
    {
        printf("\n--- SUPPLIER MANAGEMENT ---\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                addSupplier();
                break;
            case 2:
                displaySuppliers();
                break;
            case 3:
                searchSupplier();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

void addSupplier(void)
{
    if (supplierCount >= (int)(sizeof(supplierID) / sizeof(supplierID[0])))
    {
        printf("Supplier storage is full.\n");
        return;
    }

    printf("\nEnter supplier ID: ");
    scanf("%d", &supplierID[supplierCount]);
    getchar();

    printf("Enter supplier name: ");
    fgets(supplierName[supplierCount], sizeof(supplierName[supplierCount]), stdin);
    supplierName[supplierCount][strcspn(supplierName[supplierCount], "\n")] = '\0';

    printf("Enter email: ");
    fgets(supplierEmail[supplierCount], sizeof(supplierEmail[supplierCount]), stdin);
    supplierEmail[supplierCount][strcspn(supplierEmail[supplierCount], "\n")] = '\0';

    printf("Enter telephone number: ");
    fgets(supplierPhone[supplierCount], sizeof(supplierPhone[supplierCount]), stdin);
    supplierPhone[supplierCount][strcspn(supplierPhone[supplierCount], "\n")] = '\0';

    printf("Enter town/location: ");
    fgets(supplierTown[supplierCount], sizeof(supplierTown[supplierCount]), stdin);
    supplierTown[supplierCount][strcspn(supplierTown[supplierCount], "\n")] = '\0';

    supplierCount++;
    printf("Supplier added successfully.\n");
}

void displaySuppliers(void)
{
    int i;
    char supplierDetails[200];

    if (supplierCount == 0)
    {
        printf("\nNo suppliers registered.\n");
        return;
    }

    printf("\n--- SUPPLIER LIST ---\n");

    for (i = 0; i < supplierCount; i++)
    {
        strcpy(supplierDetails, supplierName[i]);
        strcat(supplierDetails, " - ");
        strcat(supplierDetails, supplierTown[i]);

        printf("\nSupplier ID: %d\n", supplierID[i]);
        printf("Name: %s\n", supplierName[i]);
        printf("Email: %s\n", supplierEmail[i]);
        printf("Telephone: %s\n", supplierPhone[i]);
        printf("Town: %s\n", supplierTown[i]);
        printf("Supplier details: %s\n", supplierDetails);
        printf("Name length: %lu\n", (unsigned long)strlen(supplierName[i]));
    }
}

void searchSupplier(void)
{
    char searchName[100];
    int found = 0;
    int i;

    printf("\nEnter supplier name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    for (i = 0; i < supplierCount; i++)
    {
        if (strcmp(searchName, supplierName[i]) == 0)
        {
            printf("\nSupplier found.\n");
            printf("ID: %d\n", supplierID[i]);
            printf("Name: %s\n", supplierName[i]);
            printf("Email: %s\n", supplierEmail[i]);
            printf("Telephone: %s\n", supplierPhone[i]);
            printf("Town: %s\n", supplierTown[i]);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Supplier not found.\n");
    }
}
