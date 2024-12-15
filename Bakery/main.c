#include <stdio.h>
#include  <string.h>
#include <stdlib.h>
#include "Bakery.h"

#define PRINT_MENU() \
     \
        printf("\n--- Menu ---\n"); \
        printf("1. Print all bakery details\n"); \
        printf("2. Save Bakery to text File\n"); \
        printf("3. Load Bakery from text File\n"); \
        printf("4. Save Bakery to binary File\n"); \
        printf("5. Load Bakery from binary File\n"); \
        printf("6. Search client by name {bsearch1}\n"); \
        printf("7. Search client by id {bsearch2}\n"); \
        printf("8. Search order by date {bsearch3}\n"); \
        printf("9. Sort clients by name {qsort1}\n"); \
        printf("10. Sort clients by age {qsort2}\n"); \
        printf("11. Sort orders by date {qsort3}\n"); \
        printf("12. Enter client to the bakery\n"); \
        printf("13. Print all missing products in store\n"); \
        printf("14. Add employee\n"); \
        printf("15. Exit\n"); \
        printf("Choose an option: "); \


#define STRING_INPUT(a) char a[255] = { 0 }; printf("Enter the name of the client:\n"); ignore = scanf("%s", clientName);

Stock* createMockStock() {
    ProductInfo product1 = { createProduct("Bread", 0), 10, 100 };
    ProductInfo product2 = { createProduct("Cake", 1), 5, 200 };
    ProductInfo product3 = { createProduct("Cookie", 0), 20, 50 };
    ProductInfo product4 = { createProduct("Milk", 0), 0, 50 };
    ProductInfo* allProducts = (ProductInfo*)calloc(4, sizeof(ProductInfo));
    if (allProducts != NULL) {
        allProducts[0] = product1;
        allProducts[1] = product2;
        allProducts[2] = product3;
        allProducts[3] = product4;
    }
    Stock* stock = createStock(allProducts, 4);
    return stock;
}

Order** createOrders(Employee** employees,Client** clients) {
  
    Date date1 = { 1, 4, 2024 }; 
    Date date2 = { 2, 4, 2024 };
    ProductInfo* product1 = createProductInfo(createProduct("Bread", 0), 2, 100);
    ProductInfo* product2 = createProductInfo(createProduct("Cake", 1), 1, 200);
    ProductInfo* product3 = createProductInfo(createProduct("Cookie", 0), 3, 50);
    ProductInfo** products1 = (ProductInfo**)calloc(3, sizeof(ProductInfo*));
    if (products1 != NULL && product1 != NULL && product2 != NULL) {
        products1[0] = product1;
        products1[1] = product2;
    }
  
   

    ProductInfo** products2 = (ProductInfo**)calloc(3, sizeof(ProductInfo*));
    if (products2 != NULL && product3 != NULL) {
        products2[0] = product3;
    }
   
  
    Employee* e1 = createEmployee(employees[0]->name, employees[0]->age, employees[0]->employeeType);
    Employee* e2 = createEmployee(employees[1]->name, employees[1]->age, employees[1]->employeeType);   
    Order* order1 = createOrder(products1, 2, date1, e1, createClient(clients[0]->name, clients[0]->age, clients[0]->id));
    Order* order2 = createOrder(products2, 1, date2, e2, createClient(clients[1]->name, clients[1]->age, clients[1]->id));

    Order** orders = (Order**)malloc(2 * sizeof(Order*));
    if (orders == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    orders[0] = order1;
    orders[1] = order2;

    return orders;
}


Employee** createMockEmploeyyes () {
    Employee** employees = (Employee**)malloc(4 * sizeof(Employee*));
    if (employees == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    employees[0] = createEmployee("Omer", 17, Cashier);
    employees[1] = createEmployee("David", 20, Baker);
    employees[2] = createEmployee("Yossi", 18, Cleaner);
    employees[3] = createEmployee("Amit", 18, Baker);

    return employees;
}

Client** createMockClients() {
    Client** clients = (Client**)malloc(6 * sizeof(Client*));
    if (clients == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    clients[0] = createClient("John", 30, 1);
    clients[1] = createClient("Alice", 25, 2);
    clients[2] = createClient("Bob", 35, 3);
    clients[3] = createClient("Emma", 28, 4);
    clients[4] = createClient("David", 40, 5);
    clients[5] = createClient("Sophia", 22, 6);

    return clients;
}

Bakery* createMockBakery() {
    Bakery* mainBakery = (Bakery*)calloc(1, sizeof(Bakery));
    Employee** employees = createMockEmploeyyes();
    Stock* stock = createMockStock();
    Client** clients = createMockClients();
    Order** orders = createOrders(employees, clients);
    for (int i = 0; i < 5; i++) {
        clients[i]->next = clients[i + 1];
    }
    clients[5]->next = NULL;
    Client* head = clients[0];
    mainBakery = createBakery(employees, stock, orders, head, 4, 2, 6, "Magic Bakery");
    return mainBakery;
}

void cleanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main() {
    int option,ignore;
    Bakery* mainBakery = createMockBakery();
    printf("#####################################\n");
    printf("Mock bakery data is loaded By default\n");
    printf("#####################################\n");
    do {
        PRINT_MENU();
        ignore = scanf("%d", &option);

        switch (option) {
        case 1:
            printBakeryDetails(mainBakery);
            break;
        case 2:
            saveBakeryToFile(mainBakery, "bakery.txt");
            printf("File saved Sucsessfuly\n");
            break;
        case 3:
            mainBakery = loadBakeryFromFile("bakery.txt");
            printf("File loaded Sucsessfuly\n");
            break;
        case 4:
            saveBakeryToBinaryFile(mainBakery, "bakery.bin");
            printf("File saved Sucsessfuly\n");
            break;
        case 5:
            mainBakery = loadBakeryFromBinaryFile("bakery.bin");
            printf("File loaded Sucsessfuly\n");
            break;
        case 6:
        {
            STRING_INPUT(clientName);
            Client* result = searchClientByName(mainBakery, clientName);
            if (result == NULL) {
                printf("Client [%s] not found\n", clientName);
            }
            else {
                printf("Client Found\n");
                printClient(result);
            }
            break;
        }
        case 7:
        {
            int id = 0;
            printf("Enter the id of the client:\n");
            ignore = scanf("%d", &id);
            Client* result = searchClientById(mainBakery, id);
            if (result == NULL) {
                printf("Client [id - %d] not found\n", id);
            }
            else {
                printf("Client Found\n");
                printClient(result);
            }
            break;
        }
        case 8:
        {
            int ignore;
            Date date;
            printf("Enter day: ");
            ignore = scanf("%d", &date.day);
            printf("Enter month: ");
            ignore = scanf("%d", &date.month);
            printf("Enter year: ");
            ignore = scanf("%d", &date.year);
            Order* result = searchOrderByDate(mainBakery,date);
            if (result == NULL) {
                printf("Order not found\n");
            }
            else {
                printf("Order Found\n");
                printOrder(result);
            }
            
            break;
        }
        case 9: {
            printf("Before:\n");
            printLinkedList(mainBakery->linkedListClients);
            printf("After:\n");
            int number;
            Client* clientArr = sortClientByName(mainBakery, &number);
            for (int i = 0; i < number; i++)
            {
                printClient(&clientArr[i]);
            }
            
            break;
        }
        case 10: {
            printf("Before:\n");
            printLinkedList(mainBakery->linkedListClients);
            printf("After:\n");
            int number;
            Client* clientArr = sortClientByAge(mainBakery, &number);
            for (int i = 0; i < number; i++)
            {
                printClient(&clientArr[i]);
            }
            break;
        }
        case 11: {
            printf("Before:\n");
            for (int i = 0; i < mainBakery->sizeOfHistoryOrders; i++) {
                printf("Order %d:\n", i + 1);
                printOrder(mainBakery->historyOrders[i]);
            }
            printf("After:\n");
            qsort(mainBakery->historyOrders, mainBakery->sizeOfHistoryOrders, sizeof(Order*), compareOrdersByDate);
            for (int i = 0; i < mainBakery->sizeOfHistoryOrders; i++) {
                printf("Order %d:\n", i + 1);
                printOrder(mainBakery->historyOrders[i]);
            }
            break;
        }
        case 12: {
            Client* client = getClientInput();
            addClientLinkedList(mainBakery, client,1);
            printf("Client added sucsseful");
            printClient(client);
            break;
        }
        case 13: {
            printMissingItems(mainBakery);
            break;
        }
        case 14: {
            Employee* newEmployee =(Employee*) calloc(1,sizeof(Employee));
            if (newEmployee == NULL) {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            printf("Enter employee name: ");
            cleanBuffer();
            char nameBuffer[100] = { 0 };
            scanf("%s", nameBuffer);
            // Allocate memory for name and copy the input
            newEmployee->name =(char*) malloc(strlen(nameBuffer) + 1);
            if (newEmployee->name == NULL) {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(newEmployee->name, nameBuffer);

            // Prompt user for age
            printf("Enter employee age: ");
            cleanBuffer();
            int ignore = scanf("%d", &newEmployee->age);

            // Prompt user for employee type
            cleanBuffer();
            int employeeTypeChoice;
            printf("Enter employee type (1 for CASHIER, 2 for BAKER, 3 for CLEANER): ");
            ignore = scanf("%d", &employeeTypeChoice);
            employeeTypeChoice--;
            newEmployee->employeeType = employeeTypeChoice;
            addEmployee(mainBakery, newEmployee);

            printf("Employee added successfully:\n");
            break;
        }
        case MENU_OPTIONS:
        {
            printf("Exiting...\n");
            break;
        }
        default:
            printf("Invalid option! Please choose again.\n");
            break;
        }
    } while (option != MENU_OPTIONS);
    freeBakery(mainBakery);
    return 0;
}
