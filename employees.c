#include <stdio.h>
#include <string.h>
#include "employees.h"

int employeeID[50];
char employeeName[50][50];
char employeeDepartment[50][50];
float basicSalary[50];
float housingAllowance[50];
float transportAllowance[50];
float otherAllowance[50];

int employeeCount = 0;

void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n--- EMPLOYEE MANAGEMENT ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

void addEmployee(void)
{
    if (employeeCount >= (int)(sizeof(employeeID) / sizeof(employeeID[0])))
    {
        printf("Employee storage is full.\n");
        return;
    }

    printf("\nEnter employee ID: ");
    scanf("%d", &employeeID[employeeCount]);
    getchar();

    printf("Enter employee name: ");
    fgets(employeeName[employeeCount], sizeof(employeeName[employeeCount]), stdin);
    employeeName[employeeCount][strcspn(employeeName[employeeCount], "\n")] = '\0';

    printf("Enter department: ");
    fgets(employeeDepartment[employeeCount], sizeof(employeeDepartment[employeeCount]), stdin);
    employeeDepartment[employeeCount][strcspn(employeeDepartment[employeeCount], "\n")] = '\0';

    printf("Enter basic salary: ");
    scanf("%f", &basicSalary[employeeCount]);

    while (basicSalary[employeeCount] < 0)
    {
        printf("Salary cannot be negative. Enter again: ");
        scanf("%f", &basicSalary[employeeCount]);
    }

    printf("Enter housing allowance: ");
    scanf("%f", &housingAllowance[employeeCount]);

    printf("Enter transport allowance: ");
    scanf("%f", &transportAllowance[employeeCount]);

    printf("Enter other allowance: ");
    scanf("%f", &otherAllowance[employeeCount]);
    getchar();

    if (housingAllowance[employeeCount] < 0 ||
        transportAllowance[employeeCount] < 0 ||
        otherAllowance[employeeCount] < 0)
    {
        printf("Allowances cannot be negative. Employee was not added.\n");
        return;
    }

    employeeCount++;
    printf("Employee added successfully.\n");
}

void displayEmployees(void)
{
    int i;

    if (employeeCount == 0)
    {
        printf("\nNo employees registered.\n");
        return;
    }

    printf("\n--- EMPLOYEE LIST ---\n");

    for (i = 0; i < employeeCount; i++)
    {
        printf("\nEmployee ID: %d\n", employeeID[i]);
        printf("Name: %s\n", employeeName[i]);
        printf("Department: %s\n", employeeDepartment[i]);
        printf("Basic Salary: %.2f\n", basicSalary[i]);
        printf("Housing Allowance: %.2f\n", housingAllowance[i]);
        printf("Transport Allowance: %.2f\n", transportAllowance[i]);
        printf("Other Allowance: %.2f\n", otherAllowance[i]);
        printf("Total Salary: %.2f\n", calculateSalary(basicSalary[i], housingAllowance[i], transportAllowance[i], otherAllowance[i]));
    }
}

void searchEmployee(void)
{
    char searchName[50];
    int found = 0;
    int i;

    printf("\nEnter employee name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    for (i = 0; i < employeeCount; i++)
    {
        if (strcmp(searchName, employeeName[i]) == 0)
        {
            printf("\nEmployee found.\n");
            printf("ID: %d\n", employeeID[i]);
            printf("Name: %s\n", employeeName[i]);
            printf("Department: %s\n", employeeDepartment[i]);
            printf("Total Salary: %.2f\n", calculateSalary(basicSalary[i], housingAllowance[i], transportAllowance[i], otherAllowance[i]));
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Employee not found.\n");
    }
}

float calculateSalary(float basic, float housing, float transport, float other)
{
    return basic + housing + transport + other;
}

int getEmployeeCount(void)
{
    return employeeCount;
}

float getAverageSalary(void)
{
    float total = 0;
    int i;

    if (employeeCount == 0)
    {
        return 0;
    }

    for (i = 0; i < employeeCount; i++)
    {
        total = total + calculateSalary(basicSalary[i], housingAllowance[i], transportAllowance[i], otherAllowance[i]);
    }

    return total / employeeCount;
}

float getHighestSalary(void)
{
    float highest;
    float salary;
    int i;

    if (employeeCount == 0)
    {
        return 0;
    }

    highest = calculateSalary(basicSalary[0], housingAllowance[0], transportAllowance[0], otherAllowance[0]);

    for (i = 1; i < employeeCount; i++)
    {
        salary = calculateSalary(basicSalary[i], housingAllowance[i], transportAllowance[i], otherAllowance[i]);

        if (salary > highest)
        {
            highest = salary;
        }
    }

    return highest;
}

float getLowestSalary(void)
{
    float lowest;
    float salary;
    int i;

    if (employeeCount == 0)
    {
        return 0;
    }

    lowest = calculateSalary(basicSalary[0], housingAllowance[0], transportAllowance[0], otherAllowance[0]);

    for (i = 1; i < employeeCount; i++)
    {
        salary = calculateSalary(basicSalary[i], housingAllowance[i], transportAllowance[i], otherAllowance[i]);

        if (salary < lowest)
        {
            lowest = salary;
        }
    }

    return lowest;
}
