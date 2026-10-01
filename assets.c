#include <stdio.h>
#include <string.h>
#include "assets.h"

int assetID[30];
char assetName[30][50];
char assetType[30][50];
float purchaseValue[30];
char assetDepartment[30][50];
char assetCondition[30][30];

int assetCount = 0;

void assetMenu(void)
{
    int choice;

    do
    {
        printf("\n--- ASSET MANAGEMENT ---\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                addAsset();
                break;
            case 2:
                displayAssets();
                break;
            case 3:
                searchAsset();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

void addAsset(void)
{
    if (assetCount >= (int)(sizeof(assetID) / sizeof(assetID[0])))
    {
        printf("Asset storage is full.\n");
        return;
    }

    printf("\nEnter asset ID: ");
    scanf("%d", &assetID[assetCount]);
    getchar();

    printf("Enter asset name: ");
    fgets(assetName[assetCount], sizeof(assetName[assetCount]), stdin);
    assetName[assetCount][strcspn(assetName[assetCount], "\n")] = '\0';

    printf("Enter asset type: ");
    fgets(assetType[assetCount], sizeof(assetType[assetCount]), stdin);
    assetType[assetCount][strcspn(assetType[assetCount], "\n")] = '\0';

    printf("Enter purchase value: ");
    scanf("%f", &purchaseValue[assetCount]);

    while (purchaseValue[assetCount] < 0)
    {
        printf("Purchase value cannot be negative. Enter again: ");
        scanf("%f", &purchaseValue[assetCount]);
    }
    getchar();

    printf("Enter department: ");
    fgets(assetDepartment[assetCount], sizeof(assetDepartment[assetCount]), stdin);
    assetDepartment[assetCount][strcspn(assetDepartment[assetCount], "\n")] = '\0';

    printf("Enter condition: ");
    fgets(assetCondition[assetCount], sizeof(assetCondition[assetCount]), stdin);
    assetCondition[assetCount][strcspn(assetCondition[assetCount], "\n")] = '\0';

    assetCount++;
    printf("Asset added successfully.\n");
}

void displayAssets(void)
{
    int i;

    if (assetCount == 0)
    {
        printf("\nNo assets registered.\n");
        return;
    }

    printf("\n--- ASSET LIST ---\n");

    for (i = 0; i < assetCount; i++)
    {
        printf("\nAsset ID: %d\n", assetID[i]);
        printf("Name: %s\n", assetName[i]);
        printf("Type: %s\n", assetType[i]);
        printf("Purchase Value: %.2f\n", purchaseValue[i]);
        printf("Department: %s\n", assetDepartment[i]);
        printf("Condition: %s\n", assetCondition[i]);
    }
}

void searchAsset(void)
{
    char searchName[50];
    int found = 0;
    int i;

    printf("\nEnter asset name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    for (i = 0; i < assetCount; i++)
    {
        if (strcmp(searchName, assetName[i]) == 0)
        {
            printf("\nAsset found.\n");
            printf("ID: %d\n", assetID[i]);
            printf("Name: %s\n", assetName[i]);
            printf("Type: %s\n", assetType[i]);
            printf("Purchase Value: %.2f\n", purchaseValue[i]);
            printf("Department: %s\n", assetDepartment[i]);
            printf("Condition: %s\n", assetCondition[i]);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Asset not found.\n");
    }
}
