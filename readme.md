# Lebanese Chart of Accounts Project

This project implements a Lebanese Chart of Accounts using a custom ForestTree data structure. The goal is to manage accounts and transactions effectively, enabling functionalities such as adding, removing, and searching for accounts, managing transactions, and generating detailed reports.

## Features

- ForestTree implementation for managing hierarchical accounts.
- Account and transaction management.
- File-based persistence for accounts and transaction logs.
- Reporting functionalities.

## Project Structure

The project consists of several classes, each responsible for a specific part of the functionality. Below is a brief overview of each class:

### 1. `System`

The main class that acts as an interface for managing the chart of accounts and interacting with the user.

**Key Responsibilities:**

- Adding, removing, and searching accounts.
- Managing transactions (credit and debit).
- Generating reports.
- Saving and loading data to/from files.

**Important Methods:**

- `addTransaction`: Adds a transaction to a specified account and updates the balance.
- `removeAccount`: Removes an account from memory and file storage.
- `printAccountReport`: Displays a detailed transaction history for a specific account.
- `saveTransactionLog`: Logs a transaction to a file.

### 2. `Account`

Represents an individual account in the chart of accounts.

**Key Attributes:**

- `accountNumber`: Unique identifier for the account.
- `description`: A textual description of the account.
- `balance`: The current balance of the account.
- `transactions`: A vector of transactions associated with the account.

**Key Methods:**

- `addTransaction`: Adds a transaction to the account and updates the balance.
- `printTransactions`: Displays all transactions for the account.

### 3. `Transaction`

Encapsulates the details of a single financial transaction.

**Key Attributes:**

- `amount`: The transaction amount.
- `type`: The type of transaction ('C' for Credit, 'D' for Debit).

### 4. `ForestTree`

A template-based hierarchical data structure used to organize accounts.

**Key Responsibilities:**

- Managing a collection of `Account` objects in a tree-like structure.
- Providing functionality to add, remove, and find accounts.

**Key Methods:**

- `addAccount`: Adds an account to the tree.
- `removeAccount`: Removes an account from the tree.
- `findAccount`: Finds and returns a pointer to an account.
- `printTree`: Prints a hierarchical view of the tree.

## Usage

1. Login using hardcoded credentials username(admin), password(admin123).
2. Initialize the system and load existing account data from their corresponding location.
3. Use the `System` interface to manage accounts and transactions.
4. Generate reports and print the account tree as needed.
5. Check transaction log in its corresponding location.

## Technologies Used

- C++ for core implementation.
- File I/O for data persistence.
- Hierarchical data structures for efficient organization.

## GitHub Repository

You can find the source code and detailed instructions for this project on GitHub:

[GitHub Repository Link](https://github.com/Mike846/AccountChart)
