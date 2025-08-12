#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 20
#include <time.h>

typedef struct tm tm;

typedef struct employee {
	char username[20];
	char firstname[10];
	char password[10];
	unsigned int level;
} Employee;

typedef struct employeeNode {
	int flag;
	int employeeNumber;
	Employee* data;
	struct employeeNode* next;
	struct employeeNode* prev;
} employeeNode;

typedef struct List
{
	employeeNode* head;
	employeeNode* tail;
	int size;
}employeeList;


employeeList* createEmployeeList();
employeeNode* createEmployeeNode();
void insertToEmployeeList(employeeList* list);
Employee* addEmployeeDetails();
void addNewEmployeeToFile(employeeNode* employeeNode, char* filename);
void addOrWriteEmployeeToFile(employeeNode* employeeNode, char* filename, int flag);
void addEmployee(employeeList* emplList);
void writeEmployeesToFile(employeeList* employeeList);
employeeList* createDefaultAdmin();
employeeNode* FindEmployee(employeeList* list);
void removeEmployee(employeeList* employeeList);
employeeList* loadingEmployeeFile();
int numberOfNodes(employeeList* employeeList);
void rewriteEmployyFile(employeeList* employeeList);
int checkIfEmployeeFileExists(char* emplyeesfile);
void displayEmployeeList(employeeList* employeeList);
void freeemployeeList(employeeList* list);
Employee* employeeLogin(employeeList* list);