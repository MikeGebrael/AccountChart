#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <sstream>

/**
 * @class Transaction
 * @brief Represents a financial transaction with a specific amount and type.
 *
 * This class encapsulates a financial transaction, which includes an amount
 * and a type (Debit or Credit). It provides methods to access the transaction
 * details, convert the transaction information into a string format for reporting,
 * and supports input/output operations using overloaded operators.
 */
class Transaction {
public:
    /**
     * @brief Default constructor.
     * Initializes the transaction with default values.
     */
    Transaction() : amount(0.0), type('D') {}

    /**
     * @brief Constructs a Transaction object.
     * @param amount The monetary amount of the transaction.
     * @param type The type of the transaction ('D' for Debit, 'C' for Credit).
     */
    Transaction(double amount, char type) : amount(amount), type(type) {}

    /**
     * @brief Retrieves the amount of the transaction.
     * @return The transaction amount as a double.
     */
    double getAmount() const { return amount; }

    /**
     * @brief Retrieves the type of the transaction.
     * @return The transaction type as a character ('D' or 'C').
     */
    char getType() const { return type; }

    /**
     * @brief Converts the transaction details to a string.
     * @return A string representation of the transaction in the format:
     *         "Type: <type> Amount: <amount>".
     */
    std::string toString() const {
        return "Type: " + std::string(1, type) + " Amount: " + std::to_string(amount);
    }

    /**
     * @brief Overloaded output stream operator.
     * Prints the transaction details to the output stream.
     * @param os The output stream object.
     * @param transaction The transaction to output.
     * @return The output stream object.
     */
    friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction) {
        os << "Type: " << transaction.type << " Amount: " << transaction.amount;
        return os;
    }

    /**
     * @brief Overloaded input stream operator.
     * Reads the transaction details from the input stream.
     * @param is The input stream object.
     * @param transaction The transaction to populate.
     * @return The input stream object.
     */
    friend std::istream& operator>>(std::istream& is, Transaction& transaction) {
        std::cout << "Enter transaction type (D/C): ";
        is >> transaction.type;
        std::cout << "Enter transaction amount: ";
        is >> transaction.amount;
        return is;
    }

    /**
     * @brief Compares two transactions for equality.
     * @param other The transaction to compare against.
     * @return True if both transactions have the same type and amount, false otherwise.
     */
    bool operator==(const Transaction& other) const {
        return (type == other.type) && (amount == other.amount);
    }

    /**
     * @brief Compares two transactions for inequality.
     * @param other The transaction to compare against.
     * @return True if the transactions differ in type or amount, false otherwise.
     */
    bool operator!=(const Transaction& other) const {
        return !(*this == other);
    }

private:
    double amount; ///< The monetary amount of the transaction.
    char type;     ///< The type of the transaction ('D' for Debit, 'C' for Credit).
};

#endif // TRANSACTION_H
