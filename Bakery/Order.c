#include <stdio.h>
#include <stdlib.h>
#include "Order.h"

Order* createOrder(ProductInfo** products, int sizeofproducts, Date dateOfOrder, Employee* employeeServices, Client* clientDetails) {
    Order* order = (Order*)malloc(sizeof(Order));
    if (order == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    order->products = products;
    order->sizeOfProducts = sizeofproducts;
    order->totalPrice = 50;
    order->dateOfOrder = dateOfOrder;
    order->employeeServices = employeeServices;
    order->clientDetails = clientDetails;
    return order;
}

void destroyOrder(Order* order) {
    if (order != NULL) {
        free(order);
    }
}

void printOrder(Order* order) {
    if (order == NULL) {
        printf("Order is not initialized.\n");
        return;
    }

    printf("Order Details:\n");
    printf("Total Products: %d\n", order->sizeOfProducts);
    for (int i = 0; i < order->sizeOfProducts; i++) {
        printf("Product %d:\n", i + 1);
        printProductInfo(order->products[i]);
    }
    printf("Total Prize: %d\n", order->totalPrice);
    printf("Order Date: %d/%d/%d\n", order->dateOfOrder.day, order->dateOfOrder.month, order->dateOfOrder.year);
    printEmployee(order->employeeServices);
    printClient(order->clientDetails);
}

void saveOrderToFile(Order* order, FILE* file) {
    fprintf(file, "%d,%d\n", order->sizeOfProducts, order->totalPrice);
    saveDateToFile(order->dateOfOrder, file);
    for (int i = 0; i < order->sizeOfProducts; i++) {
        saveProductInfoToFile(order->products[i], file);
    }
    saveEmployeeToFile(order->employeeServices, file);
    saveClientToFile(order->clientDetails, file);
}

Order* loadOrderFromFile(FILE* file) {
    Order* order = (Order*)malloc(sizeof(Order));
    if (order == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int sizeofproducts, total_prize,ignore;
    ignore = fscanf(file, "%d,%d\n", &sizeofproducts, &total_prize);
    order->dateOfOrder=loadDateFromFile(file);
    // Load products
    ProductInfo** products = (ProductInfo**)calloc(sizeofproducts,sizeof(ProductInfo*));
    if (products == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < sizeofproducts; i++) {
        products[i] = loadProductInfoFromFile(file);
    }

    // Load employee and client details
    Employee* employee = loadEmployeeFromFile(file);
    Client* client = loadClientFromFile(file);

    order->products = products;
    order->sizeOfProducts = sizeofproducts;
    order->totalPrice = total_prize;
    order->employeeServices = employee;
    order->clientDetails = client;

    return order;
}

int compareOrdersByDate(const void* a, const void* b) {
    const Order* orderA = *(const Order**)a;
    const Order* orderB = *(const Order**)b;
    if (orderA->dateOfOrder.year != orderB->dateOfOrder.year) {
        return orderA->dateOfOrder.year - orderB->dateOfOrder.year;
    }
    else if (orderA->dateOfOrder.month != orderB->dateOfOrder.month) {
        return orderA->dateOfOrder.month - orderB->dateOfOrder.month;
    }
    else {
        return orderA->dateOfOrder.day - orderB->dateOfOrder.day;
    }
}

void freeOrder(Order* order) {
    if (order == NULL)
    {
        return;
    }
    for (int i = 0; i < order->sizeOfProducts; i++)
    {
 
        freeProductInfo(order->products[i]);
    }
    free(order->products);
    freeEmployee(order->employeeServices);
    free(order->clientDetails);
    free(order);
}