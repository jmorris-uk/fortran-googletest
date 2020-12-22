# Fortran Googletest

Example of googletest for Fortran code

## Requirements

The code requires an installation of googletest. See below for platform 
dependent options.

### Mac OSX

```
git clone https://github.com/google/googletest
cd googletest
mkdir install
cd install
cmake -DCMAKE_CXX_COMPILER="c++" -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libc++" ../  
make
sudo make install
cd ../googletest
mkdir lib
cp ../install/lib/*.a lib
```

Set the environment path in `.bash_profile`

```bash
export GTEST=<path_to_googletest_folder>/googletest/googletest/
```

### Ubuntu

Packages required

```bash
sudo apt-get install libgtest-dev
sudo apt-get install cmake
```

Googletest still needs to be compiled

```bash
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo make install
```

## Building

Clone the repository and in the top level of the repo run:

```bash
cmake -H. -Bbuild
cmake --build build
```

This will create a file in `bin/` as below:

```bash
./bin/GTest.exe
```

To run the unit tests enter into the terminal:
```bash
./bin/GTest.exe
```

The output should look like:
```b
[==========] Running 3 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 3 tests from myLib
[ RUN      ] myLib.mySub_test_1
[       OK ] myLib.mySub_test_1 (0 ms)
[ RUN      ] myLib.mySub_test_2
[       OK ] myLib.mySub_test_2 (0 ms)
[ RUN      ] myLib.binomial_1
[       OK ] myLib.binomial_1 (0 ms)
[----------] 3 tests from myLib (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 3 tests.
```

## Adding test without module variables

This will outline the procedure for adding a new basic test. The Fortran 
function to be added is one that calculates the binomial coefficient for a 
given n, k. This function is defined in `myLib_module.f90` as

```fortran
real(kind=dp)  function binomial(n,k) result(coefficient) &
    bind (C, name="myLib_binomial")

    implicit none

    integer, intent(in) :: n, k
    integer :: numerator, i

    if (k == 0) then
        coefficient = 1
    else
        coefficient = 1.0D0
        do i = 1, k
            numerator = n + 1 -i
            coefficient = coefficient * real(numerator)/real(i)
        end do
    end if
  
end function binomial
```

The function takes two arguments `n` and `k` and returns a result, 
`coefficient`. The `bind` keyword provides a link between the C++ 
googletest framework and the Fortran. The `name` is the name that the 
function will be referred to from the C++. The changes required to the files 
for this example are as follows.

### main_test.cpp

Below is an outline of the `main_test.cpp` file in the repository.

```c++
#include <iostream>
#include <gtest/gtest.h>

#include "test_myLib.h"

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

To add the new test in `test_myLib.h` a new `include` statement is required in 
this file, if is not already present. To add a test to an existing set of 
tests there is no need to add anything here.

### test_myLib.h

Below is the contents of the `test_myLib.h` file which will contain the 
tests for the source file `myLib_module.f90`.

```c++
TEST(myLib, binomial_1) { 
   int n = 1;
   int k = 1;
   double c;
   c = myLib_binomial(&n, &k);
   EXPECT_EQ(1.0, c);
}
```

The first statement defines which group of tests the test `binomial_1` belongs 
to (`myLib`). Then declare in C++ the two arguments required for 
the function, `n` and `k`.

```c++
int n = 1;
int k = 1;
```

A local declaration for the function result is also required.

```c++
double c;
```

The test is then called using the `name` given in the C `bind` statement from 
the function declaration in `myLib_module.f90`.

```c++
c = myLib_binomial(&n, &k);
```

The last part of the test performs the check against the expected value

```c++
EXPECT_EQ(1.0, c);
```

This asserts the expected outcome binomial(1,1) == 1. It will report a 
failure otherwise.

### test_functions.h

Below is the part of `test_functions.h` that needs to be modified to add 
the new unit test `binomial_1`.

```c++
extern "C"
{
   //
   // Testing for module myLib
   //   
   void myLib_mySub(int *, int *);
   double myLib_binomial(int *, int *);
}
```

The final line

```c++
double myLib_binomial(int *, int *);
```

Tells the googletest C++ framework about the binomial function, referring to 
the `bind` name that was given. It also tells the framework what arguments 
to expect (to integer pointers) and what value the function returns 
(`double`). If the subroutine didn't return a value one would declare is 
as `void <subroutine_name>`.

## Adding test with module variables

In Fortran a subroutine can use variables outside of the scope of the 
subroutine by importing variables from other modules using the `use` statement. 
Such as,

```fortran
use otherLib, only: shared_value
```

Found in `otherLib_module.f90`.

### otherLib_module.f90

To add a C binding to a module variable change

```fortran
integer :: shared_value = 15
```

to:

```fortran
integer, bind(C) :: shared_value = 15
```

## test_myLib.h

Once complete add the test case to the `test_myLib.h` file, such as:

```c++
TEST(myLib, mySub_test_2) { 
   int a = 1;
   extern int shared_value;
   shared_value = 20;
   int b;

   myLib_mySub(&a, &b);
   EXPECT_EQ(b, 20);
}
```

This test overwrites the initial value of the module variable.

## Assert statements

```c++
ASSERT_LT(14.711, val);
ASSERT_GT(14.71, val);
EXPECT_EQ(14.71, val);
ASSERT_DOUBLE_EQ(14.71, val);
EXPECT_NEAR(b, a, tolerance);
```

Where tolerance is a `real`.

## Contact

[James Morris](james.morris2@ukaea.uk)
