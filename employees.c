#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "employees.h"

#define MAX_AMOUNT 10000000.0f

static int empId[MAX_EMPLOYEES];
static char empName[MAX_EMPLOYEES][NAME_LEN];
static char empDept[MAX_EMPLOYEES][DEPT_LEN];
static char empPosition[MAX_EMPLOYEES][POSITION_LEN];
static float empBasic[MAX_EMPLOYEES];
static float empHousing[MAX_EMPLOYEES];
static float empTransport[MAX_EMPLOYEES];
static float empOther[MAX_EMPLOYEES];
static int employeeCount = 0;

static void clearBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

static int isBlank(const char text[])
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isspace((unsigned char)text[i]))
        {
            return 0;
        }
    }
    return 1;
}

static void readText(const char prompt[], char text[], int size)
{
    int valid = 0;

    while (!valid)
    {
        printf("%s", prompt);

        if (fgets(text, size, stdin) == NULL)
        {
            exit(1);
        }

        if (text[strcspn(text, "\n")] == '\0')
        {
            clearBuffer();
        }
        text[strcspn(text, "\n")] = '\0';

        if (isBlank(text))
        {
            printf("Error: this field cannot be empty.\n");
        }
        else
        {
            valid = 1;
        }
    }
}

static int readInt(const char prompt[], int min, int max)
{
    int value = 0;
    int result;
    int valid = 0;

    while (!valid)
    {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result == EOF)
        {
            exit(1);
        }

        if (result != 1)
        {
            printf("Error: please enter a whole number.\n");
        }
        else if (value < min || value > max)
        {
            printf("Error: enter a number between %d and %d.\n", min, max);
        }
        else
        {
            valid = 1;
        }

        clearBuffer();
    }

    return value;
}

static float readAmount(const char prompt[], int allowZero)
{
    float value = 0;
    int result;
    int valid = 0;

    while (!valid)
    {
        printf("%s", prompt);
        result = scanf("%f", &value);

        if (result == EOF)
        {
            exit(1);
        }

        if (result != 1)
        {
            printf("Error: please enter a valid number.\n");
        }
        else if (value < 0)
        {
            printf("Error: the amount cannot be negative.\n");
        }
        else if (value == 0 && allowZero == 0)
        {
            printf("Error: the amount must be greater than 0.\n");
        }
        else if (value > MAX_AMOUNT)
        {
            printf("Error: the amount is too large.\n");
        }
        else
        {
            valid = 1;
        }

        clearBuffer();
    }

    return value;
}

static void toLowerCase(const char source[], char result[])
{
    int i;

    for (i = 0; source[i] != '\0'; i++)
    {
        result[i] = (char)tolower((unsigned char)source[i]);
    }
    result[i] = '\0';
}

static int findEmployeeById(int id)
{
    for (int i = 0; i < employeeCount; i++)
    {
        if (empId[i] == id)
        {
            return i;
        }
    }
    return -1;
}

static void printTableHeader(void)
{
    printf("\n%-6s %-22s %-16s %-16s %12s\n",
           "ID", "Name", "Department", "Position", "Gross (N$)");
    printf("------------------------------------------------------------------------------\n");
}

static void printTableRow(int index)
{
    float gross = calculateGrossSalary(empBasic[index], empHousing[index],
                                       empTransport[index], empOther[index]);

    printf("%-6d %-22.22s %-16.16s %-16.16s %12.2f\n",
           empId[index], empName[index], empDept[index],
           empPosition[index], gross);
}

static void printEmployeeDetails(int index)
{
    printf("\n--- Employee Details ---\n");
    printf("Employee ID       : %d\n", empId[index]);
    printf("Name              : %s\n", empName[index]);
    printf("Department        : %s\n", empDept[index]);
    printf("Position          : %s\n", empPosition[index]);
    printf("Basic salary      : N$%.2f\n", empBasic[index]);
    printf("Housing allowance : N$%.2f\n", empHousing[index]);
    printf("Transport allow.  : N$%.2f\n", empTransport[index]);
    printf("Other allowances  : N$%.2f\n", empOther[index]);
}

float calculateGrossSalary(float basic, float housing, float transport, float other)
{
    return basic + housing + transport + other;
}

float calculateTax(float grossSalary)
{
    float rate;

    if (grossSalary <= 5000)
    {
        rate = 0.0f;
    }
    else if (grossSalary <= 15000)
    {
        rate = 0.10f;
    }
    else if (grossSalary <= 30000)
    {
        rate = 0.20f;
    }
    else
    {
        rate = 0.30f;
    }

    return grossSalary * rate;
}

float calculateNetSalary(float grossSalary, float tax)
{
    return grossSalary - tax;
}

void addEmployee(void)
{
    int id;
    int n = employeeCount;

    printf("\n--- Add Employee ---\n");

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("Error: the employee list is full (%d employees).\n", MAX_EMPLOYEES);
        return;
    }

    id = readInt("Enter Employee ID (1-99999): ", 1, 99999);

    if (findEmployeeById(id) != -1)
    {
        printf("Error: an employee with ID %d already exists.\n", id);
        return;
    }

    empId[n] = id;
    readText("Enter full name: ", empName[n], NAME_LEN);
    readText("Enter department: ", empDept[n], DEPT_LEN);
    readText("Enter position/job title: ", empPosition[n], POSITION_LEN);
    empBasic[n] = readAmount("Enter basic salary (N$): ", 0);
    empHousing[n] = readAmount("Enter housing allowance (N$): ", 1);
    empTransport[n] = readAmount("Enter transport allowance (N$): ", 1);
    empOther[n] = readAmount("Enter other allowances (N$): ", 1);

    employeeCount++;
    printf("\nEmployee '%s' added successfully.\n", empName[n]);
}

void displayEmployees(void)
{
    printf("\n--- All Employees ---\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    printTableHeader();
    for (int i = 0; i < employeeCount; i++)
    {
        printTableRow(i);
    }
    printf("\nTotal employees: %d\n", employeeCount);
}

void searchEmployee(void)
{
    int choice;
    int index;
    int id;
    int found = 0;
    char text[100];
    char searchLower[100];
    char nameLower[NAME_LEN];
    char deptLower[DEPT_LEN];

    printf("\n--- Search Employee ---\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    printf("1. Search by Employee ID\n");
    printf("2. Search by name (full or part of the name)\n");
    printf("3. Search by department\n");
    choice = readInt("Enter your choice: ", 1, 3);

    if (choice == 1)
    {
        id = readInt("Enter Employee ID: ", 1, 99999);
        index = findEmployeeById(id);

        if (index != -1)
        {
            printEmployeeDetails(index);
            found = 1;
        }
    }
    else if (choice == 2)
    {
        readText("Enter name to search: ", text, sizeof(text));
        toLowerCase(text, searchLower);

        for (int i = 0; i < employeeCount; i++)
        {
            toLowerCase(empName[i], nameLower);

            if (strstr(nameLower, searchLower) != NULL)
            {
                printEmployeeDetails(i);
                found++;
            }
        }
    }
    else
    {
        readText("Enter department to search: ", text, sizeof(text));
        toLowerCase(text, searchLower);

        for (int i = 0; i < employeeCount; i++)
        {
            toLowerCase(empDept[i], deptLower);

            if (strcmp(deptLower, searchLower) == 0)
            {
                printEmployeeDetails(i);
                found++;
            }
        }
    }

    if (found == 0)
    {
        printf("No matching employee found.\n");
    }
    else if (choice != 1)
    {
        printf("\n%d employee(s) found.\n", found);
    }
}

void calculateSalary(void)
{
    int id;
    int index;
    float gross;
    float tax;
    float net;

    printf("\n--- Calculate Salary ---\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    id = readInt("Enter Employee ID: ", 1, 99999);
    index = findEmployeeById(id);

    if (index == -1)
    {
        printf("Error: no employee with ID %d was found.\n", id);
        return;
    }

    gross = calculateGrossSalary(empBasic[index], empHousing[index],
                                 empTransport[index], empOther[index]);
    tax = calculateTax(gross);
    net = calculateNetSalary(gross, tax);

    printf("\n========== SALARY SLIP ==========\n");
    printf("Employee : %s (ID %d)\n", empName[index], empId[index]);
    printf("Dept     : %s\n", empDept[index]);
    printf("---------------------------------\n");
    printf("Basic salary      : N$%10.2f\n", empBasic[index]);
    printf("Housing allowance : N$%10.2f\n", empHousing[index]);
    printf("Transport allow.  : N$%10.2f\n", empTransport[index]);
    printf("Other allowances  : N$%10.2f\n", empOther[index]);
    printf("---------------------------------\n");
    printf("Gross salary      : N$%10.2f\n", gross);
    printf("Tax               : N$%10.2f\n", tax);
    printf("Net salary        : N$%10.2f\n", net);
    printf("=================================\n");

    if (net >= 20000)
    {
        printf("Income level      : High Income\n");
    }
    else
    {
        printf("Income level      : Standard Income\n");
    }
}

void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("          EMPLOYEE MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add employee\n");
        printf("2. Display employees\n");
        printf("3. Search for an employee\n");
        printf("4. Calculate employee salary\n");
        printf("5. Back to main menu\n");

        choice = readInt("Enter your choice: ", 1, 5);

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
                calculateSalary();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
        }
    } while (choice != 5);
}

int getEmployeeCount(void)
{
    return employeeCount;
}

float getEmployeeGrossSalary(int index)
{
    if (index < 0 || index >= employeeCount)
    {
        return 0;
    }

    return calculateGrossSalary(empBasic[index], empHousing[index],
                                empTransport[index], empOther[index]);
}

void getEmployeeName(int index, char name[])
{
    if (index < 0 || index >= employeeCount)
    {
        name[0] = '\0';
        return;
    }

    strcpy(name, empName[index]);
}
