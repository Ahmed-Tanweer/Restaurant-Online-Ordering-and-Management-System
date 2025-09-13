#ifndef PROMOTION_H
#define PROMOTION_H

#include <iostream>
#include <string>
using namespace std;

class Promotion {
public:
    int id;
    string name;
    float discount;
    int limit;

    static int nextId;

    Promotion(string promotionName, float promotionDiscount, int promotionLimit)
        : name(promotionName), discount(promotionDiscount), limit(promotionLimit) {
        id = nextId++;
    }

    float applyPromotion(float orderTotal) {
        return orderTotal * (1 - discount);
    }
};

#endif