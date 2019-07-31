#include <iostream>
#include <gtest/gtest.h>
#include "test_functions.h"

// User created test files
#include "test_myLib.h"

// Run all tests
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}