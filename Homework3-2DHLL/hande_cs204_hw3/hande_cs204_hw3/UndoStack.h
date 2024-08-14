#pragma once
#include <iostream>
using namespace std;
//CS204 - Spring'24 - Homework 3 by Hande Altunbas

struct StackNode
{
    char operation;
    string employee_name;
    string project_name;
    int project_priority;
    StackNode * next;
};

class UndoStack
{
private:
    StackNode * top;

public:
    UndoStack();
    void push(char operation, string employeeName, string projectName,int projectPriority);
    void pop(char & operation, string & employeeName, string & projectName,int & projectPriority);
    bool isEmpty();
    void clear();


};

