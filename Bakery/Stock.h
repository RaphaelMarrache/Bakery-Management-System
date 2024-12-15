#ifndef STOCK_H
#define STOCK_H

#include "ProductInfo.h"

typedef struct Stock {
    ProductInfo* allProducts;
    int sizeOfProducts;
} Stock;

Stock* createStock(ProductInfo* allProducts, int sizeOfProducts);
void destroyStock(Stock* stock);
void printStockDetails(Stock* stock);
void saveStockToFile(Stock* stock, FILE* file);
Stock* loadStockFromFile(FILE* file);
void freeStock(Stock* stock);

#endif /* STOCK_H */
