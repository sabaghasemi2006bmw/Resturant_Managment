#include <iostream>
#include "Order.h"
#include "OrderList.h"

using namespace std;
void showMainMenu() {
    cout << "\n===== University Restaurant Management System =====" << endl;
    cout << "1. Display Menu" << endl;
    cout << "2. Register New Order" << endl;
    cout << "3. Mark Order as 'Delivered'" << endl;
    cout << "4. Cancel Order" << endl;
    cout << "5. Change an 'In Progress' Order" << endl;
    cout << "6. Review All Orders" << endl;
    cout << "0. Exit" << endl;
    cout << "=================================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    OrderList restaurantSystem; // This one object runs everything
    int choice;

    do {
		restaurantSystem.loadFromFile();
        showMainMenu();
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls || clear");

        switch (choice) {
        case 1:
            restaurantSystem.displayMenu();
            cout << "Press Enter" << endl;
            cin.ignore();
            break;
        case 2:
            restaurantSystem.addNewOrder();
            cout << "Press Enter" << endl;
            cin.ignore();
            break;
        case 3:
            restaurantSystem.markOrderDelivered();
            cout << "Press Enter" << endl;
            cin.ignore();
            break;
        case 4:
            restaurantSystem.cancelOrder();
            cout << "Press Enter" << endl;
            cin.ignore();
            break;
        case 5:
            restaurantSystem.changeOrder();
            cout << "Press Enter" << endl;
            cin.ignore();
            break;
        case 6:
            restaurantSystem.reviewAllOrders();
            cout << "Press Enter" << endl;
            cin.ignore();
            break;
        case 0:
            cout << "Saving and exiting. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        system("cls || clear");
    } while (choice != 0);
	restaurantSystem.saveToFile();
    return 0;
}