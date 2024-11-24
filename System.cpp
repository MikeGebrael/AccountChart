#include "System.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


/**
 * @brief Authenticates the user by verifying the username and password.
 *
 * Prompts the user to enter a username and password, and compares the input against
 * hardcoded credentials. If the credentials match, the user is authenticated successfully.
 *
 * @details The method uses a simple username ("admin") and password ("admin123") pair for authentication.
 * If the credentials are correct, the `isAuthenticated` flag is set to true and a success message is displayed.
 * Otherwise, an authentication failure message is shown.
 */
void System::authenticate() {
    std::string username, password;

    // Prompt user for username and password
    std::cout << "Enter username: ";
    std::cin >> username;  // Get input username

    std::cout << "Enter password: ";
    std::cin >> password;  // Get input password

    // Validate the username and password against hardcoded values
    if (username == "admin" && password == "admin123") {
        isAuthenticated = true;  // Set authentication status to true
        std::cout << "Authentication successful!" << std::endl;  // Notify user of success
    }
    else {
        isAuthenticated = false;  // Set authentication status to false
        std::cout << "Authentication failed!" << std::endl;  // Notify user of failure
    }
}


/**
 * @brief Displays the main menu and handles user interaction after successful authentication.
 *
 * Once the user is authenticated, the method presents a menu of options, processes user input,
 * and invokes the corresponding functions to manage accounts and transactions. The menu offers
 * the following actions: create an account, add a transaction, print an account report, search for an account,
 * print the account tree, remove an account, or exit the system.
 *
 * @details The method ensures that only authenticated users can access the main menu. If the user is not authenticated,
 * a prompt is shown. The method also loads the account data from a file and processes it before presenting the menu.
 * The menu is displayed repeatedly until the user selects the option to exit.
 */
void System::mainMenu() {
    if (!isAuthenticated) {
        std::cout << "You need to log in first!" << std::endl;
        return;  // Exit if user is not authenticated
    }

    // Load accounts from file
    std::string filePath = accounts_path;
    forest.processHierarchicalFile(filePath);  // Load account data from the specified file

    std::cout << "Accounts loaded successfully" << std::endl;

    int option;
    do {
        // Display main menu options
        std::cout << "\nMain Menu: \n"
            << "1. Create Account\n"
            << "2. Add Transaction\n"
            << "3. Print Account Report\n"
            << "4. Search Account\n"
            << "5. Print tree\n"
            << "6. Remove Account\n"
            << "7. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> option;  // User selects an option from the menu

        // Process the selected option
        switch (option) {
        case 1:
            createAccount();  // Create a new account
            break;
        case 2:
            addTransaction();  // Add a new transaction to an account
            break;
        case 3:
            printAccountReport();  // Print the report for a specific account
            break;
        case 4:
            searchAccount();  // Search for an account based on criteria
            break;
        case 5:
            printTree();  // Print the account tree structure
            break;
        case 6:
            removeAccount();  // Remove an existing account
            break;
        case 7:
            std::cout << "Exiting..." << std::endl;  // Exit the system
            break;
        default:
            std::cout << "Invalid option!" << std::endl;  // Handle invalid menu selections
        }
    } while (option != 7);  // Repeat menu until 'Exit' option is chosen
}


/**
 * @brief Creates a new account and adds it to both the in-memory structure and the file.
 *
 * This method prompts the user for an account number and description, validates the input, and ensures the account number
 * does not already exist in the file. Once validated, the account is added to the system's in-memory data structure
 * (forest) and written to the file in lexicographical order based on the account number.
 *
 * @details
 * The method checks that the account number entered consists only of digits, and it will repeatedly prompt the user
 * for a valid account number if the input is incorrect. It also checks whether an account with the same number already
 * exists in the file and prevents the creation of duplicate accounts. If the account is valid and does not already exist,
 * it is created and added to both the forest structure (for in-memory management) and the accounts file (for persistence).
 * The accounts are inserted into the file in lexicographical order based on the account number.
 *
 * @return void
 */
void System::createAccount() {
    std::string accountNumber, description;

    // Loop until a valid account number (digits only) is entered
    do {
        std::cout << "Enter account number (digits only): ";
        std::cin >> accountNumber;

        // Check if the account number contains only digits
        if (std::all_of(accountNumber.begin(), accountNumber.end(), ::isdigit)) {
            break;  // If it's valid, exit the loop
        }
        else {
            std::cout << "Invalid account number. Please enter digits only." << std::endl;
        }
    } while (true);

    // Check if the account already exists in the file
    std::ifstream inFile(accounts_path);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for reading!" << std::endl;
        return;
    }

    std::string line;
    bool accountExists = false;
    while (std::getline(inFile, line)) {
        std::istringstream lineStream(line);
        std::string fileAccountNumber;
        lineStream >> fileAccountNumber;
        if (fileAccountNumber == accountNumber) {
            accountExists = true;
            break;  // If the account exists, stop checking
        }
    }
    inFile.close();

    if (accountExists) {
        std::cout << "Account with number " << accountNumber << " already exists!" << std::endl;
        return;
    }

    // Get the description input
    std::cout << "Enter account description: ";
    std::cin.ignore();  // To clear the buffer before getline
    std::getline(std::cin, description);

    // Now, create the account in memory (forest structure)
    Account account(accountNumber, description);
    forest.addAccount(account);  // Add the new account to the forest
    std::cout << "Account created successfully!" << std::endl;

    // Read the existing accounts from the file
    std::ifstream inFile2(accounts_path);
    if (!inFile2.is_open()) {
        std::cerr << "Error: Could not open file for reading!" << std::endl;
        return;
    }

    std::vector<std::string> lines;
    while (std::getline(inFile2, line)) {
        lines.push_back(line);
    }
    inFile2.close();

    // Prepare the new account line
    std::string newAccountLine = accountNumber + " " + description + " 0";  // Format for the new account

    // Insert the new account at the correct position based on account number
    bool inserted = false;
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        std::istringstream lineStream(*it);
        std::string fileAccountNumber;
        lineStream >> fileAccountNumber;

        // Lexicographical comparison for string-based account number insertion
        if (fileAccountNumber > accountNumber) {
            lines.insert(it, newAccountLine);
            inserted = true;
            break;
        }
    }

    // If the new account is larger than all existing accounts, add it at the end
    if (!inserted) {
        lines.push_back(newAccountLine);
    }

    // Write the updated list of accounts back to the file
    std::ofstream outFile(accounts_path, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing!" << std::endl;
        return;
    }

    for (const auto& line : lines) {
        outFile << line << std::endl;
    }
    outFile.close();

    std::cout << "Account added to the file successfully!" << std::endl;
}


/**
 * @brief Adds a transaction to an account and updates both the in-memory data structure and the file.
 *
 * This method allows the user to add a transaction (credit or debit) to an existing account. It validates the account number,
 * transaction amount, and transaction type before processing the transaction. After updating the account's balance, the transaction
 * is logged to a transaction file, and the updated account data is saved to the accounts file.
 *
 * @details
 * The method first prompts the user to input the account number. If the account is found in the system, the user is then asked to
 * enter the transaction amount and specify the transaction type (either 'C' for credit or 'D' for debit). The transaction details
 * are validated, and if valid, the transaction is added to the account's transaction history. The account balance is updated based
 * on the transaction type, and the transaction is logged to a file for record-keeping. Finally, the updated account data is written
 * back to the accounts file.
 *
 * @return void
 */
void System::addTransaction() {
    std::string accountNumber;
    double amount;
    char letter;

    std::cout << "Enter account number: ";
    std::cin >> accountNumber;

    Account* account = forest.findAccount(accountNumber);

    if (account == nullptr) {
        std::cerr << "Account not found!" << std::endl;
        return;
    }

    std::cout << "Enter transaction amount: ";
    std::cin >> amount;

    char type;  // Variable to store the transaction type
    do {
        std::cout << "Enter transaction type (C for Credit, D for Debit): ";
        std::cin >> letter;

        type = toupper(letter);  // Ensure input is uppercase

        // Check if the input is valid (either 'C' or 'D')
        if (type == 'C' || type == 'D') {
            break;  // Exit the loop when a valid input is entered
        }
        else {
            std::cout << "Invalid transaction type! Please enter 'C' for Credit or 'D' for Debit." << std::endl;
        }
    } while (true);  // Keep looping until the user provides a valid input

    // Add the transaction to the account
    Transaction txn(amount, type);  // Use the validated transaction type
    account->addTransaction(txn);   // This updates the account balance after the transaction

    // Log the transaction to the file after the balance has been updated
    saveTransactionLog(transaction_path, account->getAccountNumber(),
        account->getDescription(), type, amount);

    // Write the updated account data to the file
    saveAccountsToFile(accounts_path);

    std::cout << "Transaction added successfully." << std::endl;
}


/**
 * @brief Prints a report of transactions for a specified account.
 *
 * This method retrieves and displays the transaction history for an account based on the account number provided by the user.
 * It first checks whether the account exists in the system. If found, it prints all transactions associated with that account.
 * If the account does not exist, an error message is displayed.
 *
 * @details
 * The method prompts the user to enter the account number. If the account exists, it calls the `printTransactions` method
 * on the corresponding account object to display a detailed list of transactions. If the account is not found, the method
 * prints an error message indicating that the account does not exist.
 *
 * @return void
 */
void System::printAccountReport() {
    std::string accountNumber;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;

    Account* account = forest.findAccount(accountNumber);
    if (account) {
        account->printTransactions();
    }
    else {
        std::cout << "Account not found!" << std::endl;
    }
}


/**
 * @brief Searches for an account based on the account number.
 *
 * This method prompts the user to input an account number and searches for the corresponding account in the system.
 * If the account is found, it displays the account number and description. If the account is not found, it shows an error message.
 *
 * @details
 * The method takes user input for an account number, searches for it in the forest structure using the `findAccount` method,
 * and then prints the account details (account number and description) if the account exists. If no account is found,
 * it notifies the user with an error message.
 *
 * @return void
 */
void System::searchAccount() {
    std::string accountNumber;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;

    Account* account = forest.findAccount(accountNumber);
    if (account) {
        std::cout << "Account found: " << account->getAccountNumber()
            << " - " << account->getDescription() << std::endl;
    }
    else {
        std::cout << "Account not found!" << std::endl;
    }
}


/**
 * @brief Prints the entire account tree structure.
 *
 * This method calls the `printTree` function of the forest object to display the hierarchical structure of accounts.
 *
 * @details
 * The method invokes the `printTree` method from the `Forest` class, which is responsible for outputting the entire
 * account tree, displaying the accounts in a tree-like structure. This allows the user to view all accounts and their
 * subaccounts in a visual hierarchy.
 *
 * @return void
 */
void System::printTree() {
    forest.printTree();
}

/**
 * @brief Removes an account from both memory and the file.
 *
 * This method removes the specified account from both the in-memory forest structure and the accounts file.
 * The method first checks if the account exists in memory, and if found, removes it from the forest.
 * Then, it updates the accounts file by removing the corresponding account entry.
 *
 * @details
 * The method begins by prompting the user to input the account number of the account to be removed.
 * If the account is found in memory, it is removed from the `forest` (in-memory structure).
 * The method then opens the accounts file, reads its content into a vector, and overwrites the file by writing
 * all lines back except the one containing the account to be removed. The account is excluded from the file,
 * effectively deleting it from both the file and memory.
 *
 * @return void
 */
void System::removeAccount() {
    std::string accountNumber;
    std::cout << "Enter account number to remove: ";
    std::cin >> accountNumber;

    // First, remove from memory
    Account* account = forest.findAccount(accountNumber);
    if (account) {
        forest.removeAccount(accountNumber);  // Remove from memory
        std::cout << "Account removed from memory!" << std::endl;
    }
    else {
        std::cout << "Account not found in memory!" << std::endl;
    }

    // Now, remove from the file
    std::ifstream inFile(accounts_path);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for reading!" << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    // Read the file into a vector of lines
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    // Open the file in write mode (overwrite the file)
    std::ofstream outFile(accounts_path, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing!" << std::endl;
        return;
    }

    bool found = false;

    // Write all lines back except the one that matches the account number
    for (auto& line : lines) {
        std::istringstream lineStream(line);
        std::string fileAccountNumber;
        lineStream >> fileAccountNumber;  // Read the account number from the file

        // If the account number matches, we skip writing this line
        if (fileAccountNumber == accountNumber) {
            found = true;
            continue; // Skip the line (don't write it back to the file)
        }

        // Otherwise, write the line back to the file
        outFile << line << std::endl;
    }

    outFile.close();

    if (found) {
        std::cout << "Account removed from file!" << std::endl;
    }
    else {
        std::cout << "Account not found in file!" << std::endl;
    }
}


/**
 * @brief Saves updated account information to a file.
 *
 * This method reads account information from the specified file, updates the balances if necessary based on
 * the in-memory data, and writes the updated account information back to the file. The file is overwritten
 * with the latest account details.
 *
 * @param filePath The path of the file where account information is saved.
 *
 * @details
 * The method starts by opening the specified file for reading. It reads all lines into a vector of strings.
 * Then, it processes each line to extract account numbers, descriptions, and balances. For each account,
 * it checks if the in-memory balance matches the file's balance. If there's a discrepancy, the balance is
 * updated to reflect the in-memory value. Finally, the updated account information is written back to the file,
 * overwriting the previous contents.
 *
 * @return void
 */
void System::saveAccountsToFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for reading! Path: " << filePath << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    std::ofstream outFile(filePath, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing! Path: " << filePath << std::endl;
        return;
    }

    // Process each line and update the balance only if necessary
    for (auto& line : lines) {
        std::istringstream lineStream(line);
        std::string accountNumber, description;
        double balance = 0.0;  // Initialize balance

        // Read the account number
        lineStream >> accountNumber;
        lineStream >> std::ws;  // Skip leading spaces

        // Now read the description and stop just before the balance
        std::string word;
        while (lineStream >> word) {
            // Check if the word is a valid number (the balance)
            if (isdigit(word[0]) || (word[0] == '-' && word.size() > 1 && isdigit(word[1]))) {
                balance = std::stod(word);  // The last token is the balance
                break;
            }
            else {
                description += word + " ";  // Add to description if it's not the balance
            }
        }

        // Trim the trailing space from description
        if (!description.empty() && description[description.length() - 1] == ' ') {
            description = description.substr(0, description.length() - 1);
        }

        // Find the account in memory
        Account* account = forest.findAccount(accountNumber);
        if (account != nullptr) {
            // If the in-memory balance differs from the file balance, update it
            if (account->getBalance() != balance) {
                balance = account->getBalance();  // Use the in-memory balance
            }
        }

        // Write the updated account information back to the file
        outFile << accountNumber << " " << description << " " << balance << std::endl;
    }

    outFile.close();
}


/**
 * @brief Logs a transaction to a specified file.
 *
 * This method logs the transaction details (account number, description, balance, type, and amount) to a transaction log file.
 * It first retrieves the account's current balance, processes the description to remove any numeric values, and appends the transaction details to the file.
 *
 * @param filePath The path of the file where the transaction log is saved.
 * @param accountNumber The account number associated with the transaction.
 * @param description The description of the transaction.
 * @param type The type of the transaction ('C' for Credit, 'D' for Debit).
 * @param amount The transaction amount.
 *
 * @details
 * This method finds the account in memory (in the forest structure), calculates the updated balance after the transaction,
 * processes the description to remove numeric characters (if any), and then appends the transaction details to the log file.
 * The transaction is logged in the following format:
 * <account number> <description> <updated balance> <transaction type> <amount>.
 * If the account is not found in memory, an error message is displayed, and the transaction is not logged.
 *
 * @return void
 */
void System::saveTransactionLog(const std::string& filePath, const std::string& accountNumber,
    const std::string& description, char type, double amount) {

    // Find the account in the memory (forest structure)
    Account* account = forest.findAccount(accountNumber);
    if (account == nullptr) {
        std::cerr << "Account not found!" << std::endl;
        return;
    }

    // Get the updated balance after the transaction is applied
    double updatedBalance = account->getBalance();

    // Process the description to stop right before the first digit
    std::string processedDescription = description;
    for (size_t i = 0; i < processedDescription.length(); ++i) {
        if (std::isdigit(processedDescription[i])) {
            processedDescription = processedDescription.substr(0, i);  // Truncate at the first digit
            break;
        }
    }

    // Open the log file in append mode
    std::ofstream logFile(filePath, std::ios::app);
    if (logFile.is_open()) {
        logFile << accountNumber << " " << processedDescription << " " << updatedBalance << " "
            << type << " " << amount << std::endl;
    }
    else {
        std::cerr << "Error: Could not open transaction log file!" << std::endl;
    }
}
