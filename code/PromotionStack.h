#ifndef PROMOTIONSTACK_H
#define PROMOTIONSTACK_H

#include "Promotion.h"
#include "Order.h"

class PromotionStack {
private:
    Promotion* promotions[50];
    int top;

public:
    PromotionStack() : top(-1) {}

    void push(Promotion* promotion) {
        if (top < 49) {
            promotions[++top] = promotion;
        }
        else {
            cout << "Promotion stack is full." << endl;
        }
    }

    Promotion* pop() {
        if (top >= 0) {
            return promotions[top--];
        }
        else {
            cout << "No promotions available in the stack." << endl;
            return nullptr;
        }
    }

    Promotion* peek() {
        return (top >= 0) ? promotions[top] : nullptr;
    }

    bool isEmpty() {
        return top == -1;
    }

    void applyPromotions(Order* order) {
        while (!isEmpty() && order->promotionCount < order->totalOrders) {
            Promotion* currentPromotion = peek();
            if (currentPromotion->limit > 0) {
                order->total = currentPromotion->applyPromotion(order->total);
                currentPromotion->limit--;
                order->promotionCount++;
                if (currentPromotion->limit == 0) {
                    pop();
                }
            }
            else {
                pop();
            }
        }
    }
};

#endif