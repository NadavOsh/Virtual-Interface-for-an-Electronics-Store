/*
תובל לנגנס - 205801095
נדב אושרוב - 318799806
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include"items.h"
#include "employees.h"
#include "customer.h"
#define MAXCHAR 20
#define EMPLOYEE_FILENAME "employees.txt"
#define CUSTOMERS_FILENAME "customers.txt"
#define ITEMS_FILENAME "item.txt"



int main()

{
    recordLogFile("System start - ");

    employeeList* employeeList;
    if (!checkIfEmployeeFileExists("employees.txt")) {

        employeeList = createDefaultAdmin();




    }

    employeeList = loadingEmployeeFile();
    Employee* currentEmployee = employeeLogin(employeeList);


    if (currentEmployee)
        showMenu(currentEmployee->level);


    return 0;

}