#define _CRT_SECURE_NO_WARNINGS
#include "customer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include"items.h"
#include "employees.h"
#define MAXCHAR 20
#define EMPLOYEE_FILENAME "employees.txt"
#define CUSTOMERS_FILENAME "customers.txt"


void recordLogFile(char* str)
{
    FILE* logFile;
    logFile = fopen("logfile.txt", "a");
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    fputs(str, logFile);
    fprintf(logFile, "%s", asctime(ptr));
    fclose(logFile);
}

void currentdate(char* date)
{
    char str[11];
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    ptr->tm_mday;
    ptr->tm_mon + 1;
    ptr->tm_year + 1900;
    strftime(str, sizeof(str) + 1, "%F", ptr);
    strcpy(date, str);

}
void getString(char* str, char* input, int strSize)
{
    int sizeInput = 0, counter = 0;
    do
    {
        if (sizeInput > (strSize - 1))
        {
            printf("\nNo more than %d characters", (strSize - 1));
            counter++;
        }
        printf("\n%s", input);
        scanf("%s", str);
        sizeInput = strlen(str);
    } while (sizeInput > strSize);
}

ListCustomers* createCustomerList()
{
    ListCustomers* list;
    list = (ListCustomers*)malloc(sizeof(ListCustomers));
    list->head = list->tail = NULL;
    return list;
}

CustomerNode* createCustomerNode()
{
    CustomerNode* newNode = NULL;
    if (NULL == (newNode = (CustomerNode*)calloc(1, sizeof(CustomerNode))))
    {
        printf("ERROR!\n");
        return 0;
    }
    newNode->custData.listItem = NULL;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertToCustomersList(ListCustomers* list)
{
    CustomerNode* newNode = NULL;
    newNode = createCustomerNode();
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void createAndAddCustomer(ListCustomers* list) {

    insertToCustomersList(list);
    CustomerNode* newNode = list->tail;
    if (newNode == NULL) {
        printf("Error allocating memory for new customer.\n");
        return;
    }
    printf("Enter customer information:\n");
    getString(newNode->custData.name, "Name: ", 20);

    currentdate(newNode->custData.date);
    printf("Phone number: ");
    scanf("%d", &newNode->custData.phone);
    newNode->custData.listItem = NULL;

    printf("Customer added successfully!\n");
}

void printListCustomers(ListCustomers* customerList) {
    if (customerList == NULL || customerList->head == NULL) {
        printf("There are no customers to display.\n");
        return;
    }

    printf("Customer List:\n");

    CustomerNode* current = customerList->head;
    while (current != NULL) {
        printf("Name: %s\n", current->custData.name);
        printf("Date: %s\n", current->custData.date);
        printf("Phone: %d\n", current->custData.phone);

        if (current->custData.listItem != NULL && current->custData.listItem->head != NULL) {
            SoldItemsNode* soldItem = current->custData.listItem->head;
            printf("First Sold Item:\n");
            printf("  ID: %d\n", soldItem->ItemsData.id);
            printf("  Product: %s\n", soldItem->ItemsData.text1);
            printf("  Category: %s\n", soldItem->ItemsData.text2);
            printf("  Price: %.2f\n", soldItem->ItemsData.price);
            printf("  Selling Date: %s\n", soldItem->ItemsData.SellingDate);
        }
        else {
            printf("No sold items found for this customer.\n");
        }

        printf("\n");
        current = current->next;
    }
}

ListSoldItems* createSoldItemsList()
{
    ListSoldItems* list = (ListSoldItems*)malloc(sizeof(ListSoldItems));
    if (list == NULL) {
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

SoldItemsNode* createSoldItemsNode()
{
    SoldItemsNode* newNode = NULL;
    if (NULL == (newNode = (SoldItemsNode*)malloc(sizeof(SoldItemsNode))))
    {
        printf("ERROR!\n");
        return 0;
    }
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertToSoldItemsList(ListSoldItems* list)
{
    SoldItemsNode* newNode = NULL;
    newNode = createSoldItemsNode();
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void addSoldItem(CustomerNode* customer, Item* item) {
    if (customer == NULL || item == NULL) {
        printf("Error: Invalid customer or item.\n");
        return;
    }

    if (customer->custData.listItem == NULL) {
        customer->custData.listItem = createSoldItemsList();
    }

    insertToSoldItemsList(customer->custData.listItem);
    SoldItemsNode* newSoldItem = customer->custData.listItem->tail;
    newSoldItem->ItemsData.id = item->id;
    strcpy(newSoldItem->ItemsData.text1, item->Product);
    strcpy(newSoldItem->ItemsData.text2, item->Category);
    newSoldItem->ItemsData.price = item->price;
    currentdate(newSoldItem->ItemsData.SellingDate);
    printf("Sold item added successfully for customer: %s\n", customer->custData.name);
}

CustomerNode* FindCustomer(ListCustomers* list)
{
    int i, num;
    CustomerNode* currentNode = NULL;
    char str[MAXCHAR];

    for (i = 0; i < 3; i++)
    {
        currentNode = list->head;
        printf("\nEnter the customer's name: ");
        scanf("%s", &str);
        while (currentNode != NULL)
        {

            if (strcmp(currentNode->custData.name, str) == 0)
            {
                printf("\nPhone number: ");
                scanf("%d", &num);
                if (num == (currentNode->custData.phone))
                {
                    return currentNode;
                }

            }
            currentNode = currentNode->next;
        }
        printf("\nThe customer does not exist in the system\n");

    }

    return NULL;
}

SoldItemsNode* FindItemInSoldItemListOfCustomer(CustomerNode* customerNode)
{
    SoldItemsNode* currentNode = customerNode->custData.listItem->tail;
    if (currentNode == NULL)
        return NULL;
    else
    {
        int checkID;
        printf("\nID of item: ");
        scanf("%d", &checkID);

        while (currentNode != NULL)
        {
            if (checkID == currentNode->ItemsData.id)
            {
                return currentNode;
            }
            currentNode = currentNode->prev;
        }
    }
    return NULL;
}

void printItemsList(ListSoldItems* list)
{
    SoldItemsNode* itemsNode;
    itemsNode = list->head;
    int i = 1;
    printf("\n");
    fflush(stdin);
    while (itemsNode != NULL)
    {
        printf("%d.Item ID:%d\n  Selling date:%s\n  Item price:%.2f\n\n", i, itemsNode->ItemsData.id, itemsNode->ItemsData.SellingDate, itemsNode->ItemsData.price);
        i++;
        itemsNode = itemsNode->next;
    }
    printf("\n");
}

void displaySoldItemsList(ListCustomers* customerList)
{

    CustomerNode* custNode = FindCustomer(customerList);
    if (!custNode)
        return;
    if (custNode->custData.listItem)
        printItemsList(custNode->custData.listItem);
    else
        printf("\nThe customer didn't buy anything\n");
}

void freeSoldItemsList(ListSoldItems* listItem)
{

    SoldItemsNode* tempNode, * nexttempNode;
    tempNode = listItem->head;
    while (tempNode)
    {
        nexttempNode = tempNode->next;
        free(tempNode);
        tempNode = nexttempNode;
    }
    free(listItem);

}

void DeleteCustomer(ListCustomers* customerList)
{
    CustomerNode* custNode = NULL;
    custNode = FindCustomer(customerList);
    if (custNode == NULL) {
        return;
    }
    if (custNode->prev == NULL && custNode->next == NULL)
    {
        customerList->head = customerList->tail = NULL;
    }
    else if (custNode->prev == NULL && custNode->next != NULL)
    {
        custNode->next->prev = NULL;
        customerList->head = custNode->next;
    }
    else if (custNode->prev != NULL && custNode->next == NULL)
    {
        custNode->prev->next = NULL;
        customerList->tail = custNode->prev;
    }
    else
    {
        custNode->prev->next = custNode->next;
        custNode->next->prev = custNode->prev;
    }


    printf("%s has been removed from the system.\n", custNode->custData.name);
    if (custNode->custData.listItem)
        freeSoldItemsList(custNode->custData.listItem);
    free(custNode);
}

void freeCustomersList(ListCustomers* list)
{
    CustomerNode* currentNode;
    CustomerNode* nextNode;
    currentNode = list->head;

    while (currentNode)
    {
        nextNode = currentNode->next;
        if (currentNode->custData.listItem != NULL)
        {
            freeSoldItemsList(currentNode->custData.listItem);
        }
        free(currentNode);
        currentNode = nextNode;
    }
    free(list);
}

float Totalpurchase(CustomerNode* customerNode)
{
    float sum = 0;
    if (!customerNode->custData.listItem)
    {
        return 0;
    }
    SoldItemsNode* currentNode = customerNode->custData.listItem->head;

    if (currentNode == NULL)
    {
        return 0;
    }

    while (currentNode != NULL)
    {
        sum += (currentNode->ItemsData.price);
        currentNode = currentNode->next;
    }
    return sum;
}


void DeleteItemFromList(ListSoldItems* solditemList, SoldItemsNode* itemNode)
{
    if (itemNode == NULL) {
        return;
    }
    if (itemNode->prev == NULL && itemNode->next == NULL)
    {
        solditemList->head = solditemList->tail = NULL;
    }
    else if (itemNode->prev == NULL)
    {
        itemNode->next->prev = NULL;
        solditemList->head = itemNode->next;
    }
    else if (itemNode->next == NULL)
    {
        itemNode->prev->next = NULL;
        solditemList->tail = itemNode->prev;
    }
    else
    {
        itemNode->prev->next = itemNode->next;
        itemNode->next->prev = itemNode->prev;
    }


    printf("Item ID:%d has been removed from sold items list.\n", itemNode->ItemsData.id);
    free(itemNode);
}

int comparingDates(char* sellingDate)
{
    char currentDate[11];
    char tempsell[11];
    strcpy(tempsell, sellingDate);
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    ptr->tm_mday;
    ptr->tm_mon + 1;
    ptr->tm_year + 1900;

    strftime(currentDate, sizeof(currentDate) + 1, "%F", ptr);
    currentDate[4] = currentDate[7] = tempsell[4] = tempsell[7] = '\0';
    int numcur = (atoi(currentDate) - 2000);
    int numsell = (atoi(tempsell) - 2000);
    if (numcur > tempsell)
        return 12961;
    numcur = (atoi(currentDate + 5) * 26298) + (atoi(currentDate + 8) * 864);
    numsell = (atoi(tempsell + 5) * 26298) + (atoi(tempsell + 8) * 864);
    return (numcur - numsell);
}

int returnItemAfterFourteenDays(ListCustomers* customerList)
{
    int num;
    CustomerNode* customerNode = FindCustomer(customerList);
    if (customerNode == NULL)
    {
        return 0;
    }
    SoldItemsNode* itemNode = FindItemInSoldItemListOfCustomer(customerNode);
    if (itemNode == NULL)
    {
        printf("\nThe customer did not purchase this item\n");
        return 0;
    }

    num = comparingDates(itemNode->ItemsData.SellingDate);
    if (num <= 12960)
    {
        num = itemNode->ItemsData.id;
        printf("\nGive the customer a credit voucher for the cost of NIS %.2f\n", itemNode->ItemsData.price);
        recordLogFile("An Item Got Returned - ");
        DeleteItemFromList(customerNode->custData.listItem, itemNode);
        if (customerNode->custData.listItem->head == NULL)
        {
            free(customerNode->custData.listItem);
            customerNode->custData.listItem = NULL;
        }
        return num;
    }
    else
    {
        printf("\nThe product cannot be returned, more than 14 days have passed\n");
        return 0;
    }
}



void WriteItemsToFile(SoldItemsNode* soldItemsNode, char* filename, int flag)
{
    char str[MAXCHAR + 1];
    int num, size;
    float num1;
    FILE* customerf = NULL;
    if (flag == 1)
    {
        if (NULL == (customerf = fopen(filename, "a")))
        {
            printf("ERROR!\n");
            return;
        }
    }
    else
    {
        if (NULL == (customerf = fopen(filename, "a")))
        {
            printf("ERROR!\n");
            return;
        }
        fputs("L.I	ID  	Text1	        Text2		    Price	SellingDate\n", customerf);
    }

    num = soldItemsNode->ItemsData.id;
    fprintf(customerf, "%d  ", num);

    strcpy(str, soldItemsNode->ItemsData.text1);
    size = strlen(str);
    memset(str + size, ' ', MAXCHAR - size);
    memset(str + 20, NULL, 1);
    fprintf(customerf, "%s", str);

    strcpy(str, soldItemsNode->ItemsData.text2);
    size = strlen(str);
    memset(str + size, ' ', MAXCHAR - size);
    memset(str + 20, NULL, 1);
    fprintf(customerf, "%s", str);

    num1 = soldItemsNode->ItemsData.price;
    fprintf(customerf, "%.2f ", num1);

    strcpy(str, soldItemsNode->ItemsData.SellingDate);
    fprintf(customerf, "%s\n", str);
    fclose(customerf);
}

void addOrWriteCustomersToFile(CustomerNode* customerNode, char* filename, int flag)
{
    char str[MAXCHAR + 1];
    int num, size;
    float num1;
    FILE* customerf = NULL;
    if (flag == 1)
    {
        if (NULL == (customerf = fopen(filename, "a")))
        {
            printf("ERROR!\n");
            return;
        }
        fputs("\n", customerf);
    }
    else
    {
        if (NULL == (customerf = fopen(filename, "w")))
        {
            printf("ERROR!\n");
            return;
        }
        fputs("Customer name	Joining customers T.purchase Phone\n", customerf);
    }

    strcpy(str, customerNode->custData.name);
    size = strlen(str);
    memset(str + size, ' ', MAXCHAR - size);
    memset(str + 20, NULL, 1);
    fprintf(customerf, "%s", str);

    strcpy(str, customerNode->custData.date);
    fprintf(customerf, "%s  ", str);

    num1 = Totalpurchase(customerNode);
    fprintf(customerf, "%.2f   ", num1);

    num = customerNode->custData.phone;
    fprintf(customerf, "%d\n\n", num);
    fclose(customerf);


    ListSoldItems* temp = customerNode->custData.listItem;
    if (temp == NULL)
        return;

    SoldItemsNode* currentItemNode = temp->head;

    WriteItemsToFile(currentItemNode, CUSTOMERS_FILENAME, 0);
    currentItemNode = currentItemNode->next;
    while (currentItemNode != NULL)
    {
        WriteItemsToFile(currentItemNode, CUSTOMERS_FILENAME, 1);
        currentItemNode = currentItemNode->next;
    }
}

void writeCustomersToFile(ListCustomers* customerList)
{
    if (customerList->head == NULL)
    {
        printf("There are no registered customers. Nothing to write.\n");
        return;
    }
    CustomerNode* currentNode;
    currentNode = customerList->head;

    addOrWriteCustomersToFile(currentNode, CUSTOMERS_FILENAME, 0);
    currentNode = currentNode->next;
    while (currentNode != NULL)
    {
        addOrWriteCustomersToFile(currentNode, CUSTOMERS_FILENAME, 1);
        currentNode = currentNode->next;
    }
    recordLogFile("The customer was recorded in the file - ");
}

ListSoldItems* loadingItemsFromFile(long int ft)
{
    FILE* customerf = NULL;
    if (NULL == (customerf = fopen(CUSTOMERS_FILENAME, "r")))
    {
        printf("ERROR!\n");
        return 0;
    }
    ListSoldItems* itemsList = NULL;
    char str[MAXCHAR], c;
    int num, size;
    float num1;
    itemsList = createSoldItemsList();

    if ((c = fgetc(customerf)) == EOF)
    {
        free(itemsList);
        return NULL;
    }
    fseek(customerf, ft, SEEK_SET);
    if ((c = fgetc(customerf)) != 'L' || (c = fgetc(customerf)) == EOF)
    {
        if (c != EOF)
            fseek(customerf, -1, SEEK_CUR);
        free(itemsList);
        return NULL;
    }
    fseek(customerf, ft + 51, SEEK_SET);
    while ((c = fgetc(customerf)) != EOF)
    {
        if (('a' <= c && c >= 'z') || ('A' <= c && c >= 'Z'))
        {
            fseek(customerf, -1, SEEK_CUR);
            break;
        }
        fseek(customerf, -1, SEEK_CUR);
        insertToSoldItemsList(itemsList);

        fscanf(customerf, "%d  ", &num);
        itemsList->tail->ItemsData.id = num;

        fscanf(customerf, "%s ", itemsList->tail->ItemsData.text1);

        fscanf(customerf, "%s ", itemsList->tail->ItemsData.text2);

        fscanf(customerf, "%f ", &num1);
        itemsList->tail->ItemsData.price = num1;

        fscanf(customerf, "%s\n", itemsList->tail->ItemsData.SellingDate);

    }

    return itemsList;
}

void insertToCustomerList(ListCustomers* list)
{
    CustomerNode* newNode = NULL;
    newNode = createCustomerNode();
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}


ListCustomers* loadingCustomersFile()
{
    FILE* customerf = NULL;
    if (NULL == (customerf = fopen(CUSTOMERS_FILENAME, "r")))
    {
        printf("ERROR!\n");
        return 0;
    }
    ListCustomers* customerList = NULL;
    char str[MAXCHAR], c;
    int num, size;
    long int ft;
    customerList = createCustomerList();


    if ((c = fgetc(customerf)) == EOF)
    {
        free(customerList);
        return NULL;
    }
    fseek(customerf, 48, SEEK_SET);
    while ((c = fgetc(customerf)) != EOF)
    {
        fseek(customerf, -1, SEEK_CUR);
        insertToCustomerList(customerList);

        fscanf(customerf, "%s ", customerList->tail->custData.name);
        fscanf(customerf, "%s  ", customerList->tail->custData.date);
        fscanf(customerf, "%d", &num);
        fseek(customerf, 1, SEEK_CUR);
        fscanf(customerf, "%d   ", &num);
        fscanf(customerf, "%d", &num);
        customerList->tail->custData.phone = num;
        fscanf(customerf, "%d\n", &num);
        ft = ftell(customerf);
        fclose(customerf);
        (customerList->tail->custData.listItem) = loadingItemsFromFile(ft);
        if ((c = fgetc(customerf)) == EOF)
        {
            break;
        }
        else
        {
            fseek(customerf, -1, SEEK_CUR);

        }
    }
    fclose(customerf);
    return customerList;
}

int dailyPurchaseCheck(ListSoldItems* list)
{
    int i, num;
    SoldItemsNode* ptr = list->tail;
    for (i = 0; i < 3; i++)
    {
        if (ptr == NULL)
            return 0;
        num = comparingDates(ptr->ItemsData.SellingDate);
        if (!(num == 0))
            return 0;
        ptr = ptr->prev;
    }
    return 1;


}
void SellProduct(ItemNode* itemNode, ListCustomers* list) {
    int id, fla = 0;
    printf("Enter the ID of the item: \n");
    scanf("%d", &id);
    CustomerNode* customer = FindCustomer(list);
    if (!customer)
        return;
    if (customer->custData.listItem)
    {
        if (dailyPurchaseCheck(customer->custData.listItem))
        {
            printf("\nIt is not possible to buy more than three items on the same day\n");
            return;
        }
    }
    Item item;
    FindItem(itemNode, id, &fla, &item);
    if (!fla)
        printf("\nThis item does not exist in the system\n");
    else
    {
        addSoldItem(customer, &item);
        subtractItem(&itemNode, id);
        recordLogFile("A Sell Was Made - ");
    }

}


int checkIfCustomersFileExists(char* customersFile)
{
    char c;
    FILE* customersf = NULL;
    if (NULL == (customersf = fopen(customersFile, "r")))
    {
        return 0;
    }

    if ((c = fgetc(customersf)) == EOF)
    {
        return 0;
    }

    fclose(customersf);
    return 1;

}
