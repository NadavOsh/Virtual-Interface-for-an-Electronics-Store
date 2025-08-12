#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#include<stdlib.h>

#include <time.h>



typedef struct Item {
    int id;
    char Product[20];
    char Category[20];
    float price;
    bool inStock;
    char date[11];
    int inventory;
} Item;


typedef struct ItemNode {

    Item itemData;
    struct ItemNode* right, * left;
} ItemNode;



void printItem(ItemNode* Node);
void print_inorder(ItemNode* item);
void print_preorder(ItemNode* item);
ItemNode* createItemNode(int id, char* text1, char* text2, float price, bool inStock, char* date, int inventory);
void insert(ItemNode** Node, Item item);
void inOrderTraversal(ItemNode* root, FILE* file);
void writeItemsToFile(ItemNode* root, FILE* filename);



ItemNode* loadItems(char* filename);
Item* readItemsToArray(char* filename, int* size);
ItemNode* sortedArrayToBST(Item* arr, int start, int end);
ItemNode* newNode(Item data);


ItemNode* deleteNode(ItemNode* root, int key, int* flag1);
void subtractItem(ItemNode** root, int id);
void addItem(ItemNode** root);

int searchById(ItemNode* root, int id);
void printItemsGreaterThan(ItemNode* root, int id, int* num);
void printItemsSmallerThan(ItemNode* root, int id, int* num);
void printItemsAbovePrice(ItemNode* root, float price, int* num);
void printItemsBelowPrice(ItemNode* root, float price, int* num);
void printItemsByInStock(ItemNode* root, bool key, int* num);
int compareDates(char* date1, char* date2);
void printItemsBeforeDate(ItemNode* root, char* targetDate, int* num);
void printItemsAfterDate(ItemNode* root, char* targetDate, int* num);
void printItemsBetweenDates(ItemNode* root, char* startDate, char* endDate, int* num);
void printItemsWithText1(ItemNode* root, char* text1, int* num);
void printItemsWithText2(ItemNode* root, char* text2, int* num);
void printItemsWithBothTexts(ItemNode* root, char* text1, char* text2, int* num);
void SearchItem(ItemNode* root);
void FindItemForChange(ItemNode* root, int id);
void FindItem(ItemNode* root, int id, int* fla, Item* item);
int checkIfItemFileExists(char* customersFile);
void ChangeInventory(ItemNode* root, int id, int inventory, int* fla);