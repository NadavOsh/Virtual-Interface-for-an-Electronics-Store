
# Virtual Electronics Store

This program implements a **virtual interface for an electronic store** in C.  
It uses multiple libraries, custom data structures, algorithms, and file handling to simulate store operations.

## Features
- Employee authentication with 3 permission levels
- Add, remove, and search for items
- Manage customers and their purchases
- Persistent storage in text files (`employees.txt`, `items.txt`, etc.)
- Automatic logging of all actions

---

## Data Structures

### Employees
- `Employee` struct — username, first name, password, permission level (1 = Manager, 2 = Employee, 3 = Entry)
- `employeeNode` — doubly linked list node holding an `Employee*`, connection flag, and employee number
- `employeeList` — head, tail, and size of the employee linked list

**Employee levels:**
1. **Manager** — access to all functions, including adding employees
2. **Employee** — search items, add/remove items/customers, update lists
3. **Entry** — search items, add items/customers

Employees are stored in `employees.txt` and updated automatically.

---

### Items
- Item struct holding all product attributes (id, product's name, category, price, in stock, date, and inventory)
- Binary search tree (BST) for fast lookup by ID or other attributes (items can be searched by all attributes)
- Stored in `items.txt` sorted by ID

---

### Customers
- Customer struct for personal data
- Linked list for customer management
- Data structures for sold items per customer
- Rules:
  - Max 3 items per purchase
  - Returns allowed within 14 days

---

### Menu
- Single function displaying different menus based on user level
- Routes actions to the correct modules

---

## Files
- `employees.h` / `employees.c` — Employee management
- `items.h` / `items.c` — Item management
- `customers.h` / `customers.c` — Customer management
- `menu.c` — Menu handling
- `log.txt` — Log file of all actions
- `employees.txt` / `items.txt`/'customers.txt' — Persistent storage

