#pragma once
#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>
#include "Order.h"

using namespace std;

const string FILENAME = "orders.txt";

struct OrderNode {
    Order orderData;
    OrderNode* next;

    OrderNode() : next(nullptr) {}
};

class OrderList {
private:
    OrderNode* head;
    int nextOrderNumber;

    Order* findOrder(int orderNum);
    int getIntInput();
public:
    OrderList();
    ~OrderList();
    void displayMenu();
    void addNewOrder();
    void markOrderDelivered();
    void cancelOrder();
    void changeOrder();
    void reviewAllOrders();
    void saveToFile();
    void loadFromFile();
};

void setConsoleColor(int color);