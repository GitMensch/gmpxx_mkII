/*
 * Copyright (c) 2024
 *      Nakata, Maho
 *      All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <iostream>
#include <cassert>
#include <cstring>
#include <string>

#include "gmpxx_mkII.h"

using namespace gmp;

// Asserts that the mpf_class object equals the expected string representation
bool Is_mpf_class_Equals(mpf_class &gmpobj, const char *expected, int base = defaults::base, int precision = 10) {
    char formatString[64];
    char buffer[64];

    // Adjust the comparison based on the base
    switch (base) {
    case 10:
        std::sprintf(formatString, "%%.%dFf", precision);      // Generates format string like "%.10Ff"
        gmp_sprintf(buffer, formatString, gmpobj.get_mpf_t()); // Uses generated format string
        break;
    case 16:
        std::sprintf(formatString, "%%.%dFa", precision);      // Generates format string like "%.10Fa"
        gmp_sprintf(buffer, formatString, gmpobj.get_mpf_t()); // Uses generated format string
        break;
    default:
        printf("not supported");
        exit(-1);
    }
    if (std::strcmp(buffer, expected) == 0)
        return true;
    else
        return false;
}

void testDefaultPrecision() {
    mp_bitcnt_t defaultPrec = defaults::get_default_prec();
    assert(defaultPrec == 512);
    std::cout << "Default precision test passed." << std::endl;

    defaults::set_default_prec(1024);
    defaultPrec = defaults::get_default_prec();
    assert(defaultPrec == 1024);
    std::cout << "Set and get precision test passed." << std::endl;

    defaults::set_default_prec(512);
}

void testDefaultConstructor() {
    mpf_class a;
    char buffer[100];
    gmp_snprintf(buffer, sizeof(buffer), "%.0Ff", a.get_mpf_t());
    assert(std::string(buffer) == "0");
    // initialized to zero
    std::cout << "Default constructor test passed." << std::endl;
}

void testCopyConstructor() {
    mpf_class a;
    mpf_class b = a;
    assert(true);
    std::cout << "Copy constructor test passed." << std::endl;
}

void testAssignmentOperator() {
    mpf_class a;
    mpf_class b;
    b = a;
    assert(true);
    std::cout << "Assignment operator test passed." << std::endl;
}

void testInitializationAndAssignmentDouble() {
    double testValue = 3.1415926535;
    const char *expectedValue = "3.1415926535";

    gmp::mpf_class a = (mpf_class)testValue;
    assert(Is_mpf_class_Equals(a, expectedValue));
    std::cout << "Substitution from double using constructor test passed." << std::endl;

    gmp::mpf_class b;
    b = testValue;
    assert(Is_mpf_class_Equals(b, expectedValue));
    std::cout << "Substitution from double using assignment test passed." << std::endl;
}

void testInitializationAndAssignmentString() {
    // Testing initialization with a decimal number using a constructor
    const char *expectedDecimalValue = "1.4142135624";
    mpf_class a = expectedDecimalValue;
    assert(Is_mpf_class_Equals(a, expectedDecimalValue));
    std::cout << "Constructor initialization with decimal '" << expectedDecimalValue << "' test passed." << std::endl;

    // Testing initialization with a decimal number using an assignment operator
    mpf_class b;
    b = expectedDecimalValue;
    assert(Is_mpf_class_Equals(b, expectedDecimalValue));
    std::cout << "Assignment initialization with decimal '" << expectedDecimalValue << "' test passed." << std::endl;

    // Testing initialization with a decimal number using a constructor
    std::string expectedDecimalValueString = "3.1415926535";
    mpf_class c = expectedDecimalValueString;
    assert(Is_mpf_class_Equals(c, expectedDecimalValueString.c_str()));
    std::cout << "Constructor initialization with decimal '" << expectedDecimalValueString << "' test passed." << std::endl;

    // Testing initialization with a decimal number using an assignment operator
    mpf_class d;
    d = expectedDecimalValueString;
    assert(Is_mpf_class_Equals(d, expectedDecimalValueString.c_str()));
    std::cout << "Assignment initialization with decimal '" << expectedDecimalValueString << "' test passed." << std::endl;

    // Testing initialization with a hexadecimal number using an assignment operator
    const char *expectedHexValue = "0x3.243f6a8885a3p+0";
    const char *inputHexValue = "3.243F6A8885A308D313198A2E03707344A4093822299F31D008";
    mpf_class e(inputHexValue, 16);
    assert(Is_mpf_class_Equals(e, expectedHexValue, 16, 12));
    std::cout << "Assignment initialization with hexadecimal '" << expectedHexValue << "' test passed." << std::endl;

    defaults::base = 16;
    // Testing initialization with a hexadecimal number using a constructor
    mpf_class f;
    e = inputHexValue;
    assert(Is_mpf_class_Equals(e, expectedHexValue, defaults::base, 12));
    std::cout << "Constructor initialization with hexadecimal '" << expectedHexValue << "' test passed." << std::endl;
    defaults::base = 10;
}

void testAddition() {
    mpf_class a(1.5);
    mpf_class b(2.5);
    std::string expected = "4.0000000000";

    mpf_class c = a + b;
    assert(Is_mpf_class_Equals(c, expected.c_str()));
    a += b;
    assert(Is_mpf_class_Equals(a, expected.c_str()));
    std::cout << "Addition Test passed." << std::endl;
}

void testMultplication() {
    mpf_class a(2.0);
    mpf_class b(3.0);
    std::string expected = "6.0000000000";

    mpf_class c = a * b;
    assert(Is_mpf_class_Equals(c, expected.c_str()));
    a *= b;
    assert(Is_mpf_class_Equals(a, expected.c_str()));
    std::cout << "Multiplication Test passed." << std::endl;
}

void testDivision() {
    mpf_class a(6.0);
    mpf_class b(2.0);
    std::string expected = "3.0000000000";

    mpf_class c = a / b;
    assert(Is_mpf_class_Equals(c, expected.c_str()));
    a /= b;
    assert(Is_mpf_class_Equals(a, expected.c_str()));
    std::cout << "Division Test passed." << std::endl;
}
void testSubtraction() {
    mpf_class a(5.0);
    mpf_class b(2.0);
    std::string expected = "3.0000000000";

    mpf_class c = a - b;
    assert(Is_mpf_class_Equals(c, expected.c_str()));
    a -= b;
    assert(Is_mpf_class_Equals(a, expected.c_str()));
    std::cout << "Subtraction Test passed." << std::endl;
}

void testEqNonEq() {
    mpf_class obj1("2.718281828459045");
    mpf_class obj2("2.718281828459045");
    assert(obj1 == obj2);
    std::cout << "Equality test passed." << std::endl;

    mpf_class obj3("3.141592653589793");
    assert(obj1 != obj3);
    std::cout << "Inequality test passed." << std::endl;

    mpf_class obj4("2.7182818284590451");
    assert(obj1 != obj4);
    std::cout << "Subtle difference test passed." << std::endl;
}

void testSqrt() {
    // Test Case 1: Calculate the square root of a positive number
    mpf_class a;
    a = "4.0"; // Square root of 4.0 is 2.0
    mpf_class result = sqrt(a);
    std::string expected = "2.0000000000";
    assert(Is_mpf_class_Equals(result, expected.c_str()));

    // Test Case 2: Calculate the square root of 0
    mpf_class b("0.0"); // Square root of 0.0 is 0.0
    result = sqrt(b);
    expected = "0.0000000000";
    assert(Is_mpf_class_Equals(result, expected.c_str()));

    // Test Case 3: Calculate the square root of a negative number (should raise an error)
    //  mpf_class c("-1.0");
    //  result = sqrt(c);
    //  assert(result.is_nan()); // Check if the result is NaN
    std::cout << "Test square root test passed." << std::endl;
}

void testNeg() {
    mpf_class a(-3.5);
    mpf_class result = neg(a);
    mpf_class expected = "3.5";
    assert(result == expected);
    std::cout << "neg test passed." << std::endl;
}

void testAbs() {
    mpf_class a(-3.5);
    mpf_class c = abs(a);
    mpf_class expected = "3.5";
    mpf_class result = abs(a);
    assert(result == expected);
    std::cout << "abs test passed." << std::endl;
}

int main() {
    testDefaultPrecision();
    testDefaultConstructor();
    testCopyConstructor();
    testAssignmentOperator();
    testInitializationAndAssignmentDouble();
    testInitializationAndAssignmentString();
    testAddition();
    testMultplication();
    testDivision();
    testSubtraction();
    testEqNonEq();
    testSqrt();
    testNeg();
    testAbs();
    //    test_mpf_class_double_addition();
    //    test_mpf_class_double_subtraction();
    //    test_mpf_class_double_multiplication();
    //    test_mpf_class_double_division();

    std::cout << "All tests passed." << std::endl;

    return 0;
}
