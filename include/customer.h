#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 20
#include <time.h>
#include <stdbool.h>
#include"items.h"
#include <string.h>
#define EMPLOYEE_FILENAME "employees.txt"
#define CUSTOMERS_FILENAME "customers.txt"


typedef struct SoldItems {
    int id;
    char text1[20];
    char text2[20];
    float price;
    char SellingDate[11];
} SoldItems;

typedef struct SoldItemsNode
{
    struct SoldItems ItemsData;
    struct SoldItemsNode* next;
    struct SoldItemsNode* prev;
}SoldItemsNode;

typedef struct ListSoldItems
{
    SoldItemsNode* head;
    SoldItemsNode* tail;
}ListSoldItems;

typedef struct Customers {
    char name[20];
    char date[11];
    int phone;
    struct ListSoldItems* listItem;
}Customers;

typedef struct CustomerNode
{
    struct Customers custData;
    struct CustomerNode* next;
    struct CustomerNode* prev;
}CustomerNode;

typedef struct ListCustomers
{
    struct CustomerNode* head;
    struct CustomerNode* tail;
}ListCustomers;


void recordLogFile(char* str);
void currentdate(char* date);
void getString(char* str, char* input, int strSize);
ListCustomers* createCustomerList();
CustomerNode* createCustomerNode();
void insertToCustomersList(ListCustomers* list);
void createAndAddCustomer(ListCustomers* list);
void printListCustomers(ListCustomers* customerList);
ListSoldItems* createSoldItemsList();
SoldItemsNode* createSoldItemsNode();
void insertToSoldItemsList(ListSoldItems* list);
void addSoldItem(CustomerNode* customer, Item* item);
CustomerNode* FindCustomer(ListCustomers* list);
SoldItemsNode* FindItemInSoldItemListOfCustomer(CustomerNode* customerNode);
void printItemsList(ListSoldItems* list);
void displaySoldItemsList(ListCustomers* customerList);
void freeSoldItemsList(ListSoldItems* listItem);
void DeleteCustomer(ListCustomers* customerList);
void freeCustomersList(ListCustomers* list);
float Totalpurchase(CustomerNode* customerNode);
void DeleteItemFromList(ListSoldItems* solditemList, SoldItemsNode* itemNode);
int comparingDates(char* sellingDate);
int returnItemAfterFourteenDays(ListCustomers* customerList);
void WriteItemsToFile(SoldItemsNode* soldItemsNode, char* filename, int flag);
void addOrWriteCustomersToFile(CustomerNode* customerNode, char* filename, int flag);
void writeCustomersToFile(ListCustomers* customerList);
ListSoldItems* loadingItemsFromFile(long int ft);
void insertToCustomerList(ListCustomers* list);
ListCustomers* loadingCustomersFile();
void SellProduct(ItemNode* itemNode, ListCustomers* list);
int dailyPurchaseCheck(ListSoldItems* soldItemNode);

