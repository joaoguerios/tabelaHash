#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100

typedef struct Contact {
    char name[50];
    char phone[20];
    struct Contact* next;
} Contact;

Contact* hashTable[TABLE_SIZE];

unsigned int hashFunction(const char* name) {
    unsigned int hash = 0;
    int i = 0;
    while (name[i] != '\0') {
        hash += name[i];
        i++;
    }
    return hash % TABLE_SIZE;
}

Contact* createContact(const char* name, const char* phone) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = NULL;
    return newContact;
}

void addContact(const char* name, const char* phone) {
    unsigned int index = hashFunction(name);
    Contact* newContact = createContact(name, phone);
    if (hashTable[index] == NULL) {
        hashTable[index] = newContact;
    } else {
        newContact->next = hashTable[index];
        hashTable[index] = newContact;
    }
    printf("Contato adicionado com sucesso.\n");
}

void searchContact(const char* name) {
    unsigned int index = hashFunction(name);
    Contact* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("Telefone de %s: %s\n", name, current->phone);
            return;
        }
        current = current->next;
    }
    printf("Contato não encontrado.\n");
}

void removeContact(const char* name) {
    unsigned int index = hashFunction(name);
    Contact* current = hashTable[index];
    Contact* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                hashTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Contato removido com sucesso.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Contato não encontrado.\n");
}

void showAllContacts() {
    int i = 0;
    Contact* current;
    while (i < TABLE_SIZE) {
        current = hashTable[i];
        while (current != NULL) {
            printf("Nome: %s, Telefone: %s\n", current->name, current->phone);
            current = current->next;
        }
        i++;
    }
}

int main() {
    int option;
    char name[50];
    char phone[20];
    clock_t start, end;
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    do {
        printf("\nEscolha uma opção:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opção: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                printf("Nome: ");
                scanf("%s", name);
                printf("Telefone: ");
                scanf("%s", phone);
                start = clock();
                addContact(name, phone);
                end = clock();
                printf("Tempo de inserção: %.2f ms\n", 1000.0 * (end - start) / CLOCKS_PER_SEC);
                break;
            case 2:
                printf("Nome: ");
                scanf("%s", name);
                start = clock();
                searchContact(name);
                end = clock();
                printf("Tempo de busca: %.2f ms\n", 1000.0 * (end - start) / CLOCKS_PER_SEC);
                break;
            case 3:
                printf("Nome: ");
                scanf("%s", name);
                removeContact(name);
                break;
            case 4:
                showAllContacts();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (option != 0);
    return 0;
}
