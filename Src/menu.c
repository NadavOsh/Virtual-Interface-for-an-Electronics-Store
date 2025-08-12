#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include <stdio.h>
#include "items.h"
#include "customer.h"
#include "employees.h"
#define EMPLOYEE_FILENAME "employees.txt"
#define CUSTOMERS_FILENAME "customers.txt"
#define ITEMS_FILENAME "item.txt"


void showMenu(unsigned int employeeLevel) {
    int Choice;
    employeeList* employeelist = loadingEmployeeFile();


    ItemNode* itemNode;

    if (checkIfItemFileExists("item.txt")) {
        itemNode = loadItems("item.txt");
    }
    else {
        itemNode = NULL;
    }



    employeeNode* employeeNode;
    ListCustomers* customerlist;
    if (checkIfCustomersFileExists("customers.txt")) {
        customerlist = loadingCustomersFile();

    }
    else {
        customerlist = createCustomerList();
    }

    int id, flag1 = 0;
    bool flag = 1;

    printf("Welcome to the menu:\n");


    if (employeeLevel == 1)
    {
        while (flag) {
            printf("--------------------\n");
            printf("1. Search Items\n");
            printf("2. Add Item\n");
            printf("3. Delete Item\n");
            printf("4. Add Customer\n");
            printf("5. Take down Customer\n");
            printf("6. Add Employee\n");
            printf("7. Sell Product\n");
            printf("8. Change Employee Level\n");
            printf("9. Return Item After 14 Days\n");
            printf("10. Display Customer's Items\n");
            printf("11. Delete Employee\n");
            printf("12. Change Item's Inventory Number\n");
            printf("13. See Employees List\n");
            printf("14. Exit\n");

            printf("Enter your choice: ");
            scanf("%d", &Choice);
            switch (Choice) {


            case 1:
                SearchItem(itemNode);
                break;


            case 2:
                addItem(&itemNode);
                recordLogFile("An Item Was Added - ");
                break;
            case 3:

                printf("Enter the id of the item you want to delete: ");
                scanf("%d", &id);
                itemNode = deleteNode(itemNode, id, &flag1);
                if (!flag1)
                    printf("\nThis item does not exist in the system\n");
                else
                {
                    printf("\nThe item has been removed\n");
                    recordLogFile("An Item Was Deleted - ");
                    flag1 = 0;
                }
                break;

            case 4:

                createAndAddCustomer(customerlist);
                recordLogFile("A New Customer Was Added - ");
                break;
            case 5:

                DeleteCustomer(customerlist);

                recordLogFile("A Customer Was Deleted - ");
                break;
            case 6:
                addEmployee(employeelist);
                recordLogFile("A New Employee Was Added - ");
                break;
            case 7:
                SellProduct(itemNode, customerlist);
                break;
            case 8:
                printf("Enter The New Employee Level \n1-Admin \n2-Employee \n3-Practitioner\n");
                scanf("%d", &Choice);
                if (Choice == 1 || Choice == 2 || Choice == 3) {
                    employeeNode = FindEmployee(employeelist);
                    if (employeeNode)
                    {
                        employeeNode->data->level = Choice;
                        printf("%s is now an employee with level %d\n", employeeNode->data->firstname, Choice);
                        recordLogFile("An Employee level Got Changed - ");
                    }
                }
                else printf("Invalid Chioce\n");
                break;
            case 9:
                Choice = returnItemAfterFourteenDays(customerlist);
                if (Choice)
                {
                    FindItemForChange(itemNode, Choice);
                }
                break;
            case 10:
                displaySoldItemsList(customerlist);
                break;
            case 11:
                removeEmployee(employeelist);
                break;
            case 12:
                printf("Enter The ID Of The Item: ");
                scanf("%d", &id);
                printf("Enter The New Invantory Number: ");
                scanf("%d", &Choice);
                ChangeInventory(itemNode, id, Choice, &flag1);
                if (!flag1)
                    printf("\nThis item does not exist in the system\n");
                else
                {
                    recordLogFile("Inventory Number Got Changed - ");
                    flag1 = 0;
                }
                break;
            case 13:
                displayEmployeeList(employeelist);
                break;
            case 14:
                printf("Exiting...\n");
                writeItemsToFile(itemNode, ITEMS_FILENAME);
                rewriteEmployyFile(employeelist);
                writeCustomersToFile(customerlist);
                recordLogFile("Exit System- ");
                flag = 0;
                break;
            default:
                printf("Invalid choice\n");
                break;
            }
        }
    }
    else if (employeeLevel == 2) {
        while (flag) {

            printf("--------------------\n");
            printf("1. Search items\n");
            printf("2. Add item\n");
            printf("3. Take down item\n");
            printf("4. Add customer\n");
            printf("5. Take down customer\n");
            printf("6. Sell Product\n");
            printf("7. Return Item After 14 Days\n");
            printf("8. Display Customer's Items\n");
            printf("9. Change Item's Inventory Number\n");
            printf("10. Exit\n");


            printf("Enter your choice: ");
            scanf("%d", &Choice);
            switch (Choice) {
            case 1:
                SearchItem(itemNode);
                break;


            case 2:
                addItem(&itemNode);
                recordLogFile("An Item Was Added - ");
                break;
            case 3:

                printf("Enter the id of the item you want to delete: ");
                scanf("%d", &id);
                itemNode = deleteNode(itemNode, id, &flag1);
                recordLogFile("An Item Was Deleted - ");
                break;

            case 4:
                createAndAddCustomer(customerlist);
                recordLogFile("A New Customer Was Added - ");
                break;

            case 5:
                DeleteCustomer(customerlist);
                recordLogFile("A Customer Was Deleted - ");
                break;
            case 6:
                SellProduct(itemNode, customerlist);

                break;
            case 7:
                Choice = returnItemAfterFourteenDays(customerlist);
                if (Choice)
                {
                    FindItemForChange(itemNode, Choice);
                }
                break;
            case 8:
                displaySoldItemsList(customerlist);
                break;
            case 9:
                printf("Enter The ID Of The Item: ");
                scanf("%d", &id);
                printf("Enter The New Invantory Number: ");
                scanf("%d", &Choice);
                ChangeInventory(itemNode, id, Choice, &flag1);
                recordLogFile("Inventory Number Got Changed - ");
                break;
            case 10:
                printf("Exiting...\n");
                writeItemsToFile(itemNode, ITEMS_FILENAME);
                rewriteEmployyFile(employeelist);
                writeCustomersToFile(customerlist);
                recordLogFile("Exit System- ");
                flag = 0;
                break;
            default:
                printf("Invalid choice\n");
                return;
            }
        }
    }
    else if (employeeLevel == 3) {
        while (flag) {
            printf("--------------------\n");
            printf("1. Search items\n");
            printf("2. Add item\n");
            printf("3. Add customer\n");
            printf("4. Sell Product\n");
            printf("5. Display Customer's Items\n");
            printf("6. Exit\n");

            printf("Enter your choice: ");
            scanf("%d", &Choice);
            switch (Choice) {
            case 1:
                SearchItem(itemNode);
                break;
            case 2:
                addItem(&itemNode);
                recordLogFile("An Item Was Added - ");
                break;
            case 3:
                createAndAddCustomer(customerlist);
                recordLogFile("A New Customer Was Added - ");
                break;
            case 4:
                SellProduct(itemNode, customerlist);
                recordLogFile("A Sell Was Made - ");

                break;
            case 5:
                displaySoldItemsList(customerlist);
                break;
            case 6:
                printf("Exiting...\n");
                writeItemsToFile(itemNode, ITEMS_FILENAME);
                rewriteEmployyFile(employeelist);
                writeCustomersToFile(customerlist);
                recordLogFile("Exit System- ");
                flag = 0;
                break;
            default:
                printf("Invalid choice\n");
                return;
            }
        }

    }if (employeeLevel != 1 && employeeLevel != 2 && employeeLevel != 3) {
        printf("Invalid employee level\n");
    }

    printf("--------------------\n");



}
