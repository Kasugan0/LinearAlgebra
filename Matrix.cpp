#include <iostream>
#include <algorithm>
#include <vector>



using namespace std;



struct Matrix
{
    static constexpr double PRECISION = 1e-8; // The precision of computing.

    vector<vector<double>> data;


    // Init 1x1 Matrix with element 0 by default.
    Matrix() : data(1, std::vector<double>(1, 0)) {}

    // Init c-by-r Matrix with element 0 by default.
    Matrix(size_t c, size_t r) : data(c, std::vector<double>(r, 0)) {}

    // Init using existing data.
    Matrix(const std::vector<std::vector<double>>& other) : data(other) {}

    // Init using existing ptr to another instance of Matrix.
    Matrix(const Matrix* ptr) : data(ptr -> data) {}

    // Init using existing another instance of Matrix.
    Matrix(const Matrix& other) : data(other.data) {}

    // Use the default dtor.
    ~Matrix() = default;

    // Return to the n-by-n Identity Matrix.
    static Matrix newIdMtrx(size_t n)
    {
        Matrix ans(n, n);
        for (size_t i = 0; i < n; i++) ans[i][i] = 1;
        return ans;
    }

    // Return to the ptr of n-by-n Identity Matrix.
    static Matrix newIdMtrxPtr(size_t n)
    {
        Matrix* ans = new Matrix(n, n);
        for (size_t i = 0; i < n; i++) ans -> data[i][i] = 1;
        return ans;
    }

    // Return to the x row. We count from 0, which is not common in math.
    vector<double>& operator[](size_t x)
    {
        return data[x];
    }

    // Return to the sum of this add another Matrix.
    Matrix operator+(Matrix& other)
    {
        size_t ilen = getRowCnt(), jlen = getColCnt();
        if (ilen != other.getRowCnt() || jlen != other.getColCnt())
            throw std::runtime_error("The two Matrix being added are not of the same type.");
        Matrix ans(ilen, jlen);
        for (size_t i = 0; i < ilen; i++)
            for (size_t j = 0; j < jlen; j++)
                ans[i][j] = data[i][j] + other[i][j];
        return ans;
    }

    // Return to the diff of this subtract another Matrix.
    Matrix operator-(Matrix& other)
    {
        size_t ilen = getRowCnt(), jlen = getColCnt();
        if (ilen != other.getRowCnt() || jlen != other.getColCnt())
            throw std::runtime_error("The two Matrix being subtracted are not of the same type.");
        Matrix ans(ilen, jlen);
        for (size_t i = 0; i < ilen; i++)
            for (size_t j = 0; j < jlen; j++)
                ans[i][j] = data[i][j] - other[i][j];
        return ans;
    }

    // Using const reference to copy.
    void operator=(const Matrix& m)
    {
        data = m.data;
    }

    // Return the number of rows of the Matrix.
    size_t getRowCnt() const
    {
        return data.size();
    }

    // Return to the number of cols of the Matrix.
    size_t getColCnt() const
    {
        return data[0].size();
    }

    // Modify the Matrix with inputed ilen, jlen and the whole data block.
    void input()
    {
        size_t ilen, jlen;
        cin >> ilen >> jlen;
        data.resize(ilen);
        for (auto& i : data)
        {
            i.resize(jlen); // Allocate enough memory only once for each row, avoiding allocating at insert each element, to get the best performance.
            for (auto& j : i) cin >> j;
        }
    }

    // Print the Matrix.
    void print() const
    {
        for (const auto& i : data)
        {
            for (const auto& j : i) cout << j << ' ';
            cout << endl;
        }
    }
};



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}