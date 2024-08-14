#pragma once
#include <iostream>
using namespace std;

//
// Created by Hande Altunbas on 1.04.2024.
//
struct ProjectNode
{
    string project_name;
    int project_priority;
    ProjectNode * next;
    ProjectNode * prev;
};

struct EmployeeNode
{
    string employee_name;
    ProjectNode * head;
    ProjectNode * tail;
    EmployeeNode * down;
};


class EmployeeProject2DLL
{
private:
    EmployeeNode *head;
    ProjectNode* findProjectWithPriority(EmployeeNode* employee, int projectPriority);
public:
    EmployeeProject2DLL();
    bool isEmployeeAssignedToProject(string employeeName, string projectName);
    bool updateProjectPriority(string employeeName, string projectName, int & projectPriority);
    bool assignEmployeeToProject(string employeeName, string projectName,int projectPriority);
    void withdrawEmployeeFromProject(string employeeName, string projectName, int & projectPriority);
    void printTheEntireList();
    void printEmployeeProjects(string employeeName, int orderNum);
    void undo(char operationType, string employeeName, string projectName,int projectPriority);
    void clear();
};


