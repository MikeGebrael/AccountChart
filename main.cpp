#include <iostream>
#include "System.h"

int main() {
    /**
     * @brief Main entry point for the application.
     *
     * This function serves as the entry point for the program. It creates an
     * instance of the `System` class and calls the `authenticate()` and `mainMenu()`
     * methods to handle user authentication and provide access to the main menu
     * of the application.
     *
     * - First, the user is prompted to authenticate using the `authenticate()` method.
     * - If authentication is successful, the `mainMenu()` method is called to display
     *   the main menu and allow the user to interact with accounts, add transactions,
     *   and perform other actions.
     *
     * The application will terminate when the user exits the menu.
     *
     * @return int Exit status of the program (0 indicates successful execution).
     */
    System system;           ///< Create an instance of the System class
    system.authenticate();   ///< Authenticate the user
    system.mainMenu();       ///< Display the main menu and handle user actions

    return 0;  ///< Return 0 indicating successful execution
}
