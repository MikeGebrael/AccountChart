cmake_minimum_required(VERSION 3.29)
project(AccountChart)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# List all source files
set(SOURCE_FILES
        main.cpp
        System.cpp
)

# List all header files
set(HEADER_FILES
        Transaction.h
        Account.h
        ForestTree.h
        System.h
)

# Create the executable
add_executable(AccountChart ${SOURCE_FILES} ${HEADER_FILES})
