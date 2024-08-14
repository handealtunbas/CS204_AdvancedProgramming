#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

//Hande Altunbas CS204 Spring 2024 Homework 2
using namespace std;

struct NodeLike  //NodeLike linkedlist taken from the homework 2 file
{
    string subject;
    string object;
    NodeLike* next;
};

struct NodeTaken //NodeTaken linkedlist taken from the homework 2 file
{
    string name;
    NodeTaken* next;
};

bool isInList(NodeLike* head, const string& firstname, const string& secondname) 
{
    //checks if firstname (ie. subject) and secondname (ie. object) is in the Nodelike list if so returns true if not returns false
    NodeLike* current = head;
    while (current != nullptr) 
    {
        if (current->subject == firstname && current->object == secondname)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool isNameTaken(NodeTaken* takenList, const string& name) //checks if the specific name is in the Nodetaken and returns true if not returns false
{
    NodeTaken* current = takenList;
    while (current != nullptr)
    {
        if (current->name == name)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void addToTakenList(NodeTaken*& takenList, const string& name) //adds name to the Takenlist alphabetically
{
    NodeTaken* newNode = new NodeTaken;
    newNode->name = name;
    newNode->next = nullptr;

    if (takenList == nullptr)
    {
        takenList = newNode;
    }
    else if (name < takenList->name) // Insert at the beginning
    {
        newNode->next = takenList;
        takenList = newNode;
    }
    else
    {
        NodeTaken* current = takenList;
        while (current->next != nullptr && current->next->name < name)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void addToLikeList(NodeLike*& likeList, const string& subject, const string& object) //add to the likelist by grouping the same subjects accordingly
{
    NodeLike* newNode = new NodeLike;
    newNode->subject = subject;
    newNode->object = object;
    newNode->next = nullptr;

    if (likeList == nullptr) 
    {
        likeList = newNode;
    } 
    else
    {
        NodeLike* current = likeList;
        NodeLike* lastNodeWithSameSubject = nullptr;
        while (current != nullptr) 
        {
            if (current->subject == subject) 
            {
                lastNodeWithSameSubject = current;
            }
            current = current->next;
        }
        if (lastNodeWithSameSubject != nullptr) 
        {
            // Insert after the last node with the same subject
            newNode->next = lastNodeWithSameSubject->next;
            lastNodeWithSameSubject->next = newNode;
        } 
        else
        {
            // Insert at the end of the list
            current = likeList;
            while (current->next != nullptr) 
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }
}


void removeFromLikeList(NodeLike*& likeList, const string& firstname, const string& secondname) 
{
    //In order to remove from the likelist we need a match and i need to remove each node that contains the taken people's names
    NodeLike* current = likeList;
    NodeLike* previous = nullptr;

    while (current != nullptr)
    {
        if (current->subject == firstname or current->object == secondname or current->subject == secondname or current->object == firstname) //checks if a node matches the firstname or secondname if so remove them
        {
            if (previous == nullptr)
            {
                likeList = current->next;
                delete current;
                current = likeList; // Move current to the next node
            }
            else
            {
                previous->next = current->next;
                delete current;
                current = previous->next; // Move current to the next node
            }
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}


void readFile(ifstream& filename, NodeLike*& likeList, NodeTaken*& takenList ) 
{
    //Begin: code taken from my previous homework (ie. Hande Altunbas' CS204 homework 1)
    string fileinput;
    cout << "Please enter the file name: ";
    cin >> fileinput;
    filename.open(fileinput);
    while (filename.fail()) 
    {
        cout << "\nCould not open the file. Please enter a valid file name: ";
        cin >> fileinput;
        filename.open(fileinput);
    }
    //End: code taken from my previous homework (ie. Hande Altunbas' CS204 homework 1)

    string line;
    int lineNum = 1; //I need to track line # in order to write them in the output
    while (getline(filename, line))
    {
        cout << "\nRead line number (" << lineNum << "): " << line << endl;
        lineNum++;

        string firstname, secondname;
        int likes_position = line.find("likes"); //finding likes index positon to divide firstname and secondname
        if (likes_position != string::npos) //if there is not any error (in this case there is not any issue since i do not need to check the file knowing that each line will be like subject likes object
        {
            firstname = line.substr(0, likes_position-1); //i put -1 since i do not want the blankspace
            secondname = line.substr(likes_position + 6); //getting the rest after the blankspace
            
            if (isNameTaken(takenList, firstname) || isNameTaken(takenList, secondname))
            {
                //checking whether the firstname or the secondname is in the taken list if so i need to write a message
                cout << "Either " << firstname << " or " << secondname << " or both is/are already taken, so the like relation is not added." << endl;
            }
            else
            {
                //now that i know the names are not in the takenlist i can check if they are in the likelist
                bool alreadyExists = isInList(likeList, secondname, firstname); //this helps me find a match
                if (!isInList(likeList, firstname, secondname)) //if it is not in the list i need to check if there is a match if so i need to add them to the takenlist if not i need to add them to the likedlist
                {
                    if (alreadyExists) //knowing that i have subject likes object , if the object likes subject already in the likedlist this means i need to remove the nodes containing their names from the liked list and add their names to the takenlist
                    {
                        addToTakenList(takenList, firstname);
                        addToTakenList(takenList, secondname);
                        removeFromLikeList(likeList, firstname, secondname);
                        removeFromLikeList(likeList, secondname, firstname);
                        cout << "Match found: " << firstname << " likes " << secondname << " and " << secondname << " likes " << firstname << "." << endl;
                        cout << "Added to taken list: " << firstname << endl;
                        cout << "Added to taken list: " << secondname << endl;
                        cout << "Any node that has " << firstname << " or " << secondname << " or both in it is removed from the likes list." << endl;
                    }
                    else //if object likes subject does not exist (again my line is subject likes object) it means there is no match so i can safely add them to the likedlist knowing that their names are also not in the takenlist since i already checked individually
                    {
                        addToLikeList(likeList, firstname, secondname);
                        cout << line << " relation has been added to the likes list." << endl;
                    }
                }
                else //isInList means the line is already in the likesnode so i cannot re-add them
                {
                    cout << line << " relation already exists in the likes list, so it is not added to it." << endl;
                }
            }
            cout << "Likes list: "; //now i can print out the like list
            NodeLike* currentLike = likeList;
            while (currentLike != nullptr) 
            {
                cout << "(" << currentLike->subject << ", " << currentLike->object << ") ";
                currentLike = currentLike->next;
            }
            cout << endl;

            cout << "Taken list: "; //i can print out the taken list
            NodeTaken* currentTaken = takenList;
            while (currentTaken != nullptr) 
            {
                cout << currentTaken->name << " ";
                currentTaken = currentTaken->next;
            }
            cout << endl;
        }
    }
}
void deleteList(NodeLike*& head) //this is for to delete like list now that i displayed everything
{
    while (head != nullptr)
    {
        NodeLike* temp = head;
        head = head->next;
        delete temp;
    }
}

void deleteList(NodeTaken*& head)  //this is for to delete taken list after displaying everything
{
    while (head != nullptr) 
    {
        NodeTaken* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() 
{
    NodeLike* likeList = nullptr;
    NodeTaken* takenList = nullptr;
    ifstream file;
    readFile(file, likeList, takenList);
    
    cout << "\nLists are deleted and the program ends successfully." << endl;

    // Delete lists to free memory
    deleteList(likeList);
    deleteList(takenList);
    
    return 0;
}


