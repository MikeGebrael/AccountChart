#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <iostream>
#include "Transaction.h"

/**
 * @class Account
 * @brief Represents a financial account with associated transactions and balance.
 *
 * The `Account` class encapsulates details about an account, including its
 * account number, description, balance, and a list of transactions. It provides
 * methods for adding transactions, updating the balance, and printing account details.
 */
class Account {
public:
    /**
     * @brief Constructs an Account object.
     * @param accountNumber The unique identifier for the account.
     * @param description A brief description of the account.
     */
    Account(std::string accountNumber, std::string description)
        : accountNumber(accountNumber), description(description), balance(0.0) {}

    /**
     * @brief Retrieves the account number.
     * @return The account number as a string.
     */
    std::string getAccountNumber() const { return accountNumber; }

    /**
     * @brief Retrieves the account description.
     * @return The account description as a string.
     */
    std::string getDescription() const { return description; }

    /**
     * @brief Retrieves the current account balance.
     * @return The account balance as a double.
     */
    double getBalance() const { return balance; }

    /**
     * @brief Sets the account number.
     * @param accountNumber The new account number as a string.
     */
    void setAccountNumber(const std::string& accountNumber) { this->accountNumber = accountNumber; }

    /**
     * @brief Sets the account description.
     * @param description The new account description as a string.
     */
    void setDescription(const std::string& description) { this->description = description; }

    /**
     * @brief Sets the account balance.
     * @param balance The new balance as a double.
     */
    void setBalance(double balance) { this->balance = balance; }

    /**
     * @brief Adds a transaction to the account and updates the balance.
     * @param transaction The `Transaction` object to add.
     *
     * This method adds a transaction to the account's transaction history.
     * If the transaction is a credit ('C'), the balance is increased by the
     * transaction amount. If it's a debit ('D'), the balance is decreased.
     */
    void addTransaction(const Transaction& transaction) {
        transactions.push_back(transaction);
        // Update the balance based on the transaction type
        if (transaction.getType() == 'C' || transaction.getType() == 'c') {
            balance += transaction.getAmount(); // Credit: Increase balance
        } else if (transaction.getType() == 'D' || transaction.getType() == 'd') {
            balance -= transaction.getAmount(); // Debit: Decrease balance
        }
    }

    /**
     * @brief Prints the account details and transaction history to the console.
     *
     * This method displays the account number, description, and a list of all
     * transactions. Each transaction includes its type, amount, and the updated
     * running balance.
     */
    void printTransactions() const {
        std::cout << "Account " << accountNumber << ": " << description << std::endl;
        double runningBalance = balance; // Start with the current balance

        // Print each transaction and calculate the running balance
        for (const auto& txn : transactions) {
            std::cout << txn.toString() << std::endl;
            if (txn.getType() == 'C' || txn.getType() == 'c') {
                runningBalance += txn.getAmount(); // Credit: Increase balance
            } else if (txn.getType() == 'D' || txn.getType() == 'd') {
                runningBalance -= txn.getAmount(); // Debit: Decrease balance
            }
        }
    }

private:
    std::string accountNumber; ///< The unique identifier for the account.
    std::string description;   ///< A brief description of the account.
    double balance;            ///< The current balance of the account.
    std::vector<Transaction> transactions; ///< A list of transactions associated with the account.
};

#endif // ACCOUNT_H
