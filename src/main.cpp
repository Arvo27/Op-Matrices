#include <iostream>
#include "Matrices.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

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
                    m1.resize(r, c);
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
                    cout << "Result (m1 + m2):\n" << (m1 + m2) << endl;
                    break;

                case 4:
                    cout << "Result (m1 - m2):\n" << (m1 - m2) << endl;
                    break;

                case 5:
                    cout << "Result (m1 * m2):\n" << (m1 * m2) << endl;
                    break;

                case 6:
                    cout << "Enter scalar value: ";
                    cin >> scalar;
                    cout << "Result (" << scalar << " * m1):\n" << (scalar * m1) << endl;
                    break;

                case 7:
                    cout << "Transpose of m1:\n" << m1.transpose() << endl;
                    break;

                case 8:
                    cout << "Inverse of m1:\n" << m1.inverse() << endl;
                    break;

                case 9:
                    cout << "Enter new dimensions for m1 (Rows Cols): ";
                    cin >> r >> c;
                    m1.resize(r, c);
                    cout << "Resized Matrix 1:\n" << m1 << endl;
                    break;

                case 10: {
                    cout << "Creating m3 as a copy of m1..." << endl;
                    Matrix m3 = m1; // Test copy constructor
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
            cerr << "\n[RUNTIME ERROR]: " << msg << endl;
        } catch (std::exception& e) {
            cerr << "\n[EXCEPTION]: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}