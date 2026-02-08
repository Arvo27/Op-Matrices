#include <iostream>
#include "Matrices.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

int main()
{
    try {
        //The user must enter the entries
        int rows, columns, rows2, columns2;
        cout << "Enter the number of rows for the matrix 1: ";
        if(!(cin >> rows)) throw "Invalid input for rows.";
        cout << "Enter the number of columns for the matrix 1: ";
        if(!(cin >> columns)) throw "Invalid input for columns.";
        Matrix m1(rows, columns);
        m1.capture();

        cout << "Enter the number of rows for the matrix 2: ";
        if(!(cin >> rows2)) throw "Invalid input for rows.";
        cout << "Enter the number of columns for the matrix 2: ";
        if(!(cin >> columns2)) throw "Invalid input for columns.";
        Matrix m2(rows2, columns2);
        m2.capture();
        //a
        cout << m1 << endl;
        cout << m2 << endl;

        // Try resizing the first matrix
        cout << "Resizing matrix 1 to 2x2...\n";
        m1.resize(2, 2);
        cout << m1 << endl;

        //Try Sum matrix
        Matrix sum = m1 + m2;
        cout << "Sum matrix:" << endl << sum << endl;

        //Try subtraction matrix
        Matrix subtraction = m1 - m2;
        cout << "Subtraction matrix:" << endl << subtraction << endl;


        //Try Product of two matrices
        Matrix product = m1 * m2;
        cout << "Product matrix:" << endl << product << endl;

        //Try transpose of matrices
        Matrix transpose = m1.transpose();
        cout << "Transpose matrix:" << endl << transpose << endl;

        //Try inverse of matrice
        Matrix inverse = m2.inverse();
        cout << "Inverse matrix:" << endl << inverse << endl;

        //Ahora probar el producto escalar
        double escalar = 2;
        Matrix escalarM = escalar * m1;
        cout << "Escalar matrix:" << endl << escalarM << endl;


    } catch(const char* msg) {
        cerr << "Error: " << msg << endl;

    } catch(...) {
        cerr << "An unexpected error occurred." << endl;
    }
}
