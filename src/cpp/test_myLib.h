//
//  Tests for myLib
//
//  James Morris
//  UKAEA
//  30/07/19
//
//---------------------------------------

TEST(myLib, mySub_test_1) { 
   int a = 1;
   int b;
   
   myLib_mySub(&a, &b);
   EXPECT_EQ(b, 15);
}

TEST(myLib, mySub_test_2) { 
   int a = 1;
   extern int shared_value;
   shared_value = 20;
   int b;

   myLib_mySub(&a, &b);
   EXPECT_EQ(b, 20);
}

TEST(myLib, binomial_1) { 
   int n = 1;
   int k = 1;
   double c;
   c = myLib_binomial(&n, &k);
   EXPECT_EQ(1.0, c);
}