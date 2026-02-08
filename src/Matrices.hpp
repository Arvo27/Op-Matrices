#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <iostream>
#define MAX_DIM 100

class Matrix {
    //Friend functions
    friend Matrix operator*(double scalar, const Matrix &m);
    friend std::istream& operator>>(std::istream& in, Matrix& m);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);


public:
    // Constructors and Destructor
    explicit Matrix(int r = 1, int c = 1); // Constructor by default of two parameters
    Matrix(const Matrix& m); // Constructor by copy
    ~Matrix();


    //Gets functions
    int getRows(); // Get Dimensions
    int getColumns();
    double getElement(int r, int c) const;


    //Sets functions
    void setElement(int r, int c, double value);


    //Matrix Manipulation
    void capture();
    void resize(int newRows, int newColumns);

    //Matrix operations
    Matrix sumMatrix(const Matrix& m) const; // Sum of two matrices
    Matrix subMatrix(const Matrix& m) const; // the subtraction of two matrices
    Matrix mulMatrix(const Matrix& m) const; // Product of two matrices
    Matrix operator*(double scalar) const; // Product to scalar

    
    //Methods of matrix
    Matrix transpose() const; //The transpose of a matrix
    Matrix inverse() const; // the inverse of a matrix

    //Overloads
    Matrix& operator=(const Matrix& m);
    double* operator[](int i);
    const double* operator[](int i) const;
    Matrix operator-(const Matrix &m) const;
    Matrix operator*(const Matrix &m) const;
    Matrix operator+(const Matrix &m) const;

private:
    //Set Dimensions of matrix
    void setDim(int r, int c);
    // Copy from other matrix
    void copyFrom(const Matrix& m);

    double** mat;
    int rows;
    int columns;
};

#endif