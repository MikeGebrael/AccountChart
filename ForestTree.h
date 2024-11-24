#ifndef FORESTTREE_H
#define FORESTTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Account.h"

/**
 * @class ForestTree
 * @brief Template class representing a hierarchical forest tree structure for accounts.
 *
 * The `ForestTree` class is designed to represent a tree structure where each node
 * corresponds to an `Account`. The structure supports hierarchical relationships between
 * accounts, allowing for child and sibling nodes. It includes functionalities for
 * adding, finding, and removing accounts, processing data from a file, and printing
 * the tree structure.
 *
 * @tparam T The data type for the tree nodes (in this case, `Account`).
 */
template <typename T>
class ForestTree {
public:
    /**
     * @brief Default constructor initializing an empty tree.
     */
    ForestTree() : root(nullptr) {}

    /**
     * @brief Retrieves all accounts in the tree as a vector.
     * @return A vector of `Account` objects.
     */
    std::vector<Account> getAllAccounts() const {
        std::vector<Account> accounts;
        collectAccountsRecursive(root, accounts);
        return accounts;
    }

    /**
     * @brief Adds an account to the tree.
     * @param account The `Account` object to add.
     */
    void addAccount(const Account& account) {
        root = addAccountRecursive(root, account);
    }

    /**
     * @brief Initializes the tree with an account (used during file loading).
     * @param account The `Account` object to initialize in the tree.
     */
    void initializingAccount(const Account& account) {
        root = addAccountRecursive(root, account);
    }

    /**
     * @brief Finds an account in the tree by its account number.
     * @param accountNumber The account number to search for.
     * @return A pointer to the `Account` object, or `nullptr` if not found.
     */
    Account* findAccount(const std::string& accountNumber) {
        Node* foundNode = findAccountRecursive(root, accountNumber);
        return (foundNode != nullptr) ? &foundNode->account : nullptr;
    }

    /**
     * @brief Processes a hierarchical file to populate the tree.
     * @param filePath The path to the input file containing account data.
     *
     * The file should contain lines with an account number followed by a description.
     */
    void processHierarchicalFile(const std::string& filePath) {
        std::ifstream inputFile(filePath);

        if (!inputFile.is_open()) {
            std::cerr << "Error: Could not open file " << filePath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            if (line.empty()) continue;

            std::string accountNumber, accountName;
            parseLine(line, accountNumber, accountName);

            if (!accountNumber.empty() && !accountName.empty()) {
                initializingAccount(Account(accountNumber, accountName));
            }
        }

        inputFile.close();
    }

    /**
     * @brief Removes an account from the tree by its account number.
     * @param accountNumber The account number to remove.
     */
    void removeAccount(const std::string& accountNumber) {
        root = removeAccountRecursive(root, accountNumber);
    }

    /**
     * @brief Prints the tree structure to the console.
     */
    void printTree() const {
        printTreeRecursive(root, 0);
    }

private:
    /**
     * @struct Node
     * @brief Represents a node in the tree containing an `Account` and pointers to its child and sibling.
     */
    struct Node {
        Account account; ///< The account stored in the node.
        Node* child;     ///< Pointer to the first child node.
        Node* sibling;   ///< Pointer to the next sibling node.

        /**
         * @brief Constructs a Node with an `Account`.
         * @param acc The account to store in the node.
         */
        Node(const Account& acc) : account(acc), child(nullptr), sibling(nullptr) {}
    };

    Node* root; ///< Root node of the tree.

    /**
     * @brief Recursively collects accounts from the tree into a vector.
     * @param current The current node in the recursion.
     * @param accounts The vector to store accounts.
     */
    void collectAccountsRecursive(Node* current, std::vector<Account>& accounts) const {
        if (current == nullptr) return;

        accounts.push_back(current->account);
        collectAccountsRecursive(current->child, accounts);
        collectAccountsRecursive(current->sibling, accounts);
    }

    /**
     * @brief Recursive helper to add accounts to the tree.
     * @param current The current node in the recursion.
     * @param account The account to add.
     * @return A pointer to the updated node.
     */
    Node* addAccountRecursive(Node* current, const Account& account) {
        if (current == nullptr) {
            return new Node(account);
        }

        if (account.getAccountNumber().find(current->account.getAccountNumber()) == 0) {
            current->child = addAccountRecursive(current->child, account);
        } else {
            current->sibling = addAccountRecursive(current->sibling, account);
        }

        return current;
    }

    /**
     * @brief Recursive helper to find an account by account number.
     * @param current The current node in the recursion.
     * @param accountNumber The account number to search for.
     * @return A pointer to the node containing the account, or `nullptr` if not found.
     */
    Node* findAccountRecursive(Node* current, const std::string& accountNumber) const {
        if (current == nullptr) {
            return nullptr;
        }

        if (current->account.getAccountNumber() == accountNumber) {
            return current;
        }

        Node* found = findAccountRecursive(current->child, accountNumber);
        if (found != nullptr) return found;

        return findAccountRecursive(current->sibling, accountNumber);
    }

    /**
     * @brief Parses a line from the input file to extract account details.
     * @param line The line to parse.
     * @param accountNumber Output parameter for the account number.
     * @param accountName Output parameter for the account name.
     */
    void parseLine(const std::string& line, std::string& accountNumber, std::string& accountName) {
        std::istringstream iss(line);
        iss >> accountNumber;
        std::getline(iss, accountName);
        if (!accountName.empty() && accountName[0] == ' ') {
            accountName.erase(0, 1); // Remove leading space
        }
    }

    /**
     * @brief Prints the tree structure recursively.
     * @param current The current node in the recursion.
     * @param depth The current depth level in the tree.
     */
    void printTreeRecursive(Node* current, int depth) const {
        if (current == nullptr) return;

        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }
        std::cout << current->account.getAccountNumber()
                  << " - " << current->account.getDescription() << std::endl;

        printTreeRecursive(current->child, depth + 1);
        printTreeRecursive(current->sibling, depth);
    }

    /**
     * @brief Recursive helper to remove an account from the tree.
     * @param current The current node in the recursion.
     * @param accountNumber The account number to remove.
     * @return A pointer to the updated node.
     */
    Node* removeAccountRecursive(Node* current, const std::string& accountNumber) {
        if (current == nullptr) {
            return nullptr;
        }

        if (current->account.getAccountNumber() == accountNumber) {
            Node* temp = current->sibling;
            delete current;
            return temp;
        }

        current->child = removeAccountRecursive(current->child, accountNumber);
        current->sibling = removeAccountRecursive(current->sibling, accountNumber);
        return current;
    }
};

#endif // FORESTTREE_H
