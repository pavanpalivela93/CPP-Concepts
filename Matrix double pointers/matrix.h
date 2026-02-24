#include <initializer_list>
class Matrix
{
private:
    int row;
    int col;
    int **data;

public:
    Matrix(int row, int col);
    Matrix(std::initializer_list<std::initializer_list<int>> init);
    ~Matrix();
    Matrix(const Matrix &other);
    Matrix &operator=(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    Matrix &operator=(Matrix &&other) noexcept;
    void print() const;
};