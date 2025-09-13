#ifndef FUNCTIONHANDLERS_H
#define FUNCTIONHANDLERS_H

#include "UserManager.h"
#include "RestaurantList.h"
#include "Admin.h"
#include "EmployeeHashTable.h"
#include "DeliveryManager.h"
#include "Employee.h"
#include "Customer.h"
#include "Restaurant.h"
#include "Menu.h"
#include "Dish.h"
#include "Order.h"
#include "PromotionStack.h"

void initializeSampleData(UserManager& userManager, RestaurantList& restaurantList, Admin*& admin,
    EmployeeHashTable& empTable, DeliveryManager* deliveryManager) {
    Admin::initializeDefaultAdmin();
    admin = Admin::defaultAdmin;

    Restaurant* r1 = new Restaurant("Pizza Palace", "Italian", nullptr, "Downtown");
    Restaurant* r2 = new Restaurant("Sushi World", "Japanese", nullptr, "City Center");

    Employee* manager1 = new Employee("Rizwan", "i233009@isb.nu.edu.pk", "Pass0123!", r1->id);
    Employee* manager2 = new Employee("Abdul Basit", "i233018@isb.nu.edu.pk", "Pass0123!", r2->id);
    r1->manager = manager1;
    r2->manager = manager2;

    restaurantList.addRestaurant(r1);
    restaurantList.addRestaurant(r2);

    empTable.addEmployee(manager1);
    empTable.addEmployee(manager2);

    Menu* menu1 = new Menu("Pizza Palace");
    menu1->addDish(new Dish("Pizza Margherita", "Main Course", 8.99), *manager1);
    menu1->addDish(new Dish("Spaghetti Carbonara", "Main Course", 12.49), *manager1);
    r1->setMenu(menu1, admin);

    Menu* menu2 = new Menu("Sushi World");
    menu2->addDish(new Dish("Sushi Rolls", "Appetizer", 15.99), *manager2);
    menu2->addDish(new Dish("Tempura", "Appetizer", 10.99), *manager2);
    r2->setMenu(menu2, admin);

    Customer* cust1 = new Customer("Abdullah Tariq", "abdtariq3274", "Pass0123!");
    Customer* cust2 = new Customer("Malik Usman", "i233020@isb.nu.edu.pk", "Pass0123!");
    userManager.addUser(new User("john", "password123", false));
    userManager.addUser(new User("jane", "password123", false));

    Driver* driver1 = new Driver("Ali Raza", "driver1@delivery.com");
    Driver* driver2 = new Driver("Sara Khan", "driver2@delivery.com");
    Driver* driver3 = new Driver("Ahmed Malik", "driver3@delivery.com");

    deliveryManager->addDriver(driver1);
    deliveryManager->addDriver(driver2);
    deliveryManager->addDriver(driver3);

    cout << "Sample data initialized successfully with drivers:\n";
    cout << "Driver 1: " << driver1->getName() << "\n";
    cout << "Driver 2: " << driver2->getName() << "\n";
    cout << "Driver 3: " << driver3->getName() << "\n";
}

void handleAdminTasks(Admin* admin, RestaurantList& restaurantList, EmployeeHashTable& empTable, PromotionStack& promoStack) {
    int choice;
    while (true) {
        cout << "\nAdmin Menu:\n"
            << "1. Add Restaurant\n"
            << "2. Delete Restaurant\n"
            << "3. View Restaurants\n"
            << "4. Add Employee\n"
            << "5. Remove Employee\n"
            << "6. Manage Promotions\n"
            << "7. View Admins\n"
            << "8. View Customers\n"
            << "9. Logout\n"
            << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, type, location;
            cout << "Enter restaurant name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter restaurant type: ";
            getline(cin, type);
            cout << "Enter restaurant location: ";
            getline(cin, location);

            Restaurant* newRestaurant = new Restaurant(name, type, nullptr, location);
            restaurantList.addRestaurant(newRestaurant);
            cout << "Restaurant added successfully.\n";
            break;
        }
        case 2: {
            int restaurantId;
            cout << "Enter restaurant ID to delete: ";
            cin >> restaurantId;
            restaurantList.deleteRestaurant(restaurantId);
            break;
        }
        case 3:
            restaurantList.displayAllRestaurants();
            break;
        case 4: {
            string name, email, password;
            int restaurantId;
            cout << "Enter employee name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter employee email: ";
            getline(cin, email);
            cout << "Enter employee password: ";
            cin >> password;
            cout << "Enter restaurant ID: ";
            cin >> restaurantId;

            try {
                Employee* emp = new Employee(name, email, password, restaurantId);
                empTable.addEmployee(emp);
                cout << "Employee added successfully.\n";
                cout << "Employee Id: " << emp->getId() << endl;
                restaurantList.getRestaurantById(restaurantId)->addEmployee(emp, admin);
            }
            catch (const char* msg) {
                cout << "Error: " << msg << endl;
            }
            break;
        }
        case 5: {
            int id;
            cout << "Enter employee ID to remove: ";
            cin >> id;
            empTable.deleteEmployee(id);
            for (int i = 0; i < restaurantList.getSize(); ++i) {
                Restaurant* restaurant = restaurantList.getRestaurant(i);
                restaurant->removeEmployee(id, admin);
            }
            cout << "Employee removed successfully.\n";
            break;
        }
        case 6: {
            int promoChoice;
            cout << "1. Add Promotion\n"
                << "2. View Promotions\n"
                << "Enter choice: ";
            cin >> promoChoice;
            if (promoChoice == 1) {
                string name;
                float discount;
                int limit;
                cout << "Enter promotion name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter discount percentage (e.g., 0.1 for 10%): ";
                cin >> discount;
                cout << "Enter usage limit: ";
                cin >> limit;
                Promotion* promo = new Promotion(name, discount, limit);
                promoStack.push(promo);
                cout << "Promotion added successfully.\n";
            }
            else if (promoChoice == 2) {
                cout << "Current Promotions:\n";
                Promotion* promo = promoStack.peek();
                if (promo) {
                    cout << "Promotion Name: " << promo->name << ", Discount: " << promo->discount * 100 << "%\n";
                }
                else {
                    cout << "No promotions available.\n";
                }
            }
            break;
        }
        case 7: {
            Admin::viewAllAdmins();
            break;
        }
        case 8: {
            Admin::viewAllCustomers();
            break;
        }
        case 9:
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

void handleEmployeeTasks(Employee* employee, RestaurantList& restaurantList) {
    int choice;
    while (true) {
        cout << "\nEmployee Menu:\n"
            << "1. View Pending Orders\n"
            << "2. Process Next Order\n"
            << "3. View Reviews\n"
            << "4. View Processed Orders\n"
            << "5. Reset Password\n"
            << "6. Edit Profile (Name)\n"
            << "7. View Your Details\n"
            << "8. Add Dish\n"
            << "9. Remove Dish\n"
            << "10. View All Dishes\n"
            << "11. Logout\n"
            << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int restaurantId;
            cout << "Enter your restaurant ID to view pending orders: ";
            cin >> restaurantId;

            if (restaurantId != employee->getRestaurantId()) {
                cout << "You are not authorized to view orders for this restaurant.\n";
                break;
            }

            Restaurant* rest = restaurantList.getRestaurantById(restaurantId);
            if (rest) {
                rest->displayPendingOrders();
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }
        case 2: {
            int restaurantId;
            cout << "Enter your restaurant ID to process an order: ";
            cin >> restaurantId;

            if (restaurantId != employee->getRestaurantId()) {
                cout << "You are not authorized to manage orders for this restaurant.\n";
                break;
            }

            Restaurant* rest = restaurantList.getRestaurantById(restaurantId);
            if (rest) {
                if (rest->orderCount > 0) {
                    rest->processNextOrder(employee);
                    employee->addProcessedOrder(rest->orderQueue[0]->id);
                }
                else {
                    cout << "No pending orders at this restaurant.\n";
                }
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }
        case 3: {
            int restaurantId;
            cout << "Enter your restaurant ID to view reviews: ";
            cin >> restaurantId;

            if (restaurantId != employee->getRestaurantId()) {
                cout << "You are not authorized to view reviews for this restaurant.\n";
                break;
            }

            Restaurant* rest = restaurantList.getRestaurantById(restaurantId);
            if (rest) {
                cout << "Reviews for Restaurant: " << rest->getName() << endl;
                rest->printReviews();
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }
        case 4: {
            employee->viewProcessedOrders();
            break;
        }
        case 5: {
            employee->resetPassword();
            break;
        }
        case 6: {
            string newName;
            cout << "Enter your new name: ";
            cin.ignore();
            getline(cin, newName);
            employee->editName(newName);
            cout << "Name updated successfully.\n";
            break;
        }
        case 7: {
            cout << "Your Details:\n";
            employee->printDetails();
            break;
        }
        case 8: {
            int restaurantId;
            cout << "Enter your restaurant ID to add a dish: ";
            cin >> restaurantId;

            if (restaurantId != employee->getRestaurantId()) {
                cout << "You are not authorized to manage dishes for this restaurant.\n";
                break;
            }

            Restaurant* rest = restaurantList.getRestaurantById(restaurantId);
            if (rest) {
                string dishName, dishType;
                double price;
                cout << "Enter dish name: ";
                cin.ignore();
                getline(cin, dishName);
                cout << "Enter dish type: ";
                getline(cin, dishType);
                cout << "Enter dish price: ";
                cin >> price;
                rest->addDishToMenu(dishName, dishType, price, employee);
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }
        case 9: {
            int restaurantId;
            cout << "Enter your restaurant ID to remove a dish: ";
            cin >> restaurantId;

            if (restaurantId != employee->getRestaurantId()) {
                cout << "You are not authorized to manage dishes for this restaurant.\n";
                break;
            }

            Restaurant* rest = restaurantList.getRestaurantById(restaurantId);
            if (rest) {
                int dishId;
                cout << "Enter the dish ID to remove: ";
                cin >> dishId;
                rest->removeDishFromMenu(dishId, employee);
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }
        case 10: {
            int restaurantId;
            cout << "Enter your restaurant ID to view all dishes: ";
            cin >> restaurantId;

            if (restaurantId != employee->getRestaurantId()) {
                cout << "You are not authorized to view dishes for this restaurant.\n";
                break;
            }

            Restaurant* rest = restaurantList.getRestaurantById(restaurantId);
            if (rest) {
                rest->getMenu()->displayAllDishes();
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }
        case 11: {
            return;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void handleCustomerTasks(RestaurantList& restaurantList, Customer* currentCustomer, DeliveryManager* deliveryManager) {
    int choice;
    while (true) {
        cout << "\nCustomer Menu:\n"
            << "1. View Restaurants\n"
            << "2. Place an Order\n"
            << "3. Update Order\n"
            << "4. Leave a Review\n"
            << "5. View Order History\n"
            << "6. View Current Orders\n"
            << "7. Edit Profile\n"
            << "8. View My Reviews\n"
            << "9. View My Bill\n"
            << "10. Logout\n"
            << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            restaurantList.displayAllRestaurants();
            break;
        }
        case 2: {
            int restaurantId, orderType;
            cout << "Enter Restaurant ID to order from: ";
            cin >> restaurantId;
            Restaurant* restaurant = restaurantList.getRestaurantById(restaurantId);
            if (!restaurant) {
                cout << "Invalid Restaurant ID.\n";
                break;
            }
            cout << "Select Order Type (1 = Premium, 2 = Express, 3 = Normal): ";
            cin >> orderType;

            Order* newOrder = new Order(currentCustomer, orderType);

            restaurant->menu->displayMenu();
            cout << "Enter Dish IDs to add to the order (-1 to stop): ";
            int dishId;
            while (cin >> dishId && dishId != -1) {
                Dish* selectedDish = restaurant->menu->getDishById(dishId);
                if (selectedDish) {
                    newOrder->addDish(selectedDish);
                    cout << "Added " << selectedDish->getName() << " to the order.\n";
                }
                else {
                    cout << "Invalid Dish ID.\n";
                }
            }

            cout << "Would you like to request delivery for your order? (1 for Yes, 0 for No): ";
            int requestDelivery;
            cin >> requestDelivery;

            if (requestDelivery == 1) {
                cout << "Available Delivery Locations:\n";
                for (int i = 0; i < DeliveryManager::MAX_LOCATIONS; i++) {
                    if (!deliveryManager->locations[i].empty()) {
                        cout << i << ": " << deliveryManager->locations[i] << endl;
                    }
                }

                cout << "\nGive your location index (0 to " << DeliveryManager::MAX_LOCATIONS - 1 << "): " << endl;
                cin >> requestDelivery;
                currentCustomer->placeOrder(newOrder->id, restaurantId, deliveryManager->locations[requestDelivery]);
                string source = deliveryManager->locations[requestDelivery];
                cout << "Customer Location: " << source << endl;
                
                int locationIndex;
                cout << "Select location index from where you want delivery (0 to " << DeliveryManager::MAX_LOCATIONS - 1 << "): ";
                cin >> locationIndex;

                if (locationIndex < 0 || locationIndex >= DeliveryManager::MAX_LOCATIONS || deliveryManager->locations[locationIndex].empty()) {
                    cout << "Invalid destination.\n";
                    break;
                }

                string destination = deliveryManager->locations[locationIndex];
                newOrder->setDeliveryLocation(destination);
                cout << destination << endl;

                float deliveryCost = deliveryManager->calculateShortestPath(source, destination);

                if (deliveryCost >= 0) {
                    cout << "Delivery to " << destination << " will cost Rs. " << deliveryCost << ".\n";

                    Driver* assignedDriver = deliveryManager->assignDriver();
                    if (assignedDriver) {
                        newOrder->assignDeliveryDriver(assignedDriver);
                        cout << "Driver " << assignedDriver->getName() << " assigned to deliver your order.\n";

                        cout << "Confirm delivery? (1 for Yes, 0 for No): ";
                        int confirm;
                        cin >> confirm;

                        if (confirm == 1) {
                            currentCustomer->assignDelivery(newOrder->id, deliveryCost);
                            cout << "Delivery scheduled successfully.\n";
                        }
                        else {
                            cout << "Delivery canceled.\n";
                            deliveryManager->releaseDriver(assignedDriver);
                        }
                    }
                    else {
                        cout << "No drivers are available at the moment. Delivery cannot be scheduled.\n";
                    }
                }
                else {
                    cout << "Unable to calculate delivery cost. Check locations and try again.\n";
                }
            }

            PromotionStack* pro = new PromotionStack();
            pro->applyPromotions(newOrder);
            newOrder->calculateTotal();
            newOrder->printOrderDetails();

            restaurant->addOrder(newOrder, nullptr);
            break;
        }
        case 3: {
            int orderId;
            cout << "Enter Order ID to update: ";
            cin >> orderId;

            int restaurantId = currentCustomer->getRestaurantForOrder(orderId);
            if (restaurantId == -1) {
                cout << "Order ID not found.\n";
                break;
            }

            Restaurant* restaurant = restaurantList.getRestaurantById(restaurantId);
            if (restaurant) {
                restaurant->updateOrder(orderId);
            }
            else {
                cout << "Restaurant for the given order not found.\n";
            }
            break;
        }
        case 4: {
            int restaurantId, dishId = -1, rating;
            string description;
            cout << "Enter Restaurant ID to review: ";
            cin >> restaurantId;
            Restaurant* restaurant = restaurantList.getRestaurantById(restaurantId);
            if (!restaurant) {
                cout << "Invalid Restaurant ID.\n";
                break;
            }

            cout << "Do you want to review a specific dish? (1 for Yes, 0 for No): ";
            int reviewDish;
            cin >> reviewDish;

            if (reviewDish) {
                restaurant->menu->displayMenu();
                cout << "Enter Dish ID to review: ";
                cin >> dishId;
                if (!restaurant->menu->getDishById(dishId)) {
                    cout << "Invalid Dish ID.\n";
                    break;
                }
            }

            cout << "Enter your rating (1-5): ";
            cin >> rating;
            if (rating < 1 || rating > 5) {
                cout << "Invalid rating. Must be between 1 and 5.\n";
                break;
            }

            cout << "Enter your review description: ";
            cin.ignore();
            getline(cin, description);

            Review* newReview = new Review(rating, description, currentCustomer->id, restaurantId, dishId);
            currentCustomer->leaveReview(newReview->id);
            restaurant->addReview(newReview);
            cout << "Review submitted successfully!\n";
            break;
        }
        case 5: {
            cout << "Enter Restaurant ID to view order history: ";
            int restaurantId;
            cin >> restaurantId;
            Restaurant* restaurant = restaurantList.getRestaurantById(restaurantId);
            if (restaurant) {
                restaurant->viewOrderHistory();
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }
        case 6: {
            currentCustomer->viewCurrentOrders();
            break;
        }
        case 7: {
            string newName, newPassword;
            cout << "Enter new name (leave blank to skip): ";
            cin.ignore();
            getline(cin, newName);
            cout << "Enter new password (leave blank to skip): ";
            newPassword = Customer::getMaskedInput();

            currentCustomer->editProfile(newName, newPassword);
            break;
        }
        case 8: {
            currentCustomer->viewReviews();
            break;
        }
        case 9: {
            int orderId;
            cout << "Enter your Order ID to view the bill: ";
            cin >> orderId;

            int restaurantId = currentCustomer->getRestaurantForOrder(orderId);
            if (restaurantId == -1) {
                cout << "Order ID not found.\n";
                break;
            }

            Restaurant* restaurant = restaurantList.getRestaurantById(restaurantId);
            if (restaurant) {
                restaurant->viewCustomerBill(currentCustomer->id);
            }
            else {
                cout << "Restaurant for the given order not found.\n";
            }
            break;
        }
        case 10: {
            return;
        }
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

void handleEmployeeLogin(EmployeeHashTable& empTable, RestaurantList& restaurantList) {
    Employee* currentEmployee = nullptr;
    while (!currentEmployee) {
        cout << "\nEmployee Menu:\n"
            << "1. Login\n"
            << "2. Register\n"
            << "3. Back to Main Menu\n"
            << "Enter choice: ";
        int subChoice;
        cin >> subChoice;

        if (subChoice == 1) {
            int empId;
            string password;
            cout << "Enter your Employee ID: ";
            cin >> empId;
            Employee* employee = empTable.getEmployee(empId);

            if (employee) {
                if (employee->login()) {
                    currentEmployee = employee;
                    cout << "Login successful! Welcome, " << employee->getName() << ".\n";
                }
                else {
                    cout << "Invalid password. Try again.\n";
                }
            }
            else {
                cout << "Employee ID not found. Try again.\n";
            }
        }
        else if (subChoice == 2) {
            string name, email, password;
            int restaurantId;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter a password: ";
            cin >> password;
            cout << "Enter your restaurant ID: ";
            cin >> restaurantId;

            try {
                Employee* newEmployee = new Employee(name, email, password, restaurantId);
                empTable.addEmployee(newEmployee);
                cout << "Registration successful! Your Employee ID is: " << newEmployee->getId() << endl;
            }
            catch (const char* error) {
                cout << "Registration failed: " << error << endl;
            }
        }
        else if (subChoice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    if (currentEmployee) {
        handleEmployeeTasks(currentEmployee, restaurantList);
    }
}

void handleCustomerLogin(RestaurantList& restaurantList, DeliveryManager* deliveryManager) {
    Customer* currentCustomer = nullptr;
    while (!currentCustomer) {
        cout << "\nCustomer Menu:\n"
            << "1. Login\n"
            << "2. Register\n"
            << "3. Back to Main Menu\n"
            << "Enter choice: ";
        int subChoice;
        cin >> subChoice;

        if (subChoice == 1) {
            string email, password;
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your password: ";
            string enteredPassword = Customer::getMaskedInput();
            currentCustomer = Customer::logIn(email, enteredPassword);

            if (!currentCustomer) {
                cout << "Login failed. Try again.\n";
            }
            else {
                cout << "Login successful! Welcome, " << currentCustomer->name << endl;
            }
        }
        else if (subChoice == 2) {
            string name, email, password, confirmPassword;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter a password: ";
            cin >> password;
            cout << "Confirm your password: ";
            cin >> confirmPassword;

            if (Customer::signUp(name, email, password, confirmPassword)) {
                currentCustomer = new Customer(name, email, password);
                int hashIndex = Customer::hashEmail(email);
                Customer::customerList[hashIndex] = currentCustomer;
                cout << "Registration successful. You can now log in.\n";
            }
            else {
                cout << "Registration failed. Try again.\n";
            }
        }
        else if (subChoice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    if (currentCustomer) {
        handleCustomerTasks(restaurantList, currentCustomer, deliveryManager);
    }
}

#endif