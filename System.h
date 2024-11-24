#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include "ForestTree.h"
#include "Account.h"
#include "Transaction.h"

/**
 * @class System
 * @brief Manages the overall functionality of the accounting system, including authentication,
 *        account management, transaction handling, and tree visualization.
 */
class System {
public:
    /**
     * @brief Constructs a System object with default file paths for accounts and transactions.
     */
    System() : isAuthenticated(false),
               accounts_path("accountswithspace.txt"),
               transaction_path("transaction_log.txt") {}

    /**
     * @brief Handles user authentication.
     */
    void authenticate();

    /**
     * @brief Displays the main menu for user interaction.
     */
    void mainMenu();

    /**
     * @brief Prompts the user to create a new account and adds it to the system.
     */
    void createAccount();

    /**
     * @brief Allows the user to add a transaction to an existing account.
     */
    void addTransaction();

    /**
     * @brief Generates and prints a detailed report for a specific account.
     */
    void printAccountReport();

    /**
     * @brief Searches for an account by its account number and displays its details.
     */
    void searchAccount();

    /**
     * @brief Prints the hierarchical structure of the account tree.
     */
    void printTree();

    /**
     * @brief Saves the current accounts in the system to a specified file.
     * @param filePath Path to the file where accounts should be saved.
     */
    void saveAccountsToFile(const std::string& filePath);

    /**
     * @brief Removes an account from the system based on its account number.
     */
    void removeAccount();

    /**
     * @brief Logs transaction details to a file for auditing and record-keeping.
     * @param accountNumber The account number associated with the transaction.
     * @param transactionType A description of the transaction type.
     * @param date The date of the transaction.
     * @param transactionSign '+' for credit or '-' for debit.
     * @param amount The amount involved in the transaction.
     */
    void saveTransactionLog(const std::string& accountNumber,
                            const std::string& transactionType,
                            const std::string& date,
                            char transactionSign,
                            double amount);

private:
    bool isAuthenticated;                 ///< Tracks whether the user is authenticated.
    std::string accounts_path;            ///< Path to the file containing account data.
    std::string transaction_path;         ///< Path to the file containing transaction logs.
    ForestTree<Account> forest;           ///< Hierarchical tree structure for managing accounts.
};

#endif