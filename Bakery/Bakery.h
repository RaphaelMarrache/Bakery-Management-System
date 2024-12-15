#ifndef BAKERY_H
#define BAKERY_H

#include "Employee.h"
#include "Stock.h"
#include "Order.h"
#pragma warning(disable:4996)
#define MAX_NAME_LENGTH 255
#define MENU_OPTIONS 15

typedef struct Bakery{
    Employee** employees;
    Stock* stock;
    Order** historyOrders;
    void* linkedListClients;
    int sizeOfEmployees;
    int sizeOfHistoryOrders;
    int sizeOfClientsInsideBakery;
    char* nameOfBakery;
} Bakery;

void printBakeryDetails(Bakery* bakery);
Bakery* createBakery(Employee** employees, Stock* stock, Order** historyOrders, void* linkedListClients, int sizeOfEmployees, int sizeOfHistoryOrders, int maxNumberClientsPermitted, const char* nameOfBakery);
void destroyBakery(Bakery* bakery);
void saveBakeryToFile(Bakery* bakery, const char* filename);
Bakery* loadBakeryFromFile(const char* filename);
void addClientLinkedList(Bakery* bakery, void* item, int shouldAddCounter);
void saveBakeryToBinaryFile(Bakery* bakery, const char* filename);
Bakery* loadBakeryFromBinaryFile(const char* filename);
int getLinkedListLength(Client* head);
Client* searchClientByName(Bakery* bakery , const char* clientName);
Client* convertLinkedListToArray(Bakery* bakery, int* size);
Client* searchClientById(Bakery* bakery, int id);
Order* searchOrderByDate(Bakery* bakery, Date date);
Client* sortClientByName(Bakery* bakery, int* size);
Client* sortClientById(Bakery* bakery, int* size);
Client* sortClientByAge(Bakery* bakery, int* size);
void printMissingItems(Bakery* bakery);
void freeBakery(Bakery* bakery);
void addEmployee(Bakery* bakery, Employee* employee);



#endif
