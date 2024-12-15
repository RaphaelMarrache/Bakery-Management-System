#ifndef PRODUCTINFO_H
#define PRODUCTINFO_H
#pragma warning(disable:4996)
#include "Product.h"


typedef struct ProductInfo {
    Product product;
    int amountOfProduct;
    int price;
} ProductInfo;

ProductInfo* createProductInfo(Product product, int amountOfProduct, int price);
void destroyProductInfo(ProductInfo* productInfo);
void printProductInfo(ProductInfo* productInfo);
void saveProductInfoToFile(ProductInfo* productInfo, FILE* file);
ProductInfo* loadProductInfoFromFile(FILE* file);
void freeProductInfo(ProductInfo*);

#endif /* PRODUCTINFO_H */
