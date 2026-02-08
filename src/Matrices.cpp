#include "Matrices.hpp"
#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::sqrt;

// =======================================================================
// Constructor and Destructor
Matrix::Matrix(int r, int c)
{
    setDim(r, c);
    mat = new double*[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new double[columns];
        for (int j = 0; j < columns; j++)
        {
            mat[i][j] = 0.0;
        }
    }
}
Matrix::Matrix(const Matrix& m)
{
    copyFrom(m);
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
}

// =======================================================================
//Sets functions
void Matrix::setElement(int r, int c, double value) {
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
//Get dimension
int Matrix::getRows()
{
    return rows;
}
int Matrix::getColumns()
{
    return columns;
}

double Matrix::getElement(int r, int c) const {
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

        for (int i = 0; i < newRows; i++)
        {
            newMat[i] = new double[newColumns];
            for (int j = 0; j < newColumns; j++)
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
        for (int i = 0; i < rows; i++)
        {
            delete[] mat[i];
        }
        delete[] mat;
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
//Overloads
std::istream& operator>>(std::istream& in, Matrix& m)
{
    m.capture();
    return in;
}

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

Matrix& Matrix::operator=(const Matrix& m)
{
    if(this != &m)
    {
        // Free existing resources
        for (int i = 0; i < rows; i++)
        {
            delete[] mat[i];
        }
        delete[] mat;

        // Copy new data
        copyFrom(m);
    }
    return *this;
}
double* Matrix::operator[](int i)
{
    if (i < 0 || i >= rows){ 
        throw "Index out of bounds.";
    }
    return mat[i];
}
const double* Matrix::operator[](int i) const {
    if (i < 0 || i >= rows) {
        throw "Row index out of bounds.";
    }
    return mat[i];
}
Matrix Matrix::operator+(const Matrix &m) const {
    return this->sumMatrix(m);
}
Matrix Matrix::operator-(const Matrix &m) const {
    return this->subMatrix(m);
}
Matrix Matrix::operator*(const Matrix &m) const {
    return this->mulMatrix(m);
}

// =======================================================================
// Private helper function to copy matrix data

void Matrix::copyFrom(const Matrix& m)
{
    setDim(m.rows, m.columns);
    mat = new double*[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new double[columns];
        for (int j = 0; j < columns; j++)
        {
            mat[i][j] = m.mat[i][j];
        }
    }
}

//Set dimension
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


// =======================================================================
// Matrix Operations

Matrix Matrix::sumMatrix(const Matrix &m) const {
    if(this->rows != m.rows || this->columns != m.columns)
    {
        throw "Matrix dimensions do not match for addition.";
    }
    Matrix result(this->rows, this->columns);
    for(int i = 0 ; i < this->rows; i++)
    {
        for(int j = 0; j < this->columns; j++)
        {
            result.mat[i][j] = this->mat[i][j] + m.mat[i][j];
        }
    }
    return result;
}

Matrix Matrix::subMatrix(const Matrix &m) const{
    if(this->rows != m.rows || this->columns != m.columns)
    {
        throw "Matrix dimensions do not match for subtraction.";
    }

    Matrix result(this->rows, this->columns);
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->columns; j++)
        {
            result.mat[i][j] = this->mat[i][j] - m.mat[i][j];
        }
    }
    return result;
}

Matrix Matrix::mulMatrix(const Matrix &m) const{
    if(this->columns != m.rows)
    {
        throw "Matrix dimensions do not match for multiplication.";
    }

    Matrix result(this->rows, m.columns);
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < m.columns; j++)
        {
            result.mat[i][j] = 0;
            for(int k = 0; k < this->columns; k++)
            {
                result.mat[i][j] += this->mat[i][k] * m.mat[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, columns);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            result.mat[i][j] = mat[i][j] * scalar;
        }
    }
    return result;
}
Matrix operator*(double scalar, const Matrix &m) {
    return m * scalar; 
}

// ==============================================================================
// Methods of Matrix
Matrix Matrix::transpose() const{
    Matrix result(this->columns, this->rows);
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->columns; j++)
        {
            result.mat[j][i] = this->mat[i][j];
        }
    }
    return result;
}

Matrix Matrix::inverse() const {
    if(rows != columns)
    {
        throw "Matrix must be square to calculate inverse.";
    }
    Matrix result(rows, columns);
    //Crear una copia de la matriz para no destruir la original

    Matrix temp(*this);
    for(int i = 0; i < rows; i++)
    {
        //Hacer la matriz identidad
        result.mat[i][i] = 1.0;
        //Hacer ceros en la columna i
        for(int j = 0; j < rows; j++)
        {
            if(i != j)
            {
                if(temp.mat[i][i] == 0)
                {
                    throw "Matrix is singular and cannot be inverted.";
                }
                double factor = temp.mat[j][i] / temp.mat[i][i];
                for(int k = 0; k < rows; k++)
                {
                    temp.mat[j][k] -= factor * temp.mat[i][k];
                    result.mat[j][k] -= factor * result.mat[i][k];
                }
            }
        }
    }

    //Hacer unos en la diagonal
    for(int i = 0; i < rows; i++)
    {
        double divisor = temp.mat[i][i];
        for(int j = 0; j < rows; j++)
        {
            temp.mat[i][j] /= divisor;
            result.mat[i][j] /= divisor;
        }
    }
    return result;
}
