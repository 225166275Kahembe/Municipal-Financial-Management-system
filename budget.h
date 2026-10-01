#ifndef BUDGET_H
#define BUDGET_H

void budgetMenu(void);
void addBudget(void);
void displayBudgets(void);
float calculateBudget(float allocated, float expenditure);
float getTotalAllocated(void);
float getTotalExpenditure(void);
float getRemainingBudget(void);

#endif
