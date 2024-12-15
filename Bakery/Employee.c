#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

Employee* createEmployee(const char* name, int age, EmployeeType type) {
    Employee* employee = (Employee*)malloc(sizeof(Employee));
    if (employee == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    employee->name = (char*)malloc(strlen(name) + 1);
    if (employee->name != NULL) {
        strcpy(employee->name, name);
    }
    if (employee->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(employee);
        exit(EXIT_FAILURE);
    }
    employee->age = age;
    employee->employeeType = type;
    return employee;
}

void destroyEmployee(Employee* employee) {
    if (employee != NULL) {
        free(employee->name);
        free(employee);
    }
}

void saveEmployeeToFile(Employee* employee, FILE* file) {
    fprintf(file, "%s,%d,%d\n", employee->name, employee->age, employee->employeeType);
}

Employee* loadEmployeeFromFile(FILE* file) {
    Employee* employee = (Employee*)malloc(sizeof(Employee));
    if (employee == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    char name[50] = { 0 };
    int age, type,ignore;
    ignore = fscanf(file, "%[^,],%d,%d\n", name, &age, &type);

    employee->name = (char*)calloc(100, sizeof(char));
    if (employee->name != NULL && name != NULL) {
        strcpy(employee->name, name);
    }
 
    employee->age = age;

    employee->employeeType = (EmployeeType)type;

    return employee;
}

void printEmployee(Employee* employee) {
    if (employee == NULL) {
        printf("Employee is not initialized.\n");
        return;
    }

    printf("Employee Details:\n");
    printf("Name: %s\n", employee->name);
    printf("Age: %d\n", employee->age);
    printf("Employee Type: ");
    switch (employee->employeeType) {
    case Cashier:
        printf("Cashier\n");
        break;
    case Baker:
        printf("Baker\n");
        break;
    case Cleaner:
        printf("Cleaner\n");
        break;
    default:
        printf("Unknown\n");
    }
}

void freeEmployee(Employee* emp) {
    if (emp == NULL) {
        return;
    }
    free(emp->name);
    free(emp);
}