#include <stdio.h>

#include <string.h>
#include "Bakery.h"



Bakery* createBakery(Employee** employees, Stock* stock, Order** historyOrders, void* linkedListClients, int sizeOfEmployees, int sizeOfHistoryOrders, int maxNumberClientsPermitted, const char* nameOfBakery) {
    Bakery* bakery = (Bakery*)malloc(sizeof(Bakery));
    if (bakery == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    bakery->employees = employees;
    bakery->stock = stock;
    bakery->historyOrders = historyOrders;
    bakery->linkedListClients = linkedListClients;
    bakery->sizeOfEmployees = sizeOfEmployees;
    bakery->sizeOfHistoryOrders = sizeOfHistoryOrders;
    bakery->sizeOfClientsInsideBakery = maxNumberClientsPermitted;
    bakery->nameOfBakery = (char*)malloc(strlen(nameOfBakery) + 1);
    if (bakery->nameOfBakery == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(bakery);
        exit(EXIT_FAILURE);
    }
    strcpy(bakery->nameOfBakery, nameOfBakery);
    return bakery;
}

void destroyBakery(Bakery* bakery) {
    if (bakery != NULL) {
        for (int i = 0; i < bakery->sizeOfEmployees; i++) {
            destroyEmployee(bakery->employees[i]);
        }
        free(bakery->employees);
        destroyStock(bakery->stock);
        for (int i = 0; i < bakery->sizeOfHistoryOrders; i++) {
            destroyOrder(bakery->historyOrders[i]);
        }
        free(bakery->historyOrders);
        destroyLinkedList((Client*)bakery->linkedListClients);
        free(bakery->nameOfBakery);
        free(bakery);
    }
}

void printBakeryDetails(Bakery* bakery) {
    if (bakery == NULL) {
        printf("Bakery is not initialized.\n");
        return;
    }

    printf("Bakery Name: %s\n", bakery->nameOfBakery);
    printf("Employees:\n");
    for (int i = 0; i < bakery->sizeOfEmployees; i++) {
        printf("Employee %d:\n", i + 1);
        printEmployee(bakery->employees[i]);
    }
    printf("=====================================================\n");
    printf("Stock:\n");
    printStockDetails(bakery->stock);
    printf("=====================================================\n");
    printf("Order History:\n");
    for (int i = 0; i < bakery->sizeOfHistoryOrders; i++) {
        printf("Order %d:\n", i + 1);
        printOrder(bakery->historyOrders[i]);
    }
    printf("=====================================================\n");
    printf("Clients:\n");
    printLinkedList((Client*)bakery->linkedListClients);
}


void saveBakeryToFile(Bakery* bakery, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }
    fprintf(file, "%s\n", bakery->nameOfBakery);
    fprintf(file, "%d\n", bakery->sizeOfEmployees);
    fprintf(file, "%d\n", bakery->sizeOfHistoryOrders);
    fprintf(file, "%d\n", bakery->sizeOfClientsInsideBakery);
    for (int i = 0; i < bakery->sizeOfEmployees; i++) {
        saveEmployeeToFile(bakery->employees[i], file);
    }
    
    saveStockToFile(bakery->stock, file);
    for (int i = 0; i < bakery->sizeOfHistoryOrders; i++) {
        saveOrderToFile(bakery->historyOrders[i], file);
    }
    void* currentNode = bakery->linkedListClients;
    while (currentNode != NULL) {
        saveClientToFile((Client*)currentNode, file);
        currentNode = ((Client*)currentNode)->next; 
    }

    fclose(file);
}


Bakery* loadBakeryFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading\n");
        return NULL;
    }

    Bakery* bakery = (Bakery*)malloc(sizeof(Bakery));
    if (bakery == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    int a;
    bakery->nameOfBakery = (char*)calloc(50,sizeof(char));
    a = fscanf(file, "%99[^\n]", bakery->nameOfBakery);
    a = fscanf(file, "%d\n", &bakery->sizeOfEmployees);
    a= fscanf(file, "%d\n", &bakery->sizeOfHistoryOrders);
    a = fscanf(file, "%d\n", &bakery->sizeOfClientsInsideBakery);

    
    bakery->employees = (Employee**)calloc(bakery->sizeOfEmployees,sizeof(Employee*));
    if (bakery->employees == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < bakery->sizeOfEmployees; i++) {
        bakery->employees[i] = loadEmployeeFromFile(file);
    } 
    bakery->stock = loadStockFromFile(file);
    bakery->historyOrders = (Order**)calloc(bakery->sizeOfHistoryOrders,sizeof(Order*));
    if (bakery->historyOrders == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < bakery->sizeOfHistoryOrders; i++) {
        bakery->historyOrders[i] = loadOrderFromFile(file);
    }
    bakery->linkedListClients = NULL;
    while (!feof(file)) {
        Client* client = loadClientFromFile(file);
        addClientLinkedList(bakery, client,0);
    }



    fclose(file);
    return bakery;
}


void addClientLinkedList(Bakery* bakery, void* item,int shouldAddCounter) {

    if (bakery->linkedListClients == NULL) {
        bakery->linkedListClients = item;
    }
    else {
        Client* temp = bakery->linkedListClients;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = item;
    }
    if (shouldAddCounter == 1) {
        bakery->sizeOfClientsInsideBakery++;
    }
}

int getLinkedListLength(Client* head) {
    int length = 0;
    Client* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

void saveBakeryToBinaryFile(Bakery* bakery, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }
    int nameLength = strlen(bakery->nameOfBakery);
    fwrite(&nameLength, sizeof(int), 1, file); 
    fwrite(bakery->nameOfBakery, sizeof(char), nameLength, file); 
    fwrite(&bakery->sizeOfEmployees, sizeof(int), 1, file);
    fwrite(&bakery->sizeOfHistoryOrders, sizeof(int), 1, file);
    fwrite(&bakery->sizeOfClientsInsideBakery, sizeof(int), 1, file);
    for (int i = 0; i < bakery->sizeOfEmployees; i++) {
        
        int nameLength = strlen(bakery->employees[i]->name);
        fwrite(&nameLength, sizeof(int), 1, file); 
        fwrite(bakery->employees[i]->name, sizeof(char), nameLength, file); 
        
        fwrite(&bakery->employees[i]->age, sizeof(int), 1, file);
        
        fwrite(&bakery->employees[i]->employeeType, sizeof(EmployeeType), 1, file);
    }
    
    fwrite(&bakery->stock->sizeOfProducts, sizeof(int), 1, file);
    for (int i = 0; i < bakery->stock->sizeOfProducts; i++) {
        
        fwrite(&bakery->stock->allProducts[i], sizeof(ProductInfo), 1, file);
    }
    
    for (int i = 0; i < bakery->sizeOfHistoryOrders; i++) {
        Order* order = bakery->historyOrders[i];
        fwrite(&order->sizeOfProducts, sizeof(int), 1, file);
        for (int j = 0; j < order->sizeOfProducts; j++) {
            ProductInfo info = (*order->products[j]);
            fwrite(&info, sizeof(ProductInfo), 1, file);
        }
        fwrite(&order->totalPrice, sizeof(int), 1, file);
        fwrite(&order->dateOfOrder, sizeof(Date), 1, file);
        Employee emp = *order->employeeServices;
        fwrite(&emp, sizeof(Employee), 1, file); 
        Client c = *order->clientDetails;
        fwrite(&c, sizeof(Client), 1, file); 
    }
    int linkedListLength = getLinkedListLength(bakery->linkedListClients);
    fwrite(&linkedListLength, sizeof(int), 1, file);
    Client* current = bakery->linkedListClients;
    while (current != NULL) {
        Client* client = (Client*)current;
        
        int clientNameLength = strlen(client->name);
        fwrite(&clientNameLength, sizeof(int), 1, file);
        fwrite(client->name, sizeof(char), clientNameLength, file);
        fwrite(&client->age, sizeof(int), 1, file); 
        fwrite(&client->id, sizeof(int), 1, file);
        current = current->next; 
    }


    fclose(file); 
}



Bakery* loadBakeryFromBinaryFile(const char* filename) {
    FILE* file = fopen(filename, "rb"); 
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading\n");
        return NULL;
    } 
    Bakery* bakery = (Bakery*)calloc(1,sizeof(Bakery));
    if (bakery == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }       int nameLength;    fread(&nameLength, sizeof(int), 1, file);    bakery->nameOfBakery = (char*)malloc((nameLength + 1) * sizeof(char)); 
    if (bakery->nameOfBakery == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        free(bakery);
        return NULL;
    }
    fread(bakery->nameOfBakery, sizeof(char), nameLength, file); 
    bakery->nameOfBakery[nameLength] = '\0'; 
    fread(&bakery->sizeOfEmployees, sizeof(int), 1, file);
    fread(&bakery->sizeOfHistoryOrders, sizeof(int), 1, file);
    fread(&bakery->sizeOfClientsInsideBakery, sizeof(int), 1, file);
    bakery->employees = (Employee**)calloc(bakery->sizeOfEmployees,sizeof(Employee*));
    for (int i = 0; i < bakery->sizeOfEmployees; i++) {
        bakery->employees[i]= (Employee*)malloc(sizeof(Employee));
        int nameLength;
        fread(&nameLength, sizeof(int), 1, file);
        bakery->employees[i]->name =(char*) malloc((nameLength + 1) * sizeof(char));
        fread(bakery->employees[i]->name, sizeof(char), nameLength, file);
        bakery->employees[i]->name[nameLength] = '\0';
       fread(&bakery->employees[i]->age, sizeof(int), 1, file);      
        fread(&bakery->employees[i]->employeeType, sizeof(EmployeeType), 1, file);
    }


    Stock* stock = (Stock*)malloc(sizeof(Stock));
    if (stock == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    fread(&stock->sizeOfProducts, sizeof(int), 1, file);
    stock->allProducts = (ProductInfo*)calloc(stock->sizeOfProducts,sizeof(ProductInfo));
    for (int i = 0; i < stock->sizeOfProducts; i++) {
        fread(&stock->allProducts[i], sizeof(ProductInfo), 1, file);
    }
    bakery->stock = stock;
    bakery->historyOrders = (Order**)calloc(bakery->sizeOfHistoryOrders,sizeof(Order*));
    for (int i = 0; i < bakery->sizeOfHistoryOrders; i++) {
        bakery->historyOrders[i] = (Order*)calloc(1,sizeof(Order));
        fread(&bakery->historyOrders[i]->sizeOfProducts, sizeof(int), 1, file);
        bakery->historyOrders[i]->products = (ProductInfo**)malloc(sizeof(ProductInfo*) * bakery->historyOrders[i]->sizeOfProducts);
        for (int j = 0; j < bakery->historyOrders[i]->sizeOfProducts; j++) {
            bakery->historyOrders[i]->products[j] = (ProductInfo*)malloc(sizeof(ProductInfo));
            fread(bakery->historyOrders[i]->products[j], sizeof(ProductInfo), 1, file);
        }
        fread(&bakery->historyOrders[i]->totalPrice, sizeof(int), 1, file);
        fread(&bakery->historyOrders[i]->dateOfOrder, sizeof(Date), 1, file);
        bakery->historyOrders[i]->employeeServices = (Employee*)malloc(sizeof(Employee));
        fread(bakery->historyOrders[i]->employeeServices, sizeof(Employee), 1, file);
        bakery->historyOrders[i]->clientDetails = (Client*)calloc(1,sizeof(Client));
        if (bakery->historyOrders[i]->clientDetails != NULL) {
            fread(bakery->historyOrders[i]->clientDetails, sizeof(Client), 1, file);
        }
    }
    int listLength;
    fread(&listLength, sizeof(int), 1, file); 
    for (int i = 0; i < listLength; i++) {
        Client* client = (Client*)calloc(1,sizeof(Client));
        if (client == NULL) {
            continue;
        }
        int clientNameLength;
        fread(&clientNameLength, sizeof(int), 1, file); 
        client->name = (char*)calloc((clientNameLength + 1) , sizeof(char)); 
        if (client->name != NULL) {
            fread(client->name, sizeof(char), clientNameLength, file);
            client->name[clientNameLength] = '\0';
        }
        fread(&client->age, sizeof(int), 1, file); 
        fread(&client->id, sizeof(int), 1, file); 
        addClientLinkedList(bakery, client,0);
    }
    fclose(file); 
    return bakery;
}

Client* convertLinkedListToArray(Bakery* bakery, int* size) {
    int count = getLinkedListLength(bakery->linkedListClients);
    Client* clientsArray = (Client*)calloc(count,sizeof(Client));
    if (clientsArray == NULL) {
        return NULL;
    }
    Client* current = bakery->linkedListClients;
    for (int i = 0; i < count; i++) {
        clientsArray[i].age = current->age;
        clientsArray[i].id = current->id;
        clientsArray[i].name = current->name;
        current = current->next;
    }
    *size = count;
    return clientsArray;
}

Client* sortClientByAge(Bakery* bakery, int* size) {
    Client* clientsArray = convertLinkedListToArray(bakery, size);
    qsort(clientsArray, *size, sizeof(Client), compareClientsByAge);
    return clientsArray;
}

Client* sortClientByName(Bakery* bakery,int *size) {
    Client* clientsArray = convertLinkedListToArray(bakery, size);
    qsort(clientsArray, *size, sizeof(Client), compareClientsByName);
    return clientsArray;
}

Client* sortClientById(Bakery* bakery, int* size) {
    Client* clientsArray = convertLinkedListToArray(bakery, size);
    qsort(clientsArray, *size, sizeof(Client), compareClientsById);
    return clientsArray;
}

Client* searchClientByName(Bakery* bakery, const char* clientName) {
    int size;
    Client* clientsArray = sortClientByName(bakery,&size);
    Client target = { clientName,0,0,NULL };
    return(Client*)bsearch(&target, clientsArray, size, sizeof(Client), compareClientsByName);
  
}

Client* searchClientById(Bakery* bakery, int id) {
    int size;
    Client* clientsArray = sortClientById(bakery, &size);
    Client target1;
    target1.id = id;
    Client* result = NULL;
    if (clientsArray != NULL) {
        result = (Client*)bsearch(&target1, clientsArray, size, sizeof(Client), compareClientsById);
    }
    return result;
}

void freeBakery(Bakery* bakery) {
    if (bakery == NULL) {
        return;
    }
    if (bakery->employees != NULL && bakery->sizeOfEmployees > 0) {
        for (int i = 0; i < bakery->sizeOfEmployees; i++)
        {
            freeEmployee(bakery->employees[i]);
        }
        free(bakery->employees);
    }
    if (bakery->historyOrders != NULL && bakery->sizeOfHistoryOrders > 0) {
        for (int i = 0; i < bakery->sizeOfHistoryOrders; i++)
        {
            freeOrder(bakery->historyOrders[i]);
        }
        free(bakery->historyOrders);
    }
    freeStock(bakery->stock);
    free(bakery->nameOfBakery);
    freeClientLinkedList(bakery->linkedListClients);
}

Order* searchOrderByDate(Bakery* bakery, Date date) {
    qsort(bakery->historyOrders, bakery->sizeOfHistoryOrders, sizeof(Order*), compareOrdersByDate);
    Order* targetOrder = (Order*)calloc(1,sizeof(Order));
    if (targetOrder == NULL) {
        return NULL;
    }
    targetOrder->dateOfOrder = date;
    Order** result = (Order**)bsearch(&targetOrder, bakery->historyOrders, bakery->sizeOfHistoryOrders, sizeof(Order*), compareOrdersByDate);
    if (result != NULL) {
        return *result;
    }
    else {
        return NULL; 
    }
}

void printMissingItems(Bakery* bakery) {
    int missingItemCount = 0;
    printf("Missing items in store:\n");
    for (int i = 0; i < bakery->stock->sizeOfProducts; i++) {
        if (bakery->stock->allProducts[i].amountOfProduct == 0) {
            printf("- Product Name: %s\n", bakery->stock->allProducts[i].product.name);
            printf("  Price: %d\n", bakery->stock->allProducts[i].price);
            printf("  Quantity: %d\n", bakery->stock->allProducts[i].amountOfProduct);
            missingItemCount++;
        }
    }
    if (missingItemCount == 0) {
        printf("All items in store are available.\n");
    }
}

void addEmployee(Bakery* bakery, Employee* employee) {
    bakery->sizeOfEmployees++;
    bakery->employees = realloc(bakery->employees, bakery->sizeOfEmployees * sizeof(Employee*));
    if (bakery->employees == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    bakery->employees[bakery->sizeOfEmployees - 1] = employee;
}
