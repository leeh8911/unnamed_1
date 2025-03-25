/**
 * @file test_main.cpp
 * @brief Main file for running Google Test cases.
 * 
 * This file initializes and runs all the Google Test cases defined in the project.
 * 
 * @copyright Copyright (c) 2025
 */
 
#include <gtest/gtest.h>

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}