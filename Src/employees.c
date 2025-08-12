/*
תובל לנגנס - 205801095
נדב אושרוב - 318799806
*/
#define _CRT_SECURE_NO_WARNINGS
#include"employees.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EMPLOYEE_FILENAME "employees.txt"
#define MAXCHAR 20





employeeList* createEmployeeList()
{
    employeeList* list = NULL;
    if (NULL == (list = (employeeList*)malloc(sizeof(employeeList))))
    {
        printf("\n\nERROR!");
        return 0;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

employeeNode* createEmployeeNode()
{
    employeeNode* newNode = NULL;
    if (NULL == (newNode = (employeeNode*)malloc(sizeof(employeeNode))))
    {
        printf("ERROR!\n");
        return 0;
    }
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data = NULL;
    newNode->flag = 0;
    return newNode;
}

void insertToEmployeeList(employeeList* list)
{
    employeeNode* newNode = NULL;
    newNode = createEmployeeNode();
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
    list->size++;
    newNode->employeeNumber = list->size;
}

Employee* addEmployeeDetails() {
    char str[MAXCHAR];
    int sizestr = 0;
    Employee* employeeData = NULL;
    if (NULL == (employeeData = (Employee*)malloc(sizeof(Employee))))
    {
        printf("ERROR!\n");
        return 0;
    }

    do
    {
        if (sizestr > (MAXCHAR - 11))
        {
            printf("\nNo more than 9 letters");
        }
        printf("\nFirst name: ");
        scanf("%s", str);
        sizestr = strlen(str);
    } while (sizestr > (MAXCHAR - 11));
    strcpy(employeeData->firstname, str);
    do
    {
        if (sizestr > (MAXCHAR - 1))
        {
            printf("\nNo more than 19 digits");
        }
        printf("\nUser name: ");
        scanf("%s", str);
        sizestr = strlen(str);
    } while (sizestr > (MAXCHAR - 1));
    strcpy(employeeData->username, str);
    do
    {
        if (sizestr > (MAXCHAR - 11))
        {
            printf("\nNo more than 9 digits");
        }
        printf("\nPassword: ");
        scanf("%s", str);
        sizestr = strlen(str);
    } while (sizestr > (MAXCHAR - 11));
    strcpy(employeeData->password, str);
    employeeData->level = 3;
    return employeeData;
}

void addNewEmployeeToFile(employeeNode* employeeNode, char* filename)
{
    char str[MAXCHAR];
    int num, size;

    FILE* employeef = NULL;
    if (NULL == (employeef = fopen(filename, "a")))
    {
        printf("ERROR!\n");
        return;
    }
    strcpy(str, employeeNode->data->firstname);
    size = strlen(str);
    memset(str + size, ' ', 10 - size);
    strcpy(str, employeeNode->data->username);
    size = strlen(str);
    memset(str + size, ' ', 20 - size);
    strcpy(str, employeeNode->data->password);
    size = strlen(str);
    memset(str + size, ' ', 10 - size);
    num = employeeNode->data->level;
    fprintf(employeef, "%d ", num);
    num = employeeNode->employeeNumber;
    fprintf(employeef, "%d\n", num);
    recordLogFile("The new employee has been added to the employee file - ");
}

void addOrWriteEmployeeToFile(employeeNode* employeeNode, char* filename, int flag)
{
    char str[MAXCHAR + 1];
    int num, size;

    FILE* employeef = NULL;
    if (flag == 1)
    {
        if (NULL == (employeef = fopen(filename, "a")))
        {
            printf("ERROR!\n");
            return;
        }
    }
    else
    {
        if (NULL == (employeef = fopen(filename, "w")))
        {
            printf("ERROR!\n");
            return;
        }
        fputs("First_n	  User_n           password   lv. empl_num\n", employeef);
    }

    strcpy(str, employeeNode->data->firstname);
    size = strlen(str);
    memset(str + size, ' ', MAXCHAR - size);
    memset(str + 10, NULL, 1);
    fprintf(employeef, "%s", str);
    strcpy(str, employeeNode->data->username);
    size = strlen(str);
    memset(str + size, ' ', MAXCHAR - size);
    memset(str + 20, NULL, 1);
    fprintf(employeef, "%s", str);
    strcpy(str, employeeNode->data->password);
    size = strlen(str);
    memset(str + size, ' ', MAXCHAR - size);
    memset(str + 10, NULL, 1);
    fprintf(employeef, "%s", str);
    num = employeeNode->data->level;
    fprintf(employeef, "%d   ", num);
    num = employeeNode->employeeNumber;
    fprintf(employeef, "%d\n", num);
    fclose(employeef);
}

void addEmployee(employeeList* emplList)
{
    insertToEmployeeList(emplList);
    emplList->tail->data = addEmployeeDetails();
    printf("Registration was successful! Your employee number is %d\n", emplList->tail->employeeNumber);
    addOrWriteEmployeeToFile(emplList->tail, EMPLOYEE_FILENAME, 1);
}

void writeEmployeesToFile(employeeList* employeeList)
{
    employeeNode* currentNode;
    currentNode = employeeList->head;
    addOrWriteEmployeeToFile(currentNode, EMPLOYEE_FILENAME, 0);
    currentNode = currentNode->next;
    while (currentNode != NULL)
    {
        addOrWriteEmployeeToFile(currentNode, EMPLOYEE_FILENAME, 1);
        currentNode = currentNode->next;
    }
}


employeeList* createDefaultAdmin() {

    employeeList* emplList = createEmployeeList();
    insertToEmployeeList(emplList);
    emplList->tail->data = addEmployeeDetails();
    emplList->tail->data->level = 1;
    emplList->tail->employeeNumber = 1;
    writeEmployeesToFile(emplList, EMPLOYEE_FILENAME, 0);
    printf("Registration was successful! Your employee number is %d\n", emplList->tail->employeeNumber);
    recordLogFile("A list of employees has been created - ");
    return emplList;
}

employeeNode* FindEmployee(employeeList* list)
{
    employeeNode* currentNode = NULL;
    currentNode = list->head;
    int employeeNumber;

    printf("\nEnter your employee number: ");
    scanf("%d", &employeeNumber);

    while (currentNode != NULL)
    {

        if ((currentNode->employeeNumber) == employeeNumber)
        {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    printf("\nThis employee is not found in the system\n");
    return NULL;
}

void removeEmployee(employeeList* employeeList)
{
    employeeNode* currentNode = NULL;
    currentNode = FindEmployee(employeeList);
    if (currentNode == NULL)
        return;

    currentNode->prev->next = currentNode->next;
    if (currentNode->next != NULL)
        currentNode->next->prev = currentNode->prev;
    else
        employeeList->tail = currentNode->prev;
    printf("%s has been removed from the system.\n", currentNode->data->username);
    free(currentNode->data);
    free(currentNode);
    recordLogFile("Employee has been removed from the system - ");
}


employeeList* loadingEmployeeFile()
{
    FILE* employeef = NULL;
    if (NULL == (employeef = fopen(EMPLOYEE_FILENAME, "r")))
    {
        printf("ERROR!\n");
        return 0;
    }
    employeeList* emplList = NULL;
    char str[MAXCHAR], c;
    int num, size;

    emplList = createEmployeeList();
    fseek(employeef, -5, SEEK_END);
    fscanf(employeef, "%d", &num);
    emplList->size = num;

    if ((c = fgetc(employeef)) == EOF)
    {
        free(emplList);
        return NULL;
    }
    fseek(employeef, 50, SEEK_SET);
    while ((c = fgetc(employeef)) != EOF)
    {
        fseek(employeef, -1, SEEK_CUR);
        insertToEmployeeList(emplList);
        if (NULL == (emplList->tail->data = (Employee*)malloc(sizeof(Employee))))
        {
            printf("ERROR!\n");
            return 0;
        }
        fscanf(employeef, "%s ", emplList->tail->data->firstname);
        fscanf(employeef, "%s ", emplList->tail->data->username);
        fscanf(employeef, "%s ", emplList->tail->data->password);
        fscanf(employeef, "%d", &num);
        emplList->tail->data->level = num;
        fscanf(employeef, "%d ", &num);
        emplList->tail->employeeNumber = num;
    }
    emplList->size = emplList->tail->employeeNumber;
    fclose(employeef);
    return emplList;
}

int numberOfNodes(employeeList* employeeList)
{
    int counter = 0;
    employeeNode* currentNode;
    currentNode = employeeList->head;
    while (currentNode != NULL)
    {
        currentNode = currentNode->next;
        counter++;
    }
    return counter;
}


void rewriteEmployyFile(employeeList* employeeList)
{
    int sizeoflist = numberOfNodes(employeeList);
    while (sizeoflist > 0)
    {
        writeEmployeesToFile(employeeList);
        sizeoflist--;
    }
    recordLogFile("A list of employees was recorded in the file - ");
}


int checkIfEmployeeFileExists(char* emplyeesfile)
{
    char c;
    FILE* emplyeesf = NULL;
    if (NULL == (emplyeesf = fopen(emplyeesfile, "r")))
    {
        return 0;
    }

    if ((c = fgetc(emplyeesf)) == EOF)
    {
        return 0;
    }

    fclose(emplyeesf);
    return 1;
}

void displayEmployeeList(employeeList* employeeList)
{
    employeeNode* currentNode;
    currentNode = employeeList->head;
    int i = 1;
    printf("\n");
    while (currentNode != NULL)
    {
        printf("%d.First name:%s\n  User name:%s\n  Level:%d\n  Employee number:%.2d\n\n", i, currentNode->data->firstname, currentNode->data->username, currentNode->data->level, currentNode->employeeNumber);
        i++;
        currentNode = currentNode->next;
    }
    printf("\n");
}

void freeemployeeList(employeeList* list)
{
    employeeNode* currentNode;
    employeeNode* nextNode;
    currentNode = list->head;

    while (currentNode)
    {
        nextNode = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        currentNode = nextNode;
    }
    free(list);
    recordLogFile("The list is free - ");
}

Employee* employeeLogin(employeeList* list) {
    int employeeNumber, i;
    char tempstr1[MAXCHAR], tempstr2[MAXCHAR];
    employeeNode* currentNode = list->head;
    for (i = 0; i < 3; i++)
    {
        currentNode = FindEmployee(list);
        if (currentNode != NULL)
            break;
    }
    if (i == 3)
    {
        printf("Login failed: Invalid worker number.\n");
        return NULL;
    }

    for (i = 0; i < 3; i++)
    {
        printf("\nEnter your user name: ");
        scanf("%s", tempstr1);

        if ((strcmp(currentNode->data->username, tempstr1)) != 0)
        {
            printf("\nERROR! try again..");
        }
        else
        {
            printf("\nEnter your password: ");
            scanf("%s", tempstr2);
            if ((strcmp(currentNode->data->password, tempstr2)) == 0)
                break;
            printf("\nERROR! try again..");
        }
    }
    if (i < 3) {
        printf("Login successful! Welcome, %s (Level: %d)\n", currentNode->data->firstname, currentNode->data->level);
        currentNode->flag = 1;
    }
    else
    {
        printf("Login failed: Invalid username or password.\n");
        return NULL;
    }
    return currentNode->data;
}