#include <iostream>
#include "Matrices.hpp"

/**
 * \file main.cpp
 * \brief Implementation of the Matrix class test suite.
 *
 * This file contains the implementation of a Matrix class test suite that allows
 * performing basic matrix operations: creation, resizing, arithmetic operations,
 * and dynamic memory management.
 *
 * \author Angel Ricardo Vazquez Ortiz & Aram Alberto McGrew Valenzuela
 * \date 09/02/26
 *
 * \code{.cpp}
 * // Usage example:
 * Matrix m1(3, 3);          // Creates 3x3 matrix initialized to zeros
 * Matrix m2(3, 3);          // Creates another 3x3 matrix
 * m1.setElement(0, 0, 5.0); // Assigns value 5.0 to position (0,0)
 * Matrix m3 = m1 + m2;      // Matrix addition
 * \endcode
 */

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

/**
 * \brief Enumeration defining the main menu options for the program.
 */
/*
enum MenuOption {
    EXIT,               ///< Exit the program
    ENTER_MATRICES,     ///< Input or overwrite matrices m1 and m2
    SHOW_MATRICES,      ///< Display the current matrices
    ADDITION,           ///< Perform matrix addition (m1 + m2)
    SUBTRACTION,        ///< Perform matrix subtraction (m1 - m2)
    MULTIPLICATION,     ///< Perform matrix multiplication (m1 * m2)
    SCALAR_MULT,        ///< Perform scalar multiplication (k * m1)
    TRANSPOSE,          ///< Calculate the transpose of m1
    INVERSE,            ///< Calculate the inverse of m1 (square matrices only)
    RESIZE,             ///< Resize matrix m1
    ASSIGN_TEST         ///< Test assignment and copy (deep copy test)
};
*/

/**
 * \brief Displays the main matrix operations menu.
 *
 * \warning This function only displays the menu; it does not process the selection.
 * \post The menu is printed to the standard output.
 */
void displayMenu() {
    cout << "\n--- C++ MATRIX CLASS TEST SUITE ---" << endl;
    cout << "1.  Enter/Overwrite Matrices (m1 & m2)" << endl;
    cout << "2.  Show Current Matrices" << endl;
    cout << "3.  Addition (m1 + m2)" << endl;
    cout << "4.  Subtraction (m1 - m2)" << endl;
    cout << "5.  Matrix Multiplication (m1 * m2)" << endl;
    cout << "6.  Scalar Multiplication (k * m1)" << endl;
    cout << "7.  Transpose of m1" << endl;
    cout << "8.  Inverse of m1 (Square matrices only)" << endl;
    cout << "9.  Resize m1" << endl;
    cout << "10. Test Assignment and Copy (Deep Copy Test)" << endl;
    cout << "0.  Exit" << endl;
    cout << "Select an option: ";
}

/**
 * \brief Main entry point of the Matrix Test Suite.
 *
 * This function orchestrates the interaction between the user and the Matrix class,
 * demonstrating dynamic memory allocation, operator overloading, and error handling.
 *
 * \return 0 upon successful program termination.
 */
int main() {
    // Initializing with default values
    Matrix m1(2, 2), m2(2, 2);
    int choice;
    double scalar;
    int r, c;

    do {
        displayMenu();
        if (!(cin >> choice)) {
            cerr << "Invalid menu input." << endl;
            break;
        }

        try {
            switch (choice) {
                case 1:
                    cout << "Configuring Matrix 1:" << endl;
                    cout << "Rows: "; cin >> r; cout << "Cols: "; cin >> c;
                    m1.resize(r, c); // Resize handles validation internally
                    cin >> m1;

                    cout << "Configuring Matrix 2:" << endl;
                    cout << "Rows: "; cin >> r; cout << "Cols: "; cin >> c;
                    m2.resize(r, c);
                    cin >> m2;
                    break;

                case 2:
                    cout << "Matrix 1:\n" << m1 << endl;
                    cout << "Matrix 2:\n" << m2 << endl;
                    break;

                case 3:
                    // Checks dimensions before adding
                    cout << "Result (m1 + m2):\n" << (m1 + m2) << endl;
                    break;

                case 4:
                    // Checks dimensions before subtracting
                    cout << "Result (m1 - m2):\n" << (m1 - m2) << endl;
                    break;

                case 5:
                    // Matrix multiplication rule: A.cols == B.rows
                    cout << "Result (m1 * m2):\n" << (m1 * m2) << endl;
                    break;

                case 6:
                    cout << "Enter scalar value: ";
                    cin >> scalar;
                    // Commutative scalar multiplication
                    cout << "Result (" << scalar << " * m1):\n" << (scalar * m1) << endl;
                    break;

                case 7:
                    cout << "Transpose of m1:\n" << m1.transpose() << endl;
                    break;

                case 8:
                    // Only applicable to non-singular square matrices
                    cout << "Inverse of m1:\n" << m1.inverse() << endl;
                    break;

                case 9:
                    cout << "Enter new dimensions for m1 (Rows Cols): ";
                    cin >> r >> c;
                    m1.resize(r, c); // Adjusts memory while preserving compatible data
                    cout << "Resized Matrix 1:\n" << m1 << endl;
                    break;

                case 10: {
                    cout << "Creating m3 as a copy of m1..." << endl;
                    Matrix m3 = m1; // Test copy constructor (Deep Copy)
                    cout << "Assigning m1 to m2..." << endl;
                    m2 = m1; // Test assignment operator
                    cout << "All matrices are now equal. Modifying m1[0][0] to check deep copy..." << endl;
                    m1[0][0] = 999.99;
                    cout << "m1[0][0]: " << m1[0][0] << endl;
                    cout << "m3[0][0] (should be original): " << m3[0][0] << endl;
                    break;
                }

                case 0:
                    cout << "Exiting program..." << endl;
                    break;

                default:
                    cout << "Invalid option. Try again." << endl;
            }
        } catch (const char* msg) {
            // Handles logic errors (Dimension mismatch, singular matrices, etc.)
            cerr << "\n[RUNTIME ERROR]: " << msg << endl;
        } catch (std::exception& e) {
            // Handles standard exceptions like memory allocation failure
            cerr << "\n[EXCEPTION]: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}