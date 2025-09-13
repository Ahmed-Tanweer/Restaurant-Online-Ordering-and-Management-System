#ifndef DELIVERY_H
#define DELIVERY_H

#include "Order.h"

class Delivery {
private:
    struct DeliveryNode {
        Order* order;
        float distance;
        DeliveryNode* next;

        DeliveryNode(Order* order, float distance) : order(order), distance(distance), next(nullptr) {}
    };

    DeliveryNode* orders;
    int orderCount;

public:
    Delivery() : orders(nullptr), orderCount(0) {}

    void addOrder(Order* order) {
        DeliveryNode* newNode = new DeliveryNode(order, order->total);
        if (!orders) {
            orders = newNode;
        }
        else {
            DeliveryNode* temp = orders;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        orderCount++;
    }

    void deliverOrders() {
        if (!orders) return;

        for (DeliveryNode* i = orders; i != nullptr; i = i->next) {
            for (DeliveryNode* j = i->next; j != nullptr; j = j->next) {
                if (i->order->total > j->order->total) {
                    Order* tempOrder = i->order;
                    i->order = j->order;
                    j->order = tempOrder;
                }
            }
        }

        DeliveryNode* temp = orders;
        while (temp) {
            cout << "Delivering Order ID " << temp->order->id << " to Customer: " << temp->order->customer->name << endl;
            temp->order->setStatus("Delivered");
            cout << "Order delivered successfully!" << endl;
            temp = temp->next;
        }
    }

    void displayDeliveryPath() {
        cout << "All orders have been delivered." << endl;
    }
};

#endif