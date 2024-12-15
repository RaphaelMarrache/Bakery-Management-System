#ifndef CLIENT_H
#define CLIENT_H
#pragma warning(disable:4996)
#include <stdlib.h>
typedef struct Client {
    char* name;
    int age;
    int id;
    struct Client* next; 
} Client;

Client* createClient(const char* name, int age, int id);
void destroyClient(Client* client);
void printClient(Client* client);
void destroyLinkedList(Client* head);
void printLinkedList(Client* head);
void saveClientToFile(Client* client, FILE* file);
Client* loadClientFromFile(FILE* file);
int compareClientsByName(const void* a, const void* b);
Client* getClientInput();
int compareClientsById(const void* a, const void* b);
int compareClientsByAge(const void* a, const void* b);
void freeClient(Client* client);
void freeClientLinkedList(void* head);
#endif
