#define _CRT_SECURE_NO_WARNINGS
#include"items.h"
#include "customer.h"
#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#include<stdlib.h>
#define MAXCHAR 20
#define EMPLOYEE_FILENAME "employees.txt"
#define CUSTOMERS_FILENAME "customers.txt"
#include <time.h>


void printItem(ItemNode* Node) {
    if (Node != NULL) {
        printf("ID: %d\n", Node->itemData.id);
        printf("Product: %s\n", Node->itemData.Product);
        printf("Category: %s\n", Node->itemData.Category);
        printf("Price: %.2f\n", Node->itemData.price);
        printf("In Stock: %s\n", Node->itemData.inStock ? "Yes" : "No");
        printf("Date: %s\n", Node->itemData.date);
        printf("Inventory: %d\n", Node->itemData.inventory);
    }
}


void print_inorder(ItemNode* item)
{
    if (item)
    {
        print_inorder(item->left);
        printItem(item);
        print_inorder(item->right);
    }
}


void print_preorder(ItemNode* item)
{
    if (item)
    {
        printItem(item);
        print_preorder(item->left);
        print_preorder(item->right);
    }
}


ItemNode* createItemNode(int id, char* text1, char* text2, float price, bool inStock, char* date, int inventory) {
    Item newItem;
    newItem.id = id;
    strcpy(newItem.Product, text1);
    strcpy(newItem.Category, text2);
    newItem.price = price;
    newItem.inStock = inStock;
    strcpy(newItem.date, date);
    newItem.inventory = inventory;
    ItemNode* itemNode;
    itemNode = (ItemNode*)malloc(sizeof(ItemNode));


    itemNode->right = itemNode->left = NULL;
    itemNode->itemData = newItem;


    return itemNode;
}




void insert(ItemNode** Node, Item item) {
    ItemNode* temp = NULL;
    if (!(*Node)) {
        temp = (ItemNode*)malloc(sizeof(ItemNode));
        temp->left = temp->right = NULL;
        temp->itemData = item;
        *Node = temp;
        return;

    }

    if (item.id < (*Node)->itemData.id) {
        insert(&(*Node)->left, item);

    }
    else {
        insert(&(*Node)->right, item);

    }

}








void inOrderTraversal(ItemNode* root, FILE* file) {
    if (root != NULL) {
        inOrderTraversal(root->left, file);
        fprintf(file, "%d, %s, %s, %.2f, %d, %s, %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price, root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        inOrderTraversal(root->right, file);
    }
}




void writeItemsToFile(ItemNode* root, FILE* filename) {
    if (root == NULL) {
        printf("Tree is empty. Nothing to write.\n");
        return;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }


    fprintf(file, "ID, Product, Category, Price, In Stock, Date, Inventory\n");


    inOrderTraversal(root, file);

    fclose(file);
    printf("Items written to file 'item.txt' successfully.\n");
    recordLogFile("The items was recorded in the file - ");
}



ItemNode* readItemsFromFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return NULL;
    }


    char buffer[100];
    fgets(buffer, sizeof(buffer), file);

    ItemNode* root = NULL;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int id;
        char Product[20], Category[20], date[11];
        float price;
        int inStock;
        int inventory;
        sscanf(buffer, "%d, %[^,], %[^,], %f, %d, %[^,], %d", &id, Product, Category, &price, &inStock, date, &inventory);

        ItemNode* newItem = createItemNode(id, Product, Category, price, inStock, date, inventory);
        if (newItem != NULL) {
            insert(&root, newItem->itemData);
        }
        else {
            printf("Error creating item.\n");
        }
    }

    fclose(file);
    return root;
}








Item* readItemsToArray(char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return NULL;
    }

    char buffer[100];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        printf("Error reading first line of the file.\n");
        fclose(file);
        return NULL;
    }

    int numLines = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        numLines++;
    }

    rewind(file);

    Item* arr = (Item*)malloc(numLines * sizeof(Item));
    if (arr == NULL) {
        printf("Error allocating memory for array.\n");
        fclose(file);
        return NULL;
    }


    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        printf("Error reading second line of the file.\n");
        free(arr);
        fclose(file);
        return NULL;
    }


    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int id;
        char Product[20], Category[20], date[11];
        float price;
        int inStock;
        int inventory;
        int itemsRead = sscanf(buffer, "%d, %[^,], %[^,], %f, %d, %[^,], %d",
            &id, Product, Category, &price, &inStock, date, &inventory);

        if (itemsRead == 7) {
            arr[i].id = id;
            strcpy(arr[i].Product, Product);
            strcpy(arr[i].Category, Category);
            arr[i].price = price;
            arr[i].inStock = inStock;
            strcpy(arr[i].date, date);
            arr[i].inventory = inventory;
            i++;
        }

    }

    *size = numLines - 1;
    fclose(file);

    return arr;
}

ItemNode* newNode(Item data)
{
    ItemNode* node = (struct ItemNode*)malloc(sizeof(struct ItemNode));
    node->itemData = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}


ItemNode* sortedArrayToBST(Item* arr, int start, int end)
{
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    ItemNode* root = newNode(arr[mid]);


    root->left = sortedArrayToBST(arr, start, mid - 1);


    root->right = sortedArrayToBST(arr, mid + 1, end);

    return root;
}




ItemNode* loadItems(char* filename) {

    int size = 0;
    Item* arr = readItemsToArray(filename, &size);
    ItemNode* tree = sortedArrayToBST(arr, 0, size);
    return tree;

}





ItemNode* deleteNode(ItemNode* root, int key, int* flag1) {
    if (root == NULL) {
        return NULL;
    }
    if (key == root->itemData.id) {



        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }
        else if (root->left == NULL) {
            ItemNode* temp = root->right;
            free(root);
            root = temp;
        }
        else if (root->right == NULL) {
            ItemNode* temp = root->left;
            free(root);
            root = temp;
        }
        else {

            ItemNode* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->itemData = temp->itemData;
            root->right = deleteNode(root->right, temp->itemData.id, flag1);
        }
        (*flag1)++;
        return NULL;
    }

    if (key < root->itemData.id) {
        root->left = deleteNode(root->left, key, flag1);
    }
    if (key > root->itemData.id) {
        root->right = deleteNode(root->right, key, flag1);
    }


    return root;
}


void subtractItem(ItemNode** root, int id) {
    if ((*root) == NULL) {
        return;
    }

    if (id < (*root)->itemData.id) {
        subtractItem(&(*root)->left, id);
    }
    else if (id > (*root)->itemData.id) {
        subtractItem(&(*root)->right, id);
    }
    else {
        (*root)->itemData.inventory--;


        if ((*root)->itemData.inventory == 0) {

            (*root)->itemData.inStock = 0;
        }
        return;
    }


}



int searchById(ItemNode* root, int id) {
    if (root == NULL) {
        return 0;
    }

    if (id < root->itemData.id) {
        searchById(root->left, id);
    }
    else if (id > root->itemData.id) {
        searchById(root->right, id);
    }
    else {

        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        return 1;
    }
}



void printItemsGreaterThan(ItemNode* root, int id, int* num) {
    if (root == NULL) {
        return;
    }

    printItemsGreaterThan(root->left, id, num);

    if (root->itemData.id > id) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num) = id + 1;
    }

    printItemsGreaterThan(root->right, id, num);
}



void printItemsSmallerThan(ItemNode* root, int id, int* num) {
    if (root == NULL) {
        return;
    }


    printItemsSmallerThan(root->left, id, num);

    if (root->itemData.id < id) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num) = id + 1;
    }


    printItemsSmallerThan(root->right, id, num);
}




void printItemsAbovePrice(ItemNode* root, float price, int* num) {
    if (root == NULL) {
        return;
    }


    printItemsAbovePrice(root->left, price, num);


    if (root->itemData.price >= price) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num) = (int)price + 1;

        printItemsAbovePrice(root->right, price, num);
    }
    else {

        printItemsAbovePrice(root->right, price, num);
    }
}




void printItemsBelowPrice(ItemNode* root, float price, int* num) {
    if (root == NULL) {
        return;
    }


    printItemsBelowPrice(root->right, price, num);


    if (root->itemData.price <= price) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num) = (int)price + 1;

        printItemsBelowPrice(root->left, price, num);
    }
    else {

        printItemsBelowPrice(root->left, price, num);
    }
}


void printItemsByInStock(ItemNode* root, bool key, int* num) {
    if (root == NULL) {
        return;
    }

    printItemsByInStock(root->left, key, num);

    if (key ^ (root->itemData.inStock) == 0) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num)++;
    }

    printItemsByInStock(root->right, key, num);
}



int compareDates(char* date1, char* date2) {
    int day1, month1, year1;
    int day2, month2, year2;

    sscanf(date1, "%d-%d-%d", &day1, &month1, &year1);
    sscanf(date2, "%d-%d-%d", &day2, &month2, &year2);

    if (year1 < year2) {
        return -1;
    }
    else if (year1 > year2) {
        return 1;
    }
    else {
        if (month1 < month2) {
            return -1;
        }
        else if (month1 > month2) {
            return 1;
        }
        else {
            if (day1 < day2) {
                return -1;
            }
            else if (day1 > day2) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
}

void printItemsBeforeDate(ItemNode* root, char* targetDate, int* num) {
    if (root == NULL) {
        return;
    }
    printItemsBeforeDate(root->left, targetDate, num);

    if (compareDates(root->itemData.date, targetDate) < 0) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num)++;

    }


    if ((*num))
        printItemsBeforeDate(root->right, targetDate, num);
}

void printItemsAfterDate(ItemNode* root, char* targetDate, int* num) {
    if (root == NULL) {
        return;
    }


    printItemsAfterDate(root->right, targetDate, num);

    if (compareDates(root->itemData.date, targetDate) > 0) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num)++;

    }

    if ((*num))
        printItemsAfterDate(root->left, targetDate, num);
}




void printItemsBetweenDates(ItemNode* root, char* startDate, char* endDate, int* num) {
    if (root == NULL) {
        return;
    }


    printItemsBetweenDates(root->left, startDate, endDate, num);


    if (compareDates(root->itemData.date, startDate) >= 0 && compareDates(root->itemData.date, endDate) <= 0) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num)++;
    }


    printItemsBetweenDates(root->right, startDate, endDate, num);
}



void printItemsWithText1(ItemNode* root, char* text1, int* num) {
    if (root == NULL) {
        return;
    }


    printItemsWithText1(root->left, text1, num);


    if (strcmp(root->itemData.Product, text1) == 0) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num)++;
    }

    printItemsWithText1(root->right, text1, num);
}



void printItemsWithText2(ItemNode* root, char* text2, int* num) {
    if (root == NULL) {
        return;
    }



    printItemsWithText2(root->left, text2, num);


    if (strcmp(root->itemData.Category, text2) == 0) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num)++;
    }

    printItemsWithText2(root->right, text2, num);
}




void printItemsWithBothTexts(ItemNode* root, char* text1, char* text2, int* num) {
    if (root == NULL) {
        return;
    }



    printItemsWithBothTexts(root->left, text1, text2, num);


    if (strcmp(root->itemData.Product, text1) == 0 && strcmp(root->itemData.Category, text2) == 0) {
        printf("ID: %d, Product: %s, Category: %s, Price: %.2f, In Stock: %d, Date: %s, Inventory: %d\n",
            root->itemData.id, root->itemData.Product, root->itemData.Category, root->itemData.price,
            root->itemData.inStock, root->itemData.date, root->itemData.inventory);
        (*num)++;
    }

    printItemsWithBothTexts(root->right, text1, text2, num);
}






void SearchItem(ItemNode* root) {
    int choice;
    int id;
    float price;
    char text1[20], text2[20];
    char startDate[12], endDate[12];

    printf("\nChoose a search method:\n");
    printf("1. Search by ID\n");
    printf("2. Search for items greater than ID\n");
    printf("3. Search for items smaller than ID\n");
    printf("4. Search for items above a price\n");
    printf("5. Search for items below a price\n");
    printf("6. Search by in-stock status\n");
    printf("7. Search for items before a date\n");
    printf("8. Search for items after a date\n");
    printf("9. Search for items between two dates\n");
    printf("10. Search for items by product name\n");
    printf("11. Search for items by category\n");
    printf("12. Search for items by both product and category\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("Enter the ID to search: ");
        scanf("%d", &id);
        choice = searchById(root, id);
        if (!choice)
            printf("\nThis item does not exist in the system\n");
        break;
    case 2:
        printf("Enter the ID to search for items greater than: ");
        scanf("%d", &id);
        choice = id;
        printItemsGreaterThan(root, id, &choice);
        if (choice == id)
            printf("\nThere are no items with an ID number in this range\n");
        break;
    case 3:
        printf("Enter the ID to search for items smaller than: ");
        scanf("%d", &id);
        choice = id;
        printItemsSmallerThan(root, id, &choice);
        if (choice == id)
            printf("\nThere are no items with an ID number in this range\n");
        break;
    case 4:
        printf("Enter the price to search for items above: ");
        scanf("%f", &price);
        choice = (int)price;
        printItemsAbovePrice(root, price, &choice);
        if (choice == (int)price)
            printf("\nThere are no items in this price range\n");
        break;
    case 5:
        printf("Enter the price to search for items below: ");
        scanf("%f", &price);
        choice = (int)price;
        printItemsBelowPrice(root, price, &choice);
        if (choice == (int)price)
            printf("\nThere are no items in this price range\n");
        break;
    case 6:
        printf("Enter 1 to search for items in stock, 0 for out of stock: ");
        scanf("%d", &choice);
        id = 0;
        printItemsByInStock(root, choice, &id);
        if (!id)
        {
            if (!choice)
                printf("\nAll items in stock\n");
            else
                printf("\nThe store is empty\n");
        }
        break;
    case 7:
        printf("Enter the date to search for items before (dd-mm-yyyy): ");
        scanf("%s", startDate);
        choice = 0;
        printItemsBeforeDate(root, startDate, &choice);
        if (!choice)
            printf("\nThere are no items in this date range\n");
        break;
    case 8:
        printf("Enter the date to search for items after (dd-mm-yyyy): ");
        scanf("%s", startDate);
        choice = 0;
        printItemsAfterDate(root, startDate, &choice);
        if (!choice)
            printf("\nThere are no items in this date range\n");
        break;
    case 9:
        printf("Enter the start date (dd-mm-yyyy): ");
        scanf("%s", startDate);
        printf("Enter the end date (dd-mm-yyyy): ");
        scanf("%s", endDate);
        choice = 0;
        printItemsBetweenDates(root, startDate, endDate, &choice);
        if (!choice)
            printf("\nThere are no items in this date range\n");
        break;
    case 10:
        printf("Enter product: ");
        scanf("%s", text1);
        choice = 0;
        printItemsWithText1(root, text1, &choice);
        if (!choice)
            printf("\nThere is no item named: %s\n", text1);
        break;
    case 11:
        printf("Enter category: ");
        scanf("%s", text2);
        choice = 0;
        printItemsWithText2(root, text2, &choice);
        if (!choice)
            printf("\nThere are no items in category\n");
        break;
    case 12:
        printf("Enter product: ");
        scanf("%s", text1);
        printf("Enter category: ");
        scanf("%s", text2);
        choice = 0;
        printItemsWithBothTexts(root, text1, text2, &choice);
        if (!choice)
            printf("\nThere is no item named: %s in %s category\n", text1, text2);
        break;
    default:
        printf("Invalid choice. Please try again.\n");
    }
}


void addItem(ItemNode** root) {

    int id, inventory;
    char text1[20], text2[20], date[11];
    float price;
    bool inStock = 1;
    getString(text1, "Enter Product's Name: ", 20);

    getString(text2, "Enter Category: ", 20);

    printf("Enter Product's ID: ");
    scanf("%d", &id);
    printf("Enter Product's price: ");
    scanf("%f", &price);

    getString(date, "Enter Date (dd-mm-yyyy): ", 11);

    printf("Enter Inventory: ");
    scanf("%d", &inventory);
    if (inventory == 0) {
        inStock = 0;
    }


    Item newItem;
    newItem.id = id;
    strcpy(newItem.Product, text1);
    strcpy(newItem.Category, text2);
    newItem.price = price;
    newItem.inStock = inStock;
    strcpy(newItem.date, date);
    newItem.inventory = inventory;

    insert(root, newItem);

}

void FindItemForChange(ItemNode* root, int id)
{
    if (root == NULL) {
        return;
    }

    if (id < root->itemData.id) {
        FindItemForChange(root->left, id);
    }
    else if (id > root->itemData.id) {
        FindItemForChange(root->right, id);
    }
    else {
        root->itemData.inventory++;
        if (!root->itemData.inStock)
            root->itemData.inStock = 1;
        return;
    }
}

void FindItem(ItemNode* root, int id, int* fla, Item* item)
{
    if (root == NULL) {
        return;
    }

    else if (id < root->itemData.id) {
        FindItem(root->left, id, fla, item);
    }
    else if (id > root->itemData.id) {
        FindItem(root->right, id, fla, item);
    }
    else {
        (*fla)++;
        (*item) = root->itemData;
    }
}


int checkIfItemFileExists(char* itemFile)
{
    char c;
    FILE* itemf = NULL;
    if (NULL == (itemf = fopen(itemFile, "r")))
    {
        return 0;
    }

    if ((c = fgetc(itemf)) == EOF)
    {
        return 0;
    }

    fclose(itemf);
    return 1;
}



void ChangeInventory(ItemNode* root, int id, int inventory, int* fla)
{
    if (root == NULL) {
        return;
    }

    if (id < root->itemData.id) {
        FindItemForChange(root->left, id, fla);
    }
    else if (id > root->itemData.id) {
        FindItemForChange(root->right, id, fla);
    }
    else {
        root->itemData.inventory = inventory;
        root->itemData.inStock = 1;
        if (!inventory)
            root->itemData.inStock = 0;
        (*fla)++;
        return;
    }

}
