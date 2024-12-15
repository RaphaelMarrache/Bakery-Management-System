#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

Product createProduct(const char* name, int isGlutenFree) {
    Product product;
    strncpy(product.name, name, sizeof(product.name) - 1);
    product.name[sizeof(product.name) - 1] = '\0';
    product.isGlutenFree = isGlutenFree;
    return product;
}

void destroyProduct(Product* product) {
    if (product != NULL) {
        free(product);
    }
}

void printProduct(Product* product) {
    if (product == NULL) {
        printf("Product is not initialized.\n");
        return;
    }
    printf("Name: %s\n", product->name);
    printf("Is Gluten Free: %s\n", product->isGlutenFree ? "Yes" : "No");
}

void saveProductToFile(Product* product, FILE* file) {
    fprintf(file, "%s,%d\n", product->name, product->isGlutenFree);
}

Product loadProductFromFile(FILE* file) {
    Product product;
    char name[50] = { 0 };
    int isGlutenFree,ignore;
    ignore = fscanf(file, "%[^,],%d\n", name, &isGlutenFree);
    strncpy(product.name, name, sizeof(product.name));
    product.isGlutenFree = isGlutenFree;
    return product;
}