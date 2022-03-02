#include "BinarySearchTree.h"
#include "List.h"
#include "Stack.h"

#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    BinarySearchTree bst;
    int input, id, age;
    string name;
    Employee newEmployee;

    while (1)
    {
        cout << "\nWelcome to the menu. Enter your choice as a number below.\n";
        cout << "1. Insert\n2. Remove\n3. Find\n4. Find Min\n";
        cout << "5. Find Max\n6. Make Empty\n7. Report\n8. Exit\n\n";
        cin >> input;


        switch (input)
        {
        case 1:		// Insert
            cout << "\nEnter the ID number: ";
            cin >> id;
            cout << "Enter the age: ";
            cin >> age;
            cout << "Enter the name: ";
            cin.ignore();
            getline(cin, name);

            newEmployee = Employee(id, age, name);

            bst.insert(newEmployee);

            cout << "\nEmployee Inserted";

            cout << "\nID: " << newEmployee.id << "\nAge: " << newEmployee.age << "\nName: " << newEmployee.name << "\n\n";
            break;

        case 2:		// Remove
            cout << "Enter the ID number of the employee to remove: ";
            cin >> id;
            bst.remove(id);
            break;

        case 3:		// Find
            cout << "Enter the ID number of the employee you wish to find: ";
            cin >> id;
            bst.find(id);
            cout << "\n";
            break;

        case 4:		// Find Min
            newEmployee = bst.findMin();
            cout << "Employee with lowest ID Number is:\n";
            cout << "ID: " << newEmployee.id << "\nAge: " << newEmployee.age << "\nName: " << newEmployee.name <<"\n";
            break;

        case 5:		// Find Max
            newEmployee = bst.findMax();
            cout << "Employee with highest ID Number is:\n";
            cout << "ID: " << newEmployee.id << "\nAge: " << newEmployee.age << "\nName: " << newEmployee.name<<"\n";
            break;

        case 6:		// Make Empty
            bst.makeEmpty();

            cout << "\nBinary search tree has been made empty.\n\n";
            break;

        case 7:		// Report
            cout << "\n";
            bst.report();
            break;

        case 8:     // Exit Program
            exit(0);

        default:	// Invalid input
            cout << "\nInvalid input, try again!\n\n";
        }
    }
}
