📋 Project Overview

This project implements a complete restaurant management ecosystem using various data structures and algorithms:
Graphs & Dijkstra's Algorithm for delivery route optimization
Hash Tables for efficient employee and customer management
Binary Trees for menu organization and dish management
Heaps for review prioritization system
Stacks for promotion management
Linked Lists for restaurant and order management


🚀 Key Features
🧑‍💼 Multi-User System
Admin Panel: Full system control - manage restaurants, employees, promotions
Employee Portal: Order processing, menu management, review handling
Customer Interface: Order placement, review system, order tracking

📦 Order Management
Three order types: Premium (no delivery fee), Express (+10% surcharge), Normal (flat fee)
Real-time order processing and status tracking
Promotion and discount application system

🗺️ Advanced Delivery System
Dijkstra's algorithm for optimal route calculation between locations
Driver assignment and availability system
Real-time delivery cost calculation based on distance

⭐ Review System
Rating-based review prioritization using heaps
Restaurant and dish-specific reviews
Employee access control for review management

🛠️ Technical Implementation
Data Structures Demonstrated
Graphs: Delivery route mapping and shortest path calculation
Hash Tables: O(1) access for employee and customer data
Binary Search Trees: Efficient menu organization by price
Heaps: Priority-based review management
Stacks: LIFO promotion management
Linked Lists: Flexible restaurant and order management

Algorithms Implemented
Dijkstra's Algorithm: For optimal delivery route finding
Hash Functions: For efficient data retrieval
Tree Traversal: For menu organization and management
Heap Operations: For review prioritization
Sorting Algorithms: For order processing

📁 Project Structure
text
RestaurantManagementSystem/
├── main.cpp                 # Main application entry point
├── Graph.h                  # Graph implementation for delivery routes
├── Review.h                 # Review system management
├── Driver.h                 # Delivery driver management
├── DeliveryManager.h        # Delivery system coordination
├── Customer.h               # Customer management system
├── Admin.h                  # Administrative functions
├── Dish.h                   # Dish item management
├── Employee.h               # Employee management
├── EmployeeHashTable.h      # Hash table for employees
├── User.h                   # Base user system
├── UserManager.h           # User management
├── HashMap.h               # Hash map implementation
├── Menu.h                  # Menu management system
├── Order.h                 # Order processing system
├── Promotion.h             # Promotion management
├── PromotionStack.h        # Promotion stack implementation
├── ReviewHeap.h            # Review prioritization heap
├── Delivery.h              # Delivery management
├── Restaurant.h            # Restaurant management
├── RestaurantList.h        # Restaurant collection management
└── FunctionHandlers.h      # Main functionality handlers


🚦 How to Run
Compile the application:

bash
g++ -o restaurant_manager main.cpp
Execute the program:

bash
./restaurant_manager
Login with sample credentials:

Admin: username: Inam, password: Pass0123!

Sample employees and customers are auto-generated

🎯 Educational Value
This project serves as an excellent demonstration of:
Advanced Data Structures: Practical implementation of graphs, hash tables, trees, heaps, stacks, and linked lists
Algorithm Optimization: Dijkstra's algorithm for pathfinding and various sorting/searching techniques
Object-Oriented Design: Clean class architecture and inheritance patterns
Memory Management: Efficient resource handling and pointer management
Real-World System Design: Architecture that mimics actual restaurant management workflows

💡 Sample Usage
As a Customer: Browse restaurants, place orders, request delivery, leave reviews
As an Employee: Process orders, manage menus, handle restaurant operations
As an Admin: Manage the entire system, add restaurants, employees, and promotions
The system includes a pre-configured delivery network with multiple locations and routes to demonstrate the pathfinding algorithm.

👨‍💻 Development Notes
Built with pure C++ (no external dependencies)
Console-based interface with secure input handling
Comprehensive error handling and validation
Memory-safe resource management
Scalable architecture for future enhancements
Perfect for students learning data structures, algorithms, and object-oriented programming in C++!

⭐ Star this repo if you find it helpful!
