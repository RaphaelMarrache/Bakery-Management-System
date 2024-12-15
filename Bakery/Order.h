#ifndef ORDER_H
#define ORDER_H

#include "ProductInfo.h"
#include "Employee.h"
#include "Client.h"
#include "Date.h"

typedef struct Order {
    ProductInfo** products;
    int sizeOfProducts;
    int totalPrice;
    Date dateOfOrder;
    Employee* employeeServices;
    Client* clientDetails;
} Order;

Order* createOrder(ProductInfo** products, int sizeofproducts, Date dateOfOrder, Employee* employeeServices, Client* clientDetails);
void destroyOrder(Order* order);
void printOrder(Order* order);
void saveOrderToFile(Order* order, FILE* file);
Order* loadOrderFromFile(FILE* file);
int compareOrdersByDate(const void* a, const void* b);
void freeOrder(Order* order);

#endif /* ORDER_H */
