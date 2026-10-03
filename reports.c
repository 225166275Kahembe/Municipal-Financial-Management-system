#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void reportsMenu(void)
{
    int choice;

    do
    {
        printf("\n--- REPORTS ---\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                printf("\n--- EMPLOYEE REPORT ---\n");
                printf("Number of employees: %d\n", getEmployeeCount());
                printf("Average salary: %.2f\n", getAverageSalary());
                printf("Highest salary: %.2f\n", getHighestSalary());
                printf("Lowest salary: %.2f\n", getLowestSalary());
                break;

            case 2:
                printf("\n--- BUDGET REPORT ---\n");
                printf("Total allocated: %.2f\n", getTotalAllocated());
                printf("Total expenditure: %.2f\n", getTotalExpenditure());
                printf("Remaining budget: %.2f\n", getRemainingBudget());
                if (getRemainingBudget() < 0)
                {
                    printf("Status: Budget exceeded\n");
                }
                else
                {
                    printf("Status: Within budget\n");
                }
                break;

            case 3:
                displaySuppliers();
                break;

            case 4:
                displayAssets();
                break;

            case 5:
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);
}
