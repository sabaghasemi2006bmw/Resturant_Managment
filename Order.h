#pragma once
#include <iostream>
using namespace std;


struct Food {
    string name;
    Food* next;
    Food(string name) : name(name), next(nullptr) {}
};


class Order {
public:
    string studentFirstName;
    string studentLastName;
    string studentID;
    int orderNumber;
    string orderStatus; // "In Progress", "Delivered", "Canceled"
    Food* itemsHead;    // Head of Foods linked list
    int countItems;
    Order();
    ~Order();

    void addItem(string name);
    void displayItems();
    bool removeItem(string name);
};