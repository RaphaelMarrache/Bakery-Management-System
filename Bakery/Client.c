#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Client.h"

Client* createClient(const char* name, int age, int id) {
    Client* client = (Client*)malloc(sizeof(Client));
    if (client == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    client->name = (char*)malloc(strlen(name) + 1);
    if (client->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(client);
        exit(EXIT_FAILURE);
    }
    strcpy(client->name, name);
    client->age = age;
    client->id = id;
    client->next = NULL;
    return client;
}

void destroyClient(Client* client) {
    if (client != NULL) {
        free(client->name);
        free(client);
    }
}

void printClient(Client* client) {
    if (client == NULL) {
        return;
    }
    printf("Client - Name: %s,Age: %d, ID: %d\n", client->name, client->age, client->id);
}

void destroyLinkedList(Client* head) {
    Client* current = head;
    while (current != NULL) {
        Client* next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
}

void printLinkedList(Client* head) {
    Client* current = head;
    printf("Linked List of Clients:\n");
    while (current != NULL) {
        printClient(current);
        current = current->next;
    }
}

void saveClientToFile(Client* client, FILE* file) {
    fprintf(file, "%s,%d,%d\n", client->name, client->age, client->id);
}

Client* loadClientFromFile(FILE* file) {
    Client* client = (Client*)malloc(sizeof(Client));
    if (client == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    char name[50] = { 0 };
    int age, id,ignore;
    ignore = fscanf(file, "%[^,],%d,%d\n", name, &age, &id);
    client->name = (char*)calloc(100, sizeof(char));
    if (name != NULL && client->name != NULL) {
        strcpy(client->name, name);
    }
    client->age = age;
    client->id = id;
    client->next = NULL;
    return client;
}

int compareClientsByName(const void* a, const void* b) {
    return strcmp(((const Client*)a)->name, ((const Client*)b)->name);
}

int compareClientsById(const void* a, const void* b) {
    return ((const Client*)a)->id - ((const Client*)b)->id;
}

int compareClientsByAge(const void* a, const void* b) {
    return ((const Client*)a)->age - ((const Client*)b)->age;
}

Client* getClientInput() {
    Client* newClient = (Client*)calloc(1,sizeof(Client));
    if (newClient == NULL) {
        return NULL;
    }
    printf("Enter client name: ");
    char name[255] = { 0 };
    int ignore;
    ignore = scanf("%s", name);
    newClient->name = (char*)calloc(strlen(name) + 1, sizeof(char));
    if (newClient->name != NULL) {
        strcpy(newClient->name, name);
    }
    printf("Enter client age: ");
    ignore = scanf("%d", &newClient->age);
    printf("Enter client ID: ");
    ignore = scanf("%d", &newClient->id);
    return newClient;
}

void freeClient(Client* client) {
    if (client == NULL) {
        return;
    }
    free(client->name);
    free(client);

}

void freeClientLinkedList(void* head) {
    Client* orgHead = (Client*)head;
    Client* temp;
    while (orgHead != NULL)
    {
        temp = orgHead;
        orgHead = orgHead->next;
        freeClient(temp);
    }
    head = NULL;
}