#include "Matrices.hpp"
#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::sqrt;
//a
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

//Get dimension
int Matrix::getRows()
{
    return rows;
}
int Matrix::getColumns()
{
    return columns;
}

//Set element
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

//Get element
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

//Capture entries
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
    try
    {
        setDim(newRows, newColumns);
        double **newMat = new double*[newRows];
        int minRows = (newRows < rows) ? newRows : rows;
        int minCols = (newColumns < columns) ? newColumns : columns;

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

//Overload >>
std::istream& operator>>(std::istream& in, Matrix& m)
{
    m.capture();
    return in;
}

//Overload <<
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

//Overload =
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

//Overload []
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
