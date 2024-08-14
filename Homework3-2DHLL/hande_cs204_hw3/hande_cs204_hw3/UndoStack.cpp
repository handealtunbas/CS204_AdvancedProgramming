//
// Created by Hande Altunbas on 1.04.2024.
//
#include <iostream>
#include "UndoStack.h"
using namespace std;
#include "UndoStack.h"

// Default constructor implementation
UndoStack::UndoStack() {
    top = nullptr; // Initialize top pointer to nullptr for an empty stack
}
void UndoStack::push(char operation, string employeeName, string projectName, int projectPriority)
{
    // Create a new stack node
    StackNode *newNode = new StackNode;
    newNode->operation = operation;
    newNode->employee_name = employeeName;
    newNode->project_name = projectName;
    newNode->project_priority = projectPriority;

    // Set the next pointer of the new node to point to the current top
    newNode->next = top;

    // Update the top pointer to the new node
    top = newNode;
}
bool UndoStack::isEmpty()
{
    return top == nullptr;
}

void UndoStack::pop(char & operation, string & employeeName, string & projectName, int & projectPriority)
{
    if (isEmpty())
    {
        // If the stack is empty, set the reference parameters to default values
        operation = '\0';
        employeeName = "";
        projectName = "";
        projectPriority = 0;
        return;
    }

    // Store the data from the top node
    operation = top->operation;
    employeeName = top->employee_name;
    projectName = top->project_name;
    projectPriority = top->project_priority;

    // Move the top pointer to the next node and deallocate the memory of the popped node
    StackNode *temp = top;
    top = top->next;
    delete temp;
}

void UndoStack::clear()
{
    while (top != nullptr)
    {
        StackNode *temp = top;
        top = top->next;
        delete temp;
    }
}






