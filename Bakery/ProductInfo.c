#include <stdio.h>
#include <stdlib.h>
#include "productinfo.h"

ProductInfo* createProductInfo(Product product, int amountOfProduct, int price) {
    ProductInfo* productInfo = (ProductInfo*)malloc(sizeof(ProductInfo));
    if (productInfo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    productInfo->product = product;
    productInfo->amountOfProduct = amountOfProduct;
    productInfo->price = price;
    return productInfo;
}

void destroyProductInfo(ProductInfo* productInfo) {
    if (productInfo != NULL) {
        free(productInfo);
    }
}


void printProductInfo(ProductInfo* productInfo) {
    if (productInfo == NULL) {
        printf("Product Info is not initialized.\n");
        return;
    }
    printf("Product: ");
    printProduct(&(productInfo->product));
    printf("Amount of Product: %d\n", productInfo->amountOfProduct);
    printf("Price: %d\n", productInfo->price);
}

void saveProductInfoToFile(ProductInfo* productInfo, FILE* file) {
    saveProductToFile(&(productInfo->product), file);
    fprintf(file, "%d,%d\n", productInfo->amountOfProduct, productInfo->price);
}

ProductInfo* loadProductInfoFromFile(FILE* file) {
    ProductInfo* productInfo = (ProductInfo*)malloc(sizeof(ProductInfo));
    if (productInfo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    productInfo->product = loadProductFromFile(file);
    int ingore = fscanf(file, "%d,%d\n", &productInfo->amountOfProduct, &productInfo->price);

    return productInfo;
}

void freeProductInfo(ProductInfo* info) {
    if (info == NULL) {

        return;
    }
    free(info);

}