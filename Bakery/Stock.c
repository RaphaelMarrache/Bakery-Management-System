#include <stdio.h>
#include <stdlib.h>
#include "Stock.h"

Stock* createStock(ProductInfo* allProducts, int sizeOfProducts) {
    Stock* stock = (Stock*)malloc(sizeof(Stock));
    if (stock == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stock->allProducts = allProducts;
    stock->sizeOfProducts = sizeOfProducts;
    return stock;
}

void destroyStock(Stock* stock) {
    if (stock != NULL) {
        free(stock);
    }
}

void printStockDetails(Stock* stock) {
    if (stock == NULL) {
        printf("Stock is not initialized.\n");
        return;
    }

    printf("Stock Details:\n");
    printf("Size of Products: %d\n", stock->sizeOfProducts);
    for (int i = 0; i < stock->sizeOfProducts; i++) {
        printf("Product %d:\n", i + 1);
        printProductInfo(&(stock->allProducts[i]));
    }
}

void saveStockToFile(Stock* stock, FILE* file) {
    fprintf(file, "%d\n", stock->sizeOfProducts);
    for (int i = 0; i < stock->sizeOfProducts; i++) {
        saveProductInfoToFile(&(stock->allProducts[i]), file);
    }
}

Stock* loadStockFromFile(FILE* file) {
    Stock* stock = (Stock*)malloc(sizeof(Stock));
    if (stock == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int ignore;
    ignore = fscanf(file, "%d\n", &stock->sizeOfProducts);
    stock->allProducts = (ProductInfo*)calloc(stock->sizeOfProducts,sizeof(ProductInfo));
    if (stock->allProducts == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < stock->sizeOfProducts; i++) {
        ProductInfo* info = loadProductInfoFromFile(file);
        ProductInfo info2 = { info->product,info->amountOfProduct,info->price };

        stock->allProducts[i] = info2;
    }

    return stock;
}

void freeStock(Stock* stock) {
    if (stock == NULL) {
        return;
    }
    freeProductInfo(stock->allProducts);
}