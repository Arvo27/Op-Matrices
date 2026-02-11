#include "Matrices.hpp"
#include <iostream>
#include <cmath>

using std::cout;
using std::cin;

// =======================================================================
/**
 * \brief Principal constructor that creates a matrix with specific dimensions.
 *
 * \param r Number of rows for the new matrix.
 * \param c Number of columns for the new matrix.
 *
 * \pre r > 0 and c > 0.
 * \warning If r or c are <= 0, validation is handled by setDim.
 * \throw const char* If dimensions are invalid or memory allocation fails.
 */
// Constructor and Destructor
Matrix::Matrix(int r, int c)
{
    setDim(r, c);
    mat = new double*[rows];
    for (int i = 0; i < rows; ++i)
    {
        mat[i] = new double[columns];
        for (int j = 0; j < columns; ++j)
        {
            mat[i][j] = 0.0;
        }
    }
}

/**
 * \brief Copy constructor that creates an exact replica of another matrix.
 *
 * \param m Original matrix to be duplicated.
 *
 * \pre Matrix m must be initialized and valid.
 * \warning Performs a deep copy; both matrices remain independent.
 * \throw std::bad_alloc If there is insufficient memory for the copy.
 */
Matrix::Matrix(const Matrix& m)
{
    copyFrom(m);
}

/**
 * \brief Destructor that releases all dynamic memory allocated for the matrix.
 *
 * \warning Must be used correctly to avoid memory leaks.
 * \post All dynamic memory pointers are deleted and cleared.
 */
Matrix::~Matrix()
{
    freeMem();
}

// =======================================================================
// Sets functions

/**
 * \brief Sets the value of a specific element in the matrix.
 *
 * \param r Row index of the element (0-based).
 * \param c Column index of the element (0-based).
 * \param value Numerical value to be assigned to the element.
 *
 * \pre Indices r and c must be within the matrix bounds.
 * \warning If indices are out of range, an exception is thrown.
 * \throw const char* Thrown if r or c are outside valid limits.
 */
void Matrix::setElement(int r, int c, double value)
{
    if (r < 0 || c < 0 || r >= rows || c >= columns)
    {
        throw "Index out of bounds.";
    }
    else
    {
        mat[r][c] = value;
    }
}

// =======================================================================
// Get functions

/**
 * \brief Returns the number of rows in the matrix.
 *
 * \return Integer representing the amount of rows in the matrix.
 */
int Matrix::getRows()
{
    return rows;
}

/**
 * \brief Returns the number of columns in the matrix.
 *
 * \return Integer representing the amount of columns in the matrix.
 */
int Matrix::getColumns()
{
    return columns;
}

/**
 * \brief Gets the value of a specific element from the matrix.
 *
 * \param r Row index of the desired element (0-based).
 * \param c Column index of the desired element (0-based).
 *
 * \return Double value stored at position (r, c).
 *
 * \pre Indices r and c must be within the matrix bounds.
 * \throw const char* Thrown if r or c are outside valid limits.
 */
double Matrix::getElement(int r, int c) const
{
    if (r < 0 || c < 0 || r >= rows || c >= columns)
    {
        throw "Index out of bounds.";
    }
    else
    {
        return mat[r][c];
    }
}

// =======================================================================
// Matrix Manipulations

/**
 * \brief Captures matrix values from standard input.
 *
 * Prompts the user to enter values for each cell, displaying the
 * coordinates for each position to be filled.
 *
 * \warning Requires valid numeric user input.
 * \pre The matrix must have defined dimensions and allocated memory.
 */
void Matrix::capture()
{
    cout << "Enter matrix entries:\n";
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            cout << "mat[" << i << "][" << j << "] = ";
            cin >> mat[i][j];
        }
    }
}

/**
 * \brief Changes matrix dimensions while preserving compatible values.
 *
 * \param newRows New row count for the matrix.
 * \param newColumns New column count for the matrix.
 *
 * \pre newRows and newColumns must be between 1 and MAX_DIM.
 * \warning If dimensions are invalid, the error is caught and printed.
 * \throw const char* Thrown if dimensions are outside permitted limits.
 */
void Matrix::resize(int newRows, int newColumns)
{
    int oldRows = this->rows;
    int oldColumns = this->columns;
    try
    {
        if (newRows < 1 || newColumns < 1 || newRows > MAX_DIM || newColumns > MAX_DIM) {
            throw "Invalid dimensions for resize.";
        }

        double **newMat = new double*[newRows];
        int minRows = (newRows < oldRows) ? newRows : oldRows;
        int minCols = (newColumns < oldColumns) ? newColumns : oldColumns;

        for (int i = 0; i < newRows; ++i)
        {
            newMat[i] = new double[newColumns];
            for (int j = 0; j < newColumns; ++j)
            {
                if (i < minRows && j < minCols)
                {
                    newMat[i][j] = mat[i][j];
                }
                else
                {
                    newMat[i][j] = 0.0;
                }
            }
        }
        freeMem();
        mat = newMat;
        rows = newRows;
        columns = newColumns;
    }
    catch (const char* e)
    {
        cout << "Error: " << e << "\n";
    }
}

// =======================================================================
// Overloads

/**
 * \brief Overloads the >> operator to read a matrix from an input stream.
 *
 * \param in Input stream to read from.
 * \param m Matrix where data will be stored.
 *
 * \return Reference to the input stream to allow chaining.
 *
 * \pre Matrix m must have dimensions defined previously.
 * \warning Delegates to the capture() method for the actual data reading.
 */
std::istream& operator>>(std::istream& in, Matrix& m)
{
    m.capture();
    return in;
}

/**
 * \brief Overloads the << operator to print the matrix to an output stream.
 *
 * \param out Output stream where the matrix will be printed.
 * \param m Matrix to be printed.
 *
 * \return Reference to the output stream to allow chaining.
 *
 * \pre Matrix m must be correctly initialized.
 * \warning Formats the matrix with brackets and line breaks.
 */
std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
    out << "[";
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.columns; ++j)
        {
            out << m.mat[i][j];
            if (j != m.columns - 1) out << " ";
        }
        if (i != m.rows - 1) out << "\n ";
    }
    out << "]";
    return out;
}

/**
 * \brief Overloads the assignment operator for deep copying.
 *
 * \param m Source matrix to be assigned to this matrix.
 *
 * \return Reference to this matrix after assignment.
 *
 * \pre Matrix m must be correctly initialized.
 * \warning Releases existing memory before copying new data.
 * \throw std::bad_alloc If memory allocation fails during copying.
 */
Matrix& Matrix::operator=(const Matrix& m)
{
    if(this != &m)
    {
        freeMem();
        copyFrom(m);
    }
    return *this;
}

/**
 * \brief Overloads the [] operator for read-only row access.
 *
 * This constant version is called when the Matrix object is immutable.
 * It provides the base logic for index validation to avoid code duplication.
 *
 * \param i Index of the row to access (0-based).
 * \return Constant pointer to the array representing row i.
 * \throw const char* Thrown if the row index is out of bounds.
 */
const double* Matrix::operator[](int i) const
{
    if (i < 0 || i >= rows) {
        throw "Index out of bounds.";
    }
    return mat[i];
}

/**
 * \brief Overloads the [] operator for row access with modification capability.
 *
 * This version optimizes performance and maintenance by calling the constant
 * version and casting the result, ensuring a single point of validation.
 *
 * \param i Index of the row to access (0-based).
 * \return Pointer to the array representing row i.
 * \throw const char* Thrown if the row index is out of bounds.
 */
double* Matrix::operator[](int i)
{
    // Calling the const version of operator[] and casting away constness
    return const_cast<double*>(static_cast<const Matrix*>(this)->operator[](i));
}

/**
 * \brief Overloads the + operator for matrix addition.
 *
 * \param m Matrix to be added to this matrix.
 *
 * \return New matrix representing the element-wise sum.
 *
 * \pre Both matrices must have identical dimensions.
 * \warning Delegates to sumMatrix() for the calculation.
 */
Matrix Matrix::operator+(const Matrix &m) const
{
    return this->sumMatrix(m);
}

/**
 * \brief Overloads the - operator for matrix subtraction.
 *
 * \param m Matrix to be subtracted from this matrix.
 *
 * \return New matrix representing the element-wise difference.
 *
 * \pre Both matrices must have identical dimensions.
 * \warning Delegates to subMatrix() for the calculation.
 */
Matrix Matrix::operator-(const Matrix &m) const
{
    return this->subMatrix(m);
}

/**
 * \brief Overloads the * operator for matrix multiplication.
 *
 * \param m Matrix to multiply on the right.
 *
 * \return New matrix representing the matrix product.
 *
 * \pre Dimensions must be compatible for multiplication.
 * \warning Delegates to mulMatrix() for the calculation.
 */
Matrix Matrix::operator*(const Matrix &m) const
{
    return this->mulMatrix(m);
}

// =======================================================================
// Private helper function to copy matrix data

/**
 * \brief Copies data and dimensions from another matrix to this one.
 *
 * \param m Source matrix to copy from.
 *
 * \pre Matrix m must be correctly initialized.
 * \warning Performs a deep copy, allocating new memory.
 * \throw std::bad_alloc If memory allocation fails during copying.
 */
void Matrix::copyFrom(const Matrix& m)
{
    setDim(m.rows, m.columns);
    mat = new double*[rows];
    for (int i = 0; i < rows; ++i)
    {
        mat[i] = new double[columns];
        for (int j = 0; j < columns; ++j)
        {
            mat[i][j] = m.mat[i][j];
        }
    }
}

/**
 * \brief Sets internal matrix dimensions with validation.
 *
 * \param r Number of rows for the matrix.
 * \param c Number of columns for the matrix.
 *
 * \pre Values must be between 1 and MAX_DIM.
 * \warning Only sets dimension values; does not allocate memory.
 * \throw const char* Thrown if dimensions are outside permitted range.
 */
void Matrix::setDim(int r, int c)
{
    if (r < 1 || c < 1 || r > MAX_DIM || c > MAX_DIM)
    {
        throw "Invalid matrix dimensions.";
    }
    else
    {
        rows = r;
        columns = c;
    }
}

/**
 * \brief Helper function to free all dynamic memory allocated for the matrix.
 *
 * \post Pointers are deleted and set to nullptr to avoid dangling pointers.
 */
void Matrix::freeMem()
{
    if (mat != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] mat[i];
        }
        delete[] mat;
        mat = nullptr;
    }
}

// =======================================================================
// Matrix Operations

/**
 * \brief Adds this matrix element-wise to another matrix.
 *
 * \param m Matrix to be added.
 *
 * \return New matrix with the element-wise sum results.
 *
 * \pre Both matrices must have the same dimensions.
 * \throw const char* Thrown if dimensions do not match.
 */
Matrix Matrix::sumMatrix(const Matrix &m) const
{
    if(this->rows != m.rows || this->columns != m.columns)
    {
        throw "Matrix dimensions do not match for addition.";
    }
    Matrix result(this->rows, this->columns);
    for(int i = 0 ; i < this->rows; ++i)
    {
        for(int j = 0; j < this->columns; ++j)
        {
            result.mat[i][j] = this->mat[i][j] + m.mat[i][j];
        }
    }
    return result;
}

/**
 * \brief Subtracts another matrix element-wise from this matrix.
 *
 * \param m Matrix to be subtracted.
 *
 * \return New matrix with the element-wise subtraction results.
 *
 * \pre Both matrices must have the same dimensions.
 * \throw const char* Thrown if dimensions do not match.
 */
Matrix Matrix::subMatrix(const Matrix &m) const
{
    if(this->rows != m.rows || this->columns != m.columns)
    {
        throw "Matrix dimensions do not match for subtraction.";
    }

    Matrix result(this->rows, this->columns);
    for(int i = 0; i < this->rows; ++i)
    {
        for(int j = 0; j < this->columns; ++j)
        {
            result.mat[i][j] = this->mat[i][j] - m.mat[i][j];
        }
    }
    return result;
}

/**
 * \brief Performs matrix multiplication between this matrix and another.
 *
 * \param m Matrix to multiply on the right.
 *
 * \return New matrix resulting from the matrix product.
 *
 * \pre Column count of this matrix must match the row count of matrix m.
 * \throw const char* Thrown if dimensions are incompatible.
 */
Matrix Matrix::mulMatrix(const Matrix &m) const
{
    if(this->columns != m.rows)
    {
        throw "Matrix dimensions do not match for multiplication.";
    }

    Matrix result(this->rows, m.columns);
    for(int i = 0; i < this->rows; ++i)
    {
        for(int j = 0; j < m.columns; ++j)
        {
            result.mat[i][j] = 0;
            for(int k = 0; k < this->columns; ++k)
            {
                result.mat[i][j] += this->mat[i][k] * m.mat[k][j];
            }
        }
    }
    return result;
}

/**
 * \brief Multiplies every element in the matrix by a scalar value.
 *
 * \param scalar Numeric value to multiply each element by.
 *
 * \return New matrix with all elements multiplied by the scalar.
 *
 * \warning Does not modify the original matrix; creates a new one.
 */
Matrix Matrix::operator*(double scalar) const
{
    Matrix result(rows, columns);
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            result.mat[i][j] = mat[i][j] * scalar;
        }
    }
    return result;
}

/**
 * \brief Overloads the * operator for left-side scalar multiplication.
 *
 * \param scalar Numeric value to multiply.
 * \param m Matrix to be multiplied.
 *
 * \return New matrix with all elements multiplied by the scalar.
 */
Matrix operator*(double scalar, const Matrix &m) {
    return m * scalar;
}

// ==============================================================================
// Methods of Matrix

/**
 * \brief Calculates the transpose matrix by swapping rows and columns.
 *
 * \return New matrix that is the transpose of the current matrix.
 *
 * \warning Resulting matrix will have inverted dimensions (columns x rows).
 */
Matrix Matrix::transpose() const
{
    Matrix result(this->columns, this->rows);
    for(int i = 0; i < this->rows; ++i)
    {
        for(int j = 0; j < this->columns; ++j)
        {
            result.mat[j][i] = this->mat[i][j];
        }
    }
    return result;
}

/**
 * \brief Calculates the inverse matrix using Gaussian elimination.
 *
 * \return New matrix that is the inverse of the current matrix.
 *
 * \pre Matrix must be square (rows == columns).
 * \warning Calculation may be inaccurate for ill-conditioned matrices.
 * \throw const char* Thrown if matrix is not square or is singular.
 */
Matrix Matrix::inverse() const
{
    if(rows != columns) {
         throw "Matrix must be square.";
    }

    Matrix res(rows, columns);
    Matrix temp(*this);
    for(int i = 0; i < rows; ++i) {
        res.mat[i][i] = 1.0;
    }

    for(int i = 0; i < rows; ++i) {
        // Pivoting/Normalization
        double pivot = temp.mat[i][i];
        if (std::abs(pivot) < 1e-12) {
            throw "Matrix is singular.";
        }

        for(int j = 0; j < rows; ++j) {
            temp.mat[i][j] /= pivot;
            res.mat[i][j] /= pivot;
        }

        for(int j = 0; j < rows; ++j) {
            if(i != j) {
                double factor = temp.mat[j][i];
                for(int k = 0; k < rows; ++k) {
                    temp.mat[j][k] -= factor * temp.mat[i][k];
                    res.mat[j][k] -= factor * res.mat[i][k];
                }
            }
        }
    }
    return res;
}
