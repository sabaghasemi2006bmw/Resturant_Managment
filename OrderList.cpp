#include "OrderList.h"
#include <windows.h>

void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Order* OrderList::findOrder(int orderNum) {
    OrderNode* temp = head;
    for (; temp != nullptr;) {
        if (temp->orderData.orderNumber == orderNum) {
            return &(temp->orderData);
        }
        temp = temp->next;
    }
    return nullptr;
}
int OrderList::getIntInput() {
    int choice;
    while (!(cin >> choice)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

OrderList::OrderList() {
    loadFromFile();
    head = nullptr;
    nextOrderNumber = 1;
}
OrderList::~OrderList() {
    saveToFile();
    OrderNode* current = head;
    for (; current != nullptr;) {
        OrderNode* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}
void OrderList::displayMenu() {
    cout << "\n--- Restaurant Menu ---" << endl;
    cout << "  Foods:" << endl;
    cout << "    1. Pizza" << endl;
    cout << "    2. Burger" << endl;
    cout << "    3. Pasta" << endl;
    cout << "  Drinks:" << endl;
    cout << "    4. Cola" << endl;
    cout << "    5. Juice" << endl;
    cout << "  Appetizers:" << endl;
    cout << "    6. Fries" << endl;
    cout << "    7. Salad" << endl;
    cout << "-----------------------" << endl;
}
void OrderList::addNewOrder() {
    OrderNode* newNode = new OrderNode();

    cout << "Enter student first name: ";
    getline(cin, newNode->orderData.studentFirstName);
    cout << "Enter student last name : ";
    getline(cin, newNode->orderData.studentLastName);
    cout << "Enter student ID: ";
    getline(cin, newNode->orderData.studentID);

    newNode->orderData.orderNumber = nextOrderNumber;
    nextOrderNumber++;
    newNode->orderData.orderStatus = "In Progress";

    cout << "Registering Order #" << newNode->orderData.orderNumber << endl;

    int choice = -1;
    while (true) {
        system("cls || clear");
        displayMenu();
        cout << "Your orders:" << endl;
        newNode->orderData.displayItems();
        cout << "***********************************************" << endl;
        cout << "Add items to the order." << endl;
        cout << "Enter item number to add (1-7) or 0 to finish: ";
        choice = getIntInput();

        string item;
        switch (choice) {
        case 1: item = "Pizza"; break;
        case 2: item = "Burger"; break;
        case 3: item = "Pasta"; break;
        case 4: item = "Cola"; break;
        case 5: item = "Juice"; break;
        case 6: item = "Fries"; break;
        case 7: item = "Salad"; break;
        case 0: break;
        default: cout << "Invalid choice." << endl; continue;
        }

        if (choice == 0) {
            if (newNode->orderData.itemsHead == nullptr) {
                cout << "Order is empty! Please add at least one item." << endl;
            }
            else {
                break;
            }
        }
        else {
            newNode->orderData.addItem(item);
            cout << "Added " << item << "." << endl;
        }
    }

    newNode->next = head;
    head = newNode;

    cout << "Order #" << newNode->orderData.orderNumber << " registered successfully." << endl;
    saveToFile();

}
void OrderList::markOrderDelivered() {
    cout << "Enter order number to mark as delivered: ";
    int orderNum = getIntInput();

    Order* order = findOrder(orderNum);
    if (order != nullptr) {
        order->orderStatus = "Delivered";
        cout << "Order #" << orderNum << " marked as 'Delivered'." << endl;
        saveToFile();
    }
    else {
        cout << "Error: Order #" << orderNum << " not found." << endl;
    }
}
void OrderList::cancelOrder() {
    cout << "Enter order number to cancel: ";
    int orderNum = getIntInput();

    Order* order = findOrder(orderNum);
    if (order != nullptr) {
        if (order->orderStatus == "Delivered") {
            cout << "Error: Cannot cancel an order that is already 'Delivered'." << endl;
        }
        else {
            order->orderStatus = "Canceled";
            cout << "Order #" << orderNum << " marked as 'Canceled'." << endl;
            saveToFile();
        }
    }
    else {
        cout << "Error: Order #" << orderNum << " not found." << endl;
    }
}
void OrderList::changeOrder() {
    cout << "Enter order number to modify: ";
    int orderNum = getIntInput();

    Order* order = findOrder(orderNum);
    if (order == nullptr) {
        cout << "Error: Order #" << orderNum << " not found." << endl;
        return;
    }

    if (order->orderStatus != "In Progress") {
        cout << "Error: Can only modify orders that are 'In Progress'." << endl;
        cout << "This order's status is: " << order->orderStatus << endl;
        return;
    }

    while (true) {
        cout << "\nModifying Order #" << orderNum << endl;
        order->displayItems();
        cout << "1. Add an item" << endl;
        cout << "2. Remove an item" << endl;
        cout << "3. Finish modifying" << endl;
        cout << "Enter choice: ";
        int choice = getIntInput();

        if (choice == 1) {
            displayMenu();
            cout << "Enter item number to add (1-7): ";
            int itemChoice = getIntInput();
            string item;
            switch (itemChoice) {
            case 1: item = "Pizza"; break;
            case 2: item = "Burger"; break;
            case 3: item = "Pasta"; break;
            case 4: item = "Cola"; break;
            case 5: item = "Juice"; break;
            case 6: item = "Fries"; break;
            case 7: item = "Salad"; break;
            default: cout << "Invalid choice." << endl; continue;
            }
            order->addItem(item);
            cout << "Added " << item << "." << endl;

        }
        else if (choice == 2) {
            if (order->countItems <= 1) {
                cout << "Error: Cannot remove the last item from an order." << endl;
                continue;
            }
            cout << "Enter exact item name to remove: ";
            string itemToRemove = "";
            getline(cin, itemToRemove);
            if (order->removeItem(itemToRemove)) {
                cout << "Removed " << itemToRemove << "." << endl;
            }
            else {
                cout << "Error: Item '" << itemToRemove << "' not found in this order." << endl;
            }

        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    cout << "Finished modifying Order #" << orderNum << "." << endl;
    saveToFile();
}
void OrderList::reviewAllOrders() {

    cout << "\n--- All Registered Orders ---" << endl;
    if (head == nullptr) {
        cout << "[No orders in the system]" << endl;
        cout << "---------------------------" << endl;
        return;
    }

    OrderNode* temp = head;
    for (; temp != nullptr;) {
        cout << "===========================" << endl;
        cout << "Order Number: " << temp->orderData.orderNumber << endl;
        cout << "Status:       ";
        if (temp->orderData.orderStatus == "In Progress") {
            setConsoleColor(10); // 10 = Bright Green
        }
        else if (temp->orderData.orderStatus == "Canceled") {
            setConsoleColor(12); // 12 = Bright Red
        }
        else {
            setConsoleColor(15); // 15 = White
        }
        cout << temp->orderData.orderStatus << endl;
        setConsoleColor(15); // Reset to white

        cout << "Student Name: " << temp->orderData.studentFirstName << " " << temp->orderData.studentLastName << endl;
        cout << "Student ID:   " << temp->orderData.studentID << endl;
        temp->orderData.displayItems();
        temp = temp->next;
    }
    cout << "===========================" << endl;
}
void OrderList::saveToFile() {
    ofstream outFile(FILENAME);
    if (!outFile) {
        cout << "Error opening file for writing: " << FILENAME << endl;
        return;
    }
    OrderNode* temp = head;
    for (; temp != nullptr;) {
        outFile << temp->orderData.orderNumber << ","
            << temp->orderData.orderStatus << ","
            << temp->orderData.studentID << ","
            << temp->orderData.studentFirstName << ","
            << temp->orderData.studentLastName << endl;
        Food* itemTemp = temp->orderData.itemsHead;
        for (; itemTemp != nullptr;) {
            outFile << "ITEM:" << itemTemp->name << endl;
            itemTemp = itemTemp->next;
        }
        outFile << "END_ORDER" << endl;
        temp = temp->next;
    }
    outFile.close();
}
void OrderList::loadFromFile() {
    ifstream inFile(FILENAME);
    if (!inFile) {
        return;
    }
    OrderNode* temp = head;
    for (; temp != nullptr;) {
        OrderNode* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
    string line;
    OrderNode* currentOrderNode = nullptr;
    int maxOrderNum = 0;

    while (getline(inFile, line)) {
        if (line.rfind("ITEM:", 0) == 0) {
            if (currentOrderNode != nullptr) {
                string itemName = line.substr(5); // Get text after "ITEM:"
                currentOrderNode->orderData.addItem(itemName);
            }
        }
        else if (line == "END_ORDER") {
            if (currentOrderNode != nullptr) {
                currentOrderNode->next = head;
                head = currentOrderNode;
                currentOrderNode = nullptr;
            }
        }
        else {
            currentOrderNode = new OrderNode();
            stringstream ss(line);
            string segment;

            getline(ss, segment, ',');
            currentOrderNode->orderData.orderNumber = stoi(segment);

            getline(ss, segment, ',');
            currentOrderNode->orderData.orderStatus = segment;

            getline(ss, segment, ',');
            currentOrderNode->orderData.studentID = segment;

            getline(ss, segment, ',');
            currentOrderNode->orderData.studentFirstName = segment;

            getline(ss, segment, ',');
            currentOrderNode->orderData.studentLastName = segment;

            if (currentOrderNode->orderData.orderNumber > maxOrderNum) {
                maxOrderNum = currentOrderNode->orderData.orderNumber;
            }
        }
    }


    nextOrderNumber = maxOrderNum + 1;

    inFile.close();
}