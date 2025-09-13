#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <string>
using namespace std;

class Driver {
public:
    int id;
    string name;
    string email;
    bool isAvailable;
    static int nextDriverId;

    Driver(string name, string email)
        : name(name), email(email), isAvailable(true) {
        id = nextDriverId++;
    }

    string getName() const {
        return name;
    }

    bool getAvailability() const {
        return isAvailable;
    }

    void setAvailability(bool availability) {
        isAvailable = availability;
    }
};

#endif