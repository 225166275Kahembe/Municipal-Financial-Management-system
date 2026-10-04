#include <stdio.h>
#include <string.h>
#include "budget.h"

char budgetDepartment[10][50];
float allocatedBudget[10];
float expenditure[10];
int budgetCount = 0;

void budgetMenu(void)
{
    int choice;

    do
    {
     printf("\n--- BUDGET MANAGEMENT ---\n");
        printf("1. Add Department Budget\n");
        printf("2. Display Budgets\n");
        printf("3. Identify Exceeded Budgets\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                addBudget();
                break;
            case 2:
                displayBudgets();
                break;
            case 3:
                identifyExceededBudgets(); 
                break;
            case 4:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4); 
}

void addBudget(void)
{
    if (budgetCount >= (int)(sizeof(budgetDepartment) / sizeof(budgetDepartment[0])))
    {
        printf("Budget storage is full.\n");
        return;
    }

    printf("\nEnter department name: ");
    fgets(budgetDepartment[budgetCount], sizeof(budgetDepartment[budgetCount]), stdin);
    budgetDepartment[budgetCount][strcspn(budgetDepartment[budgetCount], "\n")] = '\0';

    printf("Enter allocated budget: ");
    scanf("%f", &allocatedBudget[budgetCount]);

    while (allocatedBudget[budgetCount] < 0)
    {
        printf("Budget cannot be negative. Enter again: ");
        scanf("%f", &allocatedBudget[budgetCount]);
    }

    printf("Enter expenditure: ");
    scanf("%f", &expenditure[budgetCount]);

    while (expenditure[budgetCount] < 0)
    {
        printf("Expenditure cannot be negative. Enter again: ");
        scanf("%f", &expenditure[budgetCount]);
    }

    budgetCount++;
    getchar();
    printf("Budget added successfully.\n");
}

void displayBudgets(void)
{
    int i;
    float remaining;

    if (budgetCount == 0)
    {
        printf("\nNo budgets registered.\n");
        return;
    }

    printf("\n--- DEPARTMENT BUDGETS ---\n");

    for (i = 0; i < budgetCount; i++)
    {
        remaining = calculateBudget(allocatedBudget[i], expenditure[i]);

        printf("\nDepartment: %s\n", budgetDepartment[i]);
        printf("Allocated: %.2f\n", allocatedBudget[i]);
        printf("Expenditure: %.2f\n", expenditure[i]);
        printf("Remaining: %.2f\n", remaining);

        if (expenditure[i] > allocatedBudget[i])
        {
            printf("Status: Budget exceeded\n");
        }
        else
        {
            printf("Status: Within budget\n");
        }
    }
}

float calculateBudget(float allocated, float expenditureAmount)
{
    return allocated - expenditureAmount;
}

float getTotalAllocated(void)
{
    float total = 0;
    int i;

    for (i = 0; i < budgetCount; i++)
    {
        total = total + allocatedBudget[i];
    }

    return total;
}

float getTotalExpenditure(void)
{
    float total = 0;
    int i;

    for (i = 0; i < budgetCount; i++)
    {
        total = total + expenditure[i];
    }

    return total;
}

float getRemainingBudget(void)
{
    return getTotalAllocated() - getTotalExpenditure();
}
void identifyExceededBudgets(void)
{
    int i;
    int found = 0;

    if (budgetCount == 0)
    {
        printf("\nNo budgets registered.\n");
        return;
    }

    printf("\n--- DEPARTMENTS EXCEEDING BUDGET ---\n");

    for (i = 0; i < budgetCount; i++)
    {
        if (expenditure[i] > allocatedBudget[i])
        {
            float deficit = expenditure[i] - allocatedBudget[i];
            printf("Department: %s\n", budgetDepartment[i]);
            printf("Exceeded by: %.2f\n\n", deficit);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Excellent! No departments have exceeded their budget.\n");
    }
}
