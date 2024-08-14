//
//  EmployeeProject2DLL.cpp
//  hande_cs204_hw3
//
//  Created by Hande Altunbas on 3.04.2024.
//
#include <iostream>
#include "EmployeeProject2DLL.h"
using namespace std;

EmployeeProject2DLL::EmployeeProject2DLL()
{
    head = nullptr;
}

ProjectNode* EmployeeProject2DLL::findProjectWithPriority(EmployeeNode* employee, int projectPriority)
{
    // Traverse through the projects of the employee
    ProjectNode* currentProject = employee->head;
    while (currentProject != nullptr) {
        if (currentProject->project_priority == projectPriority)
        {
            // Return the project node if found
            return currentProject;
        }
        currentProject = currentProject->next;
    }

    // If the project with the given priority is not found, return nullptr
    return nullptr;
}

bool EmployeeProject2DLL::isEmployeeAssignedToProject(string employeeName, string projectName)
{
    bool isAssigned = false;
    // Start traversing the linked list from the head
    EmployeeNode *currentEmployee = head;

    // Traverse the linked list of employees
    while (currentEmployee != nullptr)
    {
        // Check if the current employee's name matches the given employeeName
        if (currentEmployee->employee_name == employeeName)
        {
            // If the employee is found, check if they have the specified project assigned
            ProjectNode *currentProject = currentEmployee->head;
            while (currentProject != nullptr)
            {
                if (currentProject->project_name == projectName)
                {
                    // Project found, return true
                    isAssigned = true;
                }
                // Move to the next project
                currentProject = currentProject->next;
            }
            // If the project is not found for the employee, return false
        }
        // Move to the next employee
        currentEmployee = currentEmployee->down;
    }

    // If the employee is not found in the list, return false
    return isAssigned;
}

bool EmployeeProject2DLL::updateProjectPriority(string employeeName, string projectName, int &projectPriority) {
    bool isUpdated = false;
    int previousPriority = -1;
    EmployeeNode *currentEmployee = head;

    // Find the employee
    while (currentEmployee != nullptr && currentEmployee->employee_name != employeeName) 
    {
        currentEmployee = currentEmployee->down;
    }

    if (currentEmployee != nullptr) 
    {
        ProjectNode *currentProject = currentEmployee->head;

        // Find the project
        while (currentProject != nullptr && currentProject->project_name != projectName) 
        {
            currentProject = currentProject->next;
        }

        if (currentProject != nullptr) 
        {
            if (currentProject->project_priority == projectPriority) 
            {
                cout << "The project priority is already the same as the new priority." << endl;
                return false; // Return false immediately after encountering error
            } 
            else
            {
                // Check if there is another project with the same priority
                if (findProjectWithPriority(currentEmployee, projectPriority)) 
                {
                    cout << "The project priority has not been updated because there is another project with the same priority." << endl;
                    return false; // Return false immediately after encountering error
                }

                // Remove current project from the list
                if (currentProject->prev != nullptr) 
                {
                    currentProject->prev->next = currentProject->next;
                } 
                else
                {
                    currentEmployee->head = currentProject->next;
                }
                if (currentProject->next != nullptr) 
                {
                    currentProject->next->prev = currentProject->prev;
                } 
                else
                {
                    currentEmployee->tail = currentProject->prev;
                }

                // Update project priority and reposition it in the list
                previousPriority = currentProject->project_priority;
                currentProject->project_priority = projectPriority;

                // Insert the project back into the list in sorted order
                ProjectNode *prev = nullptr;
                ProjectNode *temp = currentEmployee->head;
                while (temp != nullptr && temp->project_priority <= projectPriority) 
                {
                    prev = temp;
                    temp = temp->next;
                }

                if (prev == nullptr) 
                {
                    // If the updated project becomes the new head
                    currentProject->next = currentEmployee->head;
                    currentProject->prev = nullptr;
                    if (currentEmployee->head != nullptr) 
                    {
                        currentEmployee->head->prev = currentProject;
                    } 
                    else
                    {
                        currentEmployee->tail = currentProject;
                    }
                    currentEmployee->head = currentProject;
                } 
                else
                {
                    prev->next = currentProject;
                    currentProject->prev = prev;
                    currentProject->next = temp;
                    if (temp != nullptr) 
                    {
                        temp->prev = currentProject;
                    } 
                    else
                    {
                        currentEmployee->tail = currentProject;
                    }
                }

                isUpdated = true;
            }
        }
    }

    projectPriority = previousPriority;
    return isUpdated;
}



bool EmployeeProject2DLL::assignEmployeeToProject(string employeeName, string projectName, int projectPriority)
{
    bool isAssigned = true;
    // Find the employee node or create a new one if it doesn't exist
    EmployeeNode *currentEmployee = head;
    EmployeeNode *prevEmployee = nullptr;
    
    while (currentEmployee != nullptr && currentEmployee->employee_name < employeeName)
    {
        prevEmployee = currentEmployee;
        currentEmployee = currentEmployee->down;
    }
    // If the employee node doesn't exist, create a new one
    if (currentEmployee == nullptr || currentEmployee->employee_name != employeeName)
    {
        EmployeeNode *newEmployee = new EmployeeNode;
        newEmployee->employee_name = employeeName;
        newEmployee->head = nullptr;
        newEmployee->tail = nullptr;
        newEmployee->down = currentEmployee;
        if (prevEmployee != nullptr)
        {
            prevEmployee->down = newEmployee;
        }
        else
        {
            head = newEmployee;
        }
        currentEmployee = newEmployee;
        
    }
    // Check if there is another project with the same priority
    if (findProjectWithPriority(currentEmployee, projectPriority))
    {
        // Display a message and return false
        cout << "The project has not been added because there is another project with the same priority." << endl;
        isAssigned = false;
    }
    else
    {
        // Create a new project node and assign it to the employee
        ProjectNode *newProject = new ProjectNode;
        newProject->project_name = projectName;
        newProject->project_priority = projectPriority;
        newProject->next = nullptr;
        newProject->prev = nullptr;

        // Add the project to the employee's project list while maintaining the ordering rules
        ProjectNode *prevProject = nullptr;
        ProjectNode *currentProject = currentEmployee->head;
        while (currentProject != nullptr && currentProject->project_priority < projectPriority)
        {
            prevProject = currentProject;
            currentProject = currentProject->next;
        }

        // Insert the new project node into the project list
        if (prevProject != nullptr)
        {
            prevProject->next = newProject;
            newProject->prev = prevProject;
        }
        else
        {
            currentEmployee->head = newProject;
        }
        newProject->next = currentProject;
        if (currentProject != nullptr)
        {
            currentProject->prev = newProject;
        }
        else
        {
            currentEmployee->tail = newProject;
        }
    }
    
    return isAssigned;
}

void EmployeeProject2DLL::withdrawEmployeeFromProject(string employeeName, string projectName, int &projectPriority)
{
    // Find the employee node
    EmployeeNode *currentEmployee = head;
    EmployeeNode *prevEmployee = nullptr;
    while (currentEmployee != nullptr && currentEmployee->employee_name != employeeName)
    {
        prevEmployee = currentEmployee;
        currentEmployee = currentEmployee->down;
    }
    if (currentEmployee != nullptr)
    {
        // Find the project node
        ProjectNode *currentProject = currentEmployee->head;
        while (currentProject != nullptr && currentProject->project_name != projectName)
        {
            currentProject = currentProject->next;
        }
        if (currentProject != nullptr)
        {
            // Update the reference parameter with the priority of the deleted project
            projectPriority = currentProject->project_priority;
            
            if (currentEmployee->head == currentEmployee->tail)
            {
                // If the project to be deleted is the only project that the employee has,
                // delete the employee node as well
                if (prevEmployee != nullptr)
                {
                    prevEmployee->down = currentEmployee->down;
                }
                else
                {
                    head = currentEmployee->down;
                }
                delete currentEmployee;
            }
            else if (currentProject == currentEmployee->head)
            {
                // If the project to be deleted is the first project in the list
                currentEmployee->head = currentProject->next;
                currentEmployee->head->prev = nullptr;
                delete currentProject;
            }
            else if (currentProject == currentEmployee->tail)
            {
                // If the project to be deleted is the last project in the list
                currentEmployee->tail = currentProject->prev;
                currentEmployee->tail->next = nullptr;
                delete currentProject;
            }
            else
            {
                // If the project to be deleted is in the middle of the list
                currentProject->prev->next = currentProject->next;
                currentProject->next->prev = currentProject->prev;
                delete currentProject;
            }
        }
    }
}

void EmployeeProject2DLL::printTheEntireList()
{
    if (head == nullptr)
    {
        // If the list is empty, print a specific message
        cout << "The list is empty." << endl;
        return;
    }

    // Traverse the linked list of employees
    EmployeeNode *currentEmployee = head;
    while (currentEmployee != nullptr)
    {
        cout << currentEmployee->employee_name << ": " ;

        // Traverse the linked list of projects for the current employee
        ProjectNode *currentProject = currentEmployee->head;
        while (currentProject != nullptr)
        {
            // Print project information
            cout << "(" << currentProject->project_name << ", " << currentProject->project_priority << ") ";
            currentProject = currentProject->next;
        }
        // Move to the next employee
        cout << endl;
        currentEmployee = currentEmployee->down;
    }
}

void EmployeeProject2DLL::printEmployeeProjects(string employeeName, int orderNum)
{
    // Check if the list is empty
    if (head == nullptr)
    {
        // If the list is empty, print a specific message
        cout << "There are no employees in the list." << endl;
    }
    else
    {
        // Find the employee node
        EmployeeNode *currentEmployee = head;
        while (currentEmployee != nullptr && currentEmployee->employee_name != employeeName)
        {
            currentEmployee = currentEmployee->down;
        }
        // Check if the employee node exists
        if (currentEmployee == nullptr)
        {
            // If the employee is not found in the list, print a specific message
            cout << "The employee is not in the list." << endl;
        }
        else
        {
            // Traverse the linked list of projects for the current employee
            if (orderNum == 1)
            { // Ascending order
                ProjectNode *currentProject = currentEmployee->head;
                while (currentProject != nullptr)
                {
                    cout << "(" << currentProject->project_name << ", " << currentProject->project_priority << ") ";
                    currentProject = currentProject->next;
                }
                cout << endl;
            }
            else
            {
                // Descending order
                ProjectNode *currentProject = currentEmployee->tail;
                while (currentProject != nullptr)
                {
                    cout << "(" << currentProject->project_name << ", " << currentProject->project_priority << ") ";
                    currentProject = currentProject->prev;
                }
                cout << endl;
            }
        }
    }
}

void EmployeeProject2DLL::undo(char operationType, string employeeName, string projectName, int projectPriority)
{
    if (operationType == 'a')
    {
        withdrawEmployeeFromProject(employeeName, projectName, projectPriority);
        cout << "Undoing the assignment of a project." << endl;
    }
    else if (operationType == 'w')
    {
        assignEmployeeToProject(employeeName, projectName, projectPriority);
        cout << "Undoing the withdrawal of a project." << endl;
    }
    else if (operationType == 'u')
    {
        updateProjectPriority(employeeName, projectName, projectPriority);
        cout << "Undoing the update of a project priority." << endl;
    }
}

void EmployeeProject2DLL::clear()
{
    // Traverse the linked list of employees
    while (head != nullptr)
    {
        // Delete projects for the current employee
        ProjectNode *currentProject = head->head;
        while (currentProject != nullptr)
        {
            ProjectNode *temp = currentProject;
            currentProject = currentProject->next;
            delete temp;
        }

        // Delete the current employee node
        EmployeeNode *temp = head;
        head = head->down;
        delete temp;
    }
}

