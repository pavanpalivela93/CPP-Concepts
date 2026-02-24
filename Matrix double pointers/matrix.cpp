#include "matrix.h"
#include <iostream>
Matrix::Matrix(int row, int col) : row(row), col(col)
{
    data = new int *[row];
    for (int i = 0; i < row; i++)
    {
        data[i] = new int[col];
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            data[i][j] = i * j;
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < row; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

Matrix::Matrix(const Matrix &other)
{
    row = other.row;
    col = other.col;
    data = new int *[row];
    for (int i = 0; i < row; i++)
    {
        data[i] = new int[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this == &other)
    {
        return *this;
    }

    for (int i = 0; i < row; i++)
    {
        delete[] data[i];
    }
    delete[] data;
    row = other.row;
    col = other.col;
    data = new int *[row];
    for (int i = 0; i < row; i++)
    {
        data[i] = new int[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            data[i][j] = other.data[i][j];
        }
    }
    return *this;
}

Matrix::Matrix(Matrix &&other) noexcept : row(other.row), col(other.col), data(std::move(other.data))
{

    other.data = nullptr;
    other.row = 0;
    other.col = 0;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept
{
    for (int i = 0; i < row; i++)
    {
        delete[] data[i];
    }
    delete[] data;

    data = std::move(other.data);
    row = other.row;
    col = other.col;
    other.data = nullptr;
    other.row = 0;
    other.col = 0;
    return *this;
}

void Matrix::print() const
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> init)
{
    int rows = init.size();
    int cols = init.begin()->size();
    row = rows;
    col = cols;
    data = new int *[rows];
    int r = 0;
    for (const auto &x : init)
    {
        int j = 0;
        data[r] = new int[cols];
        for (int c : x)
        {
            data[r][j] = c;
            j++;
        }
        r++;
    }
}
