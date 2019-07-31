#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

// 
//  Place subroutines and functions for testing here
//  Use the name given in the bind(C, name="") in the Fortran source
//
extern "C"
{
   
   //
   // Testing for module myLib
   //   
   void myLib_mySub(int *, int *);
   double myLib_binomial(int *, int *);
}

#endif
