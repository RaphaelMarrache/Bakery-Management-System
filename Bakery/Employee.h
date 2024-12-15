#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#pragma warning(disable:4996)
typedef enum EmployeeType {
    Cashier,
    Baker,
    Cleaner
} EmployeeType;

typedef struct Employee{
    char* name;
    int age;
    EmployeeType employeeType;
} Employee;

Employee* createEmployee(const char* name, int age, EmployeeType type);
void destroyEmployee(Employee* employee);
void printEmployee(Employee* employee);
void saveEmployeeToFile(Employee* employee, FILE* file);
Employee* loadEmployeeFromFile(FILE* file);
void freeEmployee(Employee* emp);

#endif 
