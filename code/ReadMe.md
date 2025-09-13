# Restaurant Management System

## Description
The **Restaurant Management System** is a comprehensive application designed to streamline and manage various aspects of restaurant operations. It incorporates functionalities for customers, employees, and administrators, making it a multi-faceted solution for restaurant management. Key features include order handling, employee and menu management, review collection, and promotion application, among others.

## Features
- **Customer Management**
  - Sign-up and login functionality with secure password criteria.
  - Order placement, history viewing, and restaurant-specific reviews.
  - Notifications for order updates.

- **Admin Functionality**
  - Add, update, and delete restaurants.
  - Manage employees and their association with restaurants.
  - View customer and admin details.
  - Manage promotional codes for discounts.

- **Employee Management**
  - View and process pending orders.
  - Add or remove dishes from restaurant menus.
  - Handle reviews and order updates.

- **Menu and Dish Management**
  - Add and organize dishes in a restaurant-specific menu.
  - Binary tree-based structure for efficient menu handling.

- **Order Management**
  - Create and manage orders with options for different types (Premium, Express, Normal).
  - Apply promotional discounts and calculate final totals.

- **Review System**
  - Gather customer reviews for dishes and restaurants.
  - Heap-based system to manage and display top good and bad reviews.

## Steps to Run the Application
1. **Install Required Compiler**:
   - Ensure a C++ compiler like GCC or MSVC is installed.
   - On Windows, install [MinGW](https://www.mingw.org/) or use Visual Studio.
   - On Linux/macOS, GCC is typically pre-installed.

2. **Set Up Environment**:
   - Clone or download the project files.
   - Open the project in a C++ IDE such as Visual Studio, Code::Blocks, or CLion.

3. **Compile the Code**:
   - Navigate to the project directory.
   - Compile the source file using the command:
     ```bash
     g++ -o RestaurantManagementSystem Check.cpp
     ```

4. **Run the Application**:
   - Execute the compiled program:
     ```bash
     ./RestaurantManagementSystem
     ```

5. **Follow On-Screen Prompts**:
   - Log in as an admin, employee, or customer.
   - Explore features based on the user role.

## Functionalities
### Admin
- Add new restaurants, employees, and promotions.
- Manage and update restaurant details.
- View customer and employee records.

### Employee
- Process orders and manage reviews.
- Add or remove menu items.
- View and edit personal profile details.

### Customer
- Register and log in securely.
- Place orders and leave reviews.
- View order history and track current orders.

## Notes
- The program includes error handling to prevent invalid operations, such as adding a dish to an unassociated restaurant or attempting to process orders without authorization.
- The password system ensures high security with a validation mechanism.
- Object-oriented principles and data structures such as heaps, stacks, and hash tables are utilized for efficient operations.

---

## New Features
Graph-Based Delivery Management

Delivery paths are optimized using graph data structures.
Calculate shortest paths using Dijkstra's algorithm for efficient deliveries.
Delivery System

Enhanced DeliveryManager handles location mapping and driver assignments.
Calculate delivery costs based on shortest paths between locations.
Driver Management

Assign and release drivers dynamically.
Track driver availability and performance.