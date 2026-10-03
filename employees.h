#ifndef EMPLOYEES_H
#define EMPLOYEES_H

void employeeMenu(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
float calculateSalary(float basic, float housing, float transport, float other);
int getEmployeeCount(void);
float getAverageSalary(void);
float getHighestSalary(void);
float getLowestSalary(void);

#endif
