#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRUDCT_NAME_LENGTH 20
typedef struct Product {
    char name[20];
    int isGlutenFree;
} Product;

Product createProduct(const char* name, int isGlutenFree);
void destroyProduct(Product* product);
void printProduct(Product* product);
void saveProductToFile(Product* product, FILE* file);
Product loadProductFromFile(FILE* file);
#endif /* PRODUCT_H */
