#ifndef MATRICES_HPP_INCLUDED
#define MATRICES_HPP_INCLUDED

#include <iostream>

/** * \def MAX_DIM 
 * \brief Maximum allowed dimension for rows or columns to prevent excessive memory allocation.
 */
#define MAX_DIM 100

/**
 * \class Matrix
 * \brief Implements matrix operations using dynamic memory allocation.
 *
 * This class provides a robust interface for creating, manipulating, and performing 
 * algebraic operations with matrices of variable dimensions. It handles deep copying,
 * operator overloading, and common linear algebra algorithms.
 */
class Matrix {
    /**
     * \brief Commutative scalar multiplication (scalar * Matrix).
     * \param scalar The real number to multiply.
     * \param m The Matrix object.
     * \return A new Matrix where each element is multiplied by the scalar.
     */
    friend Matrix operator*(double scalar, const Matrix &m);

    /**
     * \brief Overloads the extraction operator for matrix input.
     * \param in Input stream.
     * \param m Matrix object to store the captured data.
     * \return Reference to the input stream.
     */
    friend std::istream& operator>>(std::istream& in, Matrix& m);

    /**
     * \brief Overloads the insertion operator for matrix output.
     * \param out Output stream.
     * \param m Matrix object to be printed.
     * \return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

public:
    // =======================================================================
    // Constructors and Destructor
    
    /**
     * \brief Default and parameterized constructor.
     * \param r Number of rows (defaults to 1).
     * \param c Number of columns (defaults to 1).
     */
    explicit Matrix(int r = 1, int c = 1);

    /**
     * \brief Copy constructor for deep copying.
     * \param m The source matrix to copy from.
     */
    Matrix(const Matrix& m);

    /**
     * \brief Destructor to free dynamically allocated memory.
     */
    ~Matrix();

    // =======================================================================
    // Getter Functions

    /** \brief Returns the number of rows in the matrix. */
    int getRows(); 

    /** \brief Returns the number of columns in the matrix. */
    int getColumns();

    /** * \brief Returns the value of a specific element.
     * \param r Row index.
     * \param c Column index.
     * \return The double value at the specified position.
     * \throw const char* if indices are out of bounds.
     */
    double getElement(int r, int c) const;

    // =======================================================================
    // Setter Functions

    /** * \brief Sets the value of a specific element.
     * \param r Row index.
     * \param c Column index.
     * \param value The new value to assign.
     * \throw const char* if indices are out of bounds.
     */
    void setElement(int r, int c, double value);

    // =======================================================================
    // Matrix Manipulation

    /** \brief Prompts the user to enter each matrix entry via standard input. */
    void capture();

    /** * \brief Resizes the matrix while preserving compatible data.
     * \param newRows New row count.
     * \param newColumns New column count.
     * \note Truncates data if dimensions decrease; fills with 0.0 if they increase.
     */
    void resize(int newRows, int newColumns);

    // =======================================================================
    // Matrix Arithmetic Operations

    /** \brief Calculates the sum of two matrices of the same dimensions. */
    Matrix sumMatrix(const Matrix& m) const;

    /** \brief Calculates the difference between two matrices. */
    Matrix subMatrix(const Matrix& m) const;

    /** \brief Performs standard matrix multiplication (dot product). */
    Matrix mulMatrix(const Matrix& m) const;

    /** \brief Multiplies each element of the matrix by a scalar value. */
    Matrix operator*(double scalar) const;

    // =======================================================================
    // Linear Algebra Methods

    /** \brief Returns the transpose of the matrix (rows become columns). */
    Matrix transpose() const;

    /** * \brief Calculates the inverse of a square matrix using Gauss-Jordan elimination.
     * \throw const char* if the matrix is not square or is singular (non-invertible).
     */
    Matrix inverse() const;

    // =======================================================================
    // Operator Overloads

    /** \brief Assignment operator to ensure deep copying of resources. */
    Matrix& operator=(const Matrix& m);

    /** \brief Accesses a specific row for indexed entry access (m[i][j]). */
    double* operator[](int i);

    /** \brief Constant version of row access for read-only operations. */
    const double* operator[](int i) const;

    /** \brief Overloads the '-' operator for matrix subtraction. */
    Matrix operator-(const Matrix &m) const;

    /** \brief Overloads the '*' operator for matrix multiplication. */
    Matrix operator*(const Matrix &m) const;

    /** \brief Overloads the '+' operator for matrix addition. */
    Matrix operator+(const Matrix &m) const;

private:
    /** * \brief Validates and sets internal dimensions.
     * \throw const char* if dimensions exceed MAX_DIM or are less than 1.
     */
    void setDim(int r, int c);

    /** \brief Frees dynamically allocated memory to prevent leaks. */
    void freeMem(); 

    /** \brief Internal helper to perform deep copy of matrix data. */
    void copyFrom(const Matrix& m);

    double** mat;   ///< Dynamic 2D array storing matrix elements.
    int rows;       ///< Number of rows.
    int columns;    ///< Number of columns.
};

#endif // MATRICES_HPP_INCLUDED