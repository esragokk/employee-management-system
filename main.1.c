#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Include for isdigit function

// Defining a linked list "employee" for employee management system 
struct employee { 
    char name[50]; //maximum 50 characters can be hold in memory for each employee
    int employee_id;
    char position[50];
    float salary;
    struct employee* next;
};

struct employee* head = NULL;

// Defining a function for checking is employee with the given name already exists
int checkDuplicate(char* name) {
    struct employee* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // Returning 1 when the given name already exists(duplicate situations)
            return 1; // Duplicate
        }
        current = current->next; 
    }
    return 0; // There is not a duplicate situation, given name does not exist
}

// Defining a function for adding a new employee to the linked list
void addEmployee(char* name, int employee_id, char* position, float salary) {
    // Checking duplicate situations before adding
    if (checkDuplicate(name)) {
        printf("Employee with the same name already exists. Cannot add duplicate employee.\n");
        return;// the name of new employee is already in the list 
    }

    // Allocate node for new employee
    struct employee* new_employee = (struct employee*)malloc(sizeof(struct employee));
    if (new_employee == NULL) {
        // Handle memory allocation failure situation 
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy data to the new employee node
    strcpy(new_employee->name, name);
    new_employee->employee_id = employee_id;
    strcpy(new_employee->position, position);
    new_employee->salary = salary;
    new_employee->next = NULL;

    // If the linked list is empty, setting the new employee as the head
    if (head == NULL) {
        head = new_employee;
    } else { //linked is not empty
        // Traversing the linked list to find the last node for addition 
        struct employee* current = head;
        while (current->next != NULL) {
            current = current->next;
        }

        // Adding the new employee at the end of the linked list
        current->next = new_employee;
    }
}

// Defining a function to delete the employee information with a given name
void deleteEmployee(char* name) {
    struct employee* current = head;
    struct employee* prev = NULL; 

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // Employee with the given name exists and found
            if (prev == NULL) {
                // employee is at the head of the list situation
                head = current->next;
            } else {
                // employee is not at the head of the list situation
                prev->next = current->next;
            }

            //  Free the memory of the deleted employee 
            free(current);
            printf("Deleting '%s':\n",name);
            printf("Employee '%s' deleted successfully.\n", name);
            return;
        }

        prev = current;
        current = current->next;
    }

    //employee with the given name is not in the list
    printf("Employee '%s' not found. Deletion failed.\n", name);
}

// Defining a function to search for an employee with given name and print the employee informaiton 
void searchEmployee(char* name) {
    struct employee* current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // Employee with the given name exists and found
            printf("Searching for '%s':\n",name);
            printf("Employee ID: %d\nPosition: %s\nSalary: $%.2f\n",
                   current->employee_id, current->position, current->salary);
            return;
        }
        current = current->next;
    }

    // employee with the given name is not in the list 
    printf("Employee '%s' not found.\n", name);
}

// Defining a function to display all employees and informations in the order they are stored in the list
void displayEmployees() {
    struct employee* current = head;

    if (current == NULL) { //when linked list is empty
        printf("No employees in the list.\n");
        return;
    }

    while (current != NULL) { // at least one employee exists in the list
        printf("Displaying all employees: \n");
        printf("name: %s\nid: %d\nposition: %s\nsalary: $%.2f\n", current->name, current->employee_id, current->position, current->salary);// printing employee information
        for (int i = 0; i < 30; i++) {
            printf("-");
        }
        printf("\n");
        current = current->next;
    }
}

int main() { 
    char name[50];
    int employee_id;
    char position[50];
    float salary;
    int choice;
    int inputSuccess;

    do {
        // Display menu for Employee Management System
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Search Employee\n");
        printf("4. Display Employees\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        // choosing a function from menu  
        inputSuccess = scanf("%d", &choice);

        if (inputSuccess != 1) {
            //  input is not a valid integer handling error situation for entering letters 
            printf("Invalid input. Please enter a valid number.\n");

            // Clear the input buffer
            while (getchar() != '\n');

            continue; // Skiping rest of the loop and restarting
        }

        switch (choice) {
            case 1:
                // Adding a new employee by asking employee information from the user
                do {
                    printf("Name: ");
                    scanf(" %49[^\n]", name);

                    // if case for validate name error
                    if (strlen(name) == 0) {
                        printf("Invalid name. Please enter a valid name.\n");
                    }
                } while (strlen(name) == 0);

                do {
                    printf("Employee ID: ");
                    inputSuccess = scanf("%d", &employee_id);

                    // if case for validate employee ID
                    if (inputSuccess != 1 || employee_id <= 0) {
                        printf("Invalid employee ID. Please enter a positive integer.\n");
                        // Clear the input buffer
                        while (getchar() != '\n');
                    }
                } while (inputSuccess != 1 || employee_id <= 0);

                do {
                    printf("Position: ");
                    scanf(" %49[^\n]", position);

                    // if case for validate position
                    if (strlen(position) == 0) {
                        printf("Invalid position. Please enter a valid position.\n");
                    }
                } while (strlen(position) == 0);

                do {
                    printf("Salary: $");
                    inputSuccess = scanf("%f", &salary);

                    // if case for validate salary
                    if (inputSuccess != 1 || salary < 0) {
                        printf("Invalid salary. Please enter a non-negative number.\n");
                        // Clear the input buffer
                        while (getchar() != '\n');
                    }
                } while (inputSuccess != 1 || salary < 0);

                addEmployee(name, employee_id, position, salary);
                break;

            case 2:
                // Deleting an employee with given name from the list 
                do {
                    printf("\nEnter the name of the employee to delete: ");
                    scanf(" %49[^\n]", name);

                    // if case for validate name
                    if (strlen(name) == 0) {
                        printf("Invalid name. Please enter a valid name.\n");
                    }
                } while (strlen(name) == 0);

                deleteEmployee(name);
                break;

            case 3:
                // Searching for an employee with given name
                do {
                    printf("\nEnter the name of the employee to search: ");
                    scanf(" %49[^\n]", name);

                    // if case for validate name
                    if (strlen(name) == 0) {
                        printf("Invalid name. Please enter a valid name.\n");
                    }
                } while (strlen(name) == 0);

                searchEmployee(name);
                break;

            case 4:
                // Displaying all employees that are stored in linked list
                displayEmployees();
                for (int i = 0; i < 20; i++) {
                    printf("-");
                }
                break;

            case 5:
                // Exiting the program
                printf("Exiting the program.\n");
                break;

            default:
                // Invalid choice for entering numbers are not between 1 and 5 
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }

    } while (choice != 5);

    // Free the memory allocated for the linked list
    struct employee* next;
    struct employee* current = head;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}


