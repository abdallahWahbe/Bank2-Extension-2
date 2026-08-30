# 🏦 Bank Management System

A **Console-Based Bank Management System** developed using **C++**.
The project provides a simple banking environment for managing clients, performing financial transactions, managing system users, and controlling access through permissions.

---

## ✨ Features

### 👤 Client Management

* 📋 Display all clients
* ➕ Add new clients
* 🗑️ Delete clients
* ✏️ Update client information
* 🔎 Find clients by account number
* 💰 View account balances

### 💳 Banking Transactions

* 💵 Deposit money
* 💸 Withdraw money
* 📊 View total balances
* ✅ Confirmation before performing transactions
* 🚫 Prevent withdrawals that exceed the available balance

### 👥 User Management

* 📋 List all users
* ➕ Add new users
* 🗑️ Delete users
* ✏️ Update users
* 🔎 Find users by username

### 🔐 Authentication & Permissions

* 🔑 Username and password login
* 🛡️ Permission-based access control
* 👑 Full-access administrator permission
* ⚙️ Individual permissions for different system operations
* 🔢 Bitwise operators used to manage permissions

The system defines separate permissions for:

* 📋 Listing clients
* ➕ Adding clients
* 🗑️ Deleting clients
* ✏️ Updating clients
* 🔎 Finding clients
* 💳 Performing transactions
* 👥 Managing users

---

## 💾 Data Storage

The system uses **text files** to store data persistently.

### 📁 Files

```text
Clients.txt
Users.txt
```

Client and user records are converted between structures and text lines using a custom delimiter:

```text
#//#
```

This allows the application to save and load data between program executions.

---

## 🛠️ Technologies Used

* 💻 **C++**
* 📦 **STL**

  * `vector`
  * `string`
* 📂 **File Handling**

  * `fstream`
* 🧱 **Structs**
* 🔢 **Enums**
* ⚡ **Bitwise Operators**
* 🔐 **Permission Management**
* 🖥️ **Console Interface**

---

## 🧠 Concepts Practiced

This project was built to practice several important C++ programming concepts:

* Functions
* Structures (`struct`)
* Enumerations (`enum`)
* Vectors
* Strings
* File input/output
* Passing by reference
* Loops and conditions
* Switch statements
* CRUD operations
* Data conversion
* Authentication
* Access control
* Bitwise operations

---

## 🏗️ Main Menu

```text
===========================================================

                     Main Menu

===========================================================

        [1] Show Client List
        [2] Add New Client
        [3] Delete Client
        [4] Update Client Info
        [5] Find Client
        [6] Transaction
        [7] Manage Users
        [8] Exit

===========================================================
```

---

## 💳 Transactions Menu

```text
===========================================

        Transactions Menu Screen

===========================================

        [1] Deposit
        [2] Withdraw
        [3] Total Balances
        [4] Main Menu

===========================================
```

---

## 👥 Manage Users Menu

```text
===========================================

        Manage Users Menu Screen

===========================================

        [1] List Users
        [2] Add New User
        [3] Delete User
        [4] Update User
        [5] Find User
        [6] Main Menu

===========================================
```

---

## 🔐 Permission System

The project uses different permission values:

```text
List Clients      = 1
Add New Client    = 2
Delete Client     = 4
Update Clients    = 8
Find Client       = 16
Transactions      = 32
Manage Users      = 64
Full Access       = -1
```

Multiple permissions can be combined using bitwise operations.

For example:

```cpp
Permissions = pListClients + pAddNewClient + pFindClient;
```

And access is checked using:

```cpp
(Permissions & currentUser.Permissions) == Permissions
```

This allows each user to have specific access rights instead of giving every user full access.

---

## 📂 Project Structure

```text
Bank-Management-System/
│
├── BankExtension2.cpp
├── Clients.txt
├── Users.txt
└── README.md
```

---

## 🚀 How to Run

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/abdallahWahbe/Bank-Management-System2.git
```

### 2️⃣ Open the Project

Open the project using a C++ IDE such as:

* Visual Studio
* Code::Blocks
* Dev-C++
* Any C++ compiler/IDE

### 3️⃣ Build & Run

Compile the project and run the executable.

### 4️⃣ Login

Enter a valid username and password from `Users.txt`.

---

## 📌 Notes

⚠️ This project is a **learning project** and is designed for practicing C++ programming concepts.

🔒 Passwords are currently stored as plain text in `Users.txt`. This is **not suitable for a real banking application**.

💾 The application uses local text files instead of a database.

---

## 🎯 Project Goal

The main goal of this project is to apply C++ programming concepts in a practical project and build a complete console-based system with:

**Authentication → Authorization → Client Management → Transactions → User Management → File Storage**

---

## 👨‍💻 Author

**Abd Allah Wahbe**

📚 C++ Programming Project

⭐ If you find this project useful, feel free to give it a star!
