#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
public:
    int id;
    string name;
    string password;
    bool isAdmin;
    User* next;

    User(string userName, string userPassword, bool isAdminFlag) {
        static int idCounter = 0;
        id = idCounter++;
        name = userName;
        password = userPassword;
        isAdmin = isAdminFlag;
        next = nullptr;
    }
};

#endif