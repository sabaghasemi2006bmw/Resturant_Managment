#include "Order.h"

Order::Order() {
	itemsHead = nullptr;
	orderNumber = 0;
	orderStatus = "In Progress";
	countItems = 0;
};

Order::~Order() {
	Food* temp = itemsHead;
	while (temp != nullptr) {
		Food* next = temp->next;
		delete temp;
		temp = next;
	}
}

void Order::addItem(string name) {
	Food* newItem = new Food(name);
	newItem->next = itemsHead;
	itemsHead = newItem;
	countItems++;
}

bool Order::removeItem(string name) {
	Food* temp = itemsHead;
	Food* prev = nullptr;
	for (; temp != nullptr && temp->name != name;) {
		prev = temp;
		temp = temp->next;
	}
	if (temp == nullptr) {
		return false; // Item not found
	}
	if (prev == nullptr) {
		itemsHead = temp->next;
	}
	else {
		prev->next = temp->next;
	}
	delete temp;
	countItems--;
	return true;
}

void Order::displayItems() {
	if (itemsHead == nullptr) {
		cout << "  [No items in this order]" << endl;
		return;
	}
	Food* temp = itemsHead;
	cout << "  Items:" << endl;
	for (; temp != nullptr;) {
		cout << "  - " << temp->name << endl;
		temp = temp->next;
	}
}