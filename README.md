# MUNICIPAL FINANCIAL MANAGEMENT SYSTEM (MFMS)

## Course
PAP521S – Programming in Practice

## Project
Project A – Foundation System

## Programming Language
ANSI C (C99)

## Development Environment
Visual Studio Code + GCC

## Group Number
[ENTER GROUP NUMBER]

## Group Members
1. [Student Name] – [Student Number]
2. [Student Name] – [Student Number]
3. [Student Name] – [Student Number]
4. [Student Name] – [Student Number]
5. [Student Name] – [Student Number]
6. [Student Name] – [Student Number]
7. [Student Name] – [Student Number]

## Project Description
The Municipal Financial Management System (MFMS) is a foundation C application for managing basic municipal financial information.

The system demonstrates the programming concepts covered during Weeks 1–8, including variables, input/output, decisions, loops, arrays, strings, searching and functions.

## System Features
- Employee management
- Budget management
- Supplier management
- Asset management
- Basic reports
- Searching
- Salary and budget calculations
- Basic input validation
- Menu-driven navigation

## Files
- main.c
- employees.c
- employees.h
- budget.c
- budget.h
- suppliers.c
- suppliers.h
- assets.c
- assets.h
- reports.c
- reports.h

## Compilation
Open the terminal in the project folder and run:

```bash
gcc main.c employees.c budget.c suppliers.c assets.c reports.c -o mfms
```

## Run
Linux/macOS:
```bash
./mfms
```

Windows:
```bash
mfms.exe
```

## Individual Responsibilities
- Student 1: Employee Management
- Student 2: Budget Management
- Student 3: Supplier Management
- Student 4: Asset Management
- Student 5: Reports
- Student 6: Functions, integration and validation
- Student 7: Testing, documentation and Git coordination

Replace the names and responsibilities above with the actual group information.

## Concepts Used
The implementation is intentionally kept within the introductory C concepts covered in Weeks 1–8:
- Variables and data types
- printf() and scanf()
- if/else
- switch
- for and do-while loops
- Arrays
- Strings
- strlen()
- strcmp()
- Functions
- Parameters and return values
- Basic searching


### Week 7 string functions used
The project uses the string concepts from the Week 7 notes:
- `fgets()` for reading names, departments, towns and other text that may contain spaces.
- `strlen()` to find the length of a supplier name.
- `strcmp()` to compare a supplier name when searching.
- `strcpy()` and `strcat()` to copy and join supplier text.
- `strcspn()` is used to remove the newline left by `fgets()`.

The employee arrays use the same basic array style from the Week 5 and 6 notes, such as arrays of 50 values. No `MAX_EMPLOYEES` constant is used.
