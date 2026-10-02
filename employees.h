#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100
#define NAME_LEN 50
#define DEPT_LEN 30
#define POSITION_LEN 30

void employeeMenu(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void calculateSalary(void);

float calculateGrossSalary(float basic, float housing, float transport, float other);
float calculateTax(float grossSalary);
float calculateNetSalary(float grossSalary, float tax);

int getEmployeeCount(void);
float getEmployeeGrossSalary(int index);
void getEmployeeName(int index, char name[]);

#endif
