#include <iostream>
#include <algorithm>
#include <vector>



using namespace std;



struct Determinant
{
    vector<vector<double>> data;
    double coefficient;


    // Init first-order determinant with element 0 by default.
    Determinant()
    {
        data.resize(1), data[0].resize(1);
        coefficient = 1;
    }

    // Init n-order determinant with element 0 by default.
    Determinant(size_t n)
    {
        data.resize(n);
        for (auto& i : data) i.resize(n);
        coefficient = 1;
    }

    // Init using existing data.
    Determinant(const vector<vector<double>>& d)
    {
        data = d;
        coefficient = 1;
    }

    // Return to the x row. We count from 0, which is not common in math.
    vector<double>& operator[](unsigned int x)
    {
        return data[x];
    }

    // Using const reference to copy.
    void operator=(const Determinant& d)
    {
        data = d.data;
        coefficient = d.coefficient;
    }

    // Return the order of the determinant.
    size_t getOrder() const
    {
        return data.size();
    }

    // Modify the determinant with inputed ilen, jlen and the whole data block.
    void input()
    {
        size_t n;
        cin >> n;
        data.resize(n);
        for (auto& i : data)
        {
            i.resize(n); // Allocate enough memory only once for each row, avoiding allocating at insert each element, to get the best performance.
            for (auto& j : i) cin >> j;
        }
    }

    // Print the determinant.
    void print() const
    {
        for (const auto& i : data)
        {
            for (const auto& j : i) cout << j << ' ';
            cout << endl;
        }
    }

    // Swap two rows.
    void rowSwap(size_t a, size_t b)
    {
        coefficient = -coefficient;
        swap(data[a], data[b]);
    }

    // Swap two cols.
    void colSwap(size_t a, size_t b)
    {
        coefficient = -coefficient;
        for (auto& i : data) swap(i[a], i[b]);
    }

    // Let r Row multiply by k. (i.e. r *= k)
    void rowMutiByNum(size_t r, double k)
    {
        for (auto& j : data[r]) j *= k;
    }

    // Let c Col multiply by k. (i.e. c *= k)
    void colMutiByNum(size_t c, double k)
    {
        for (auto& i : data) i[c] *= k;
    }

    // Let r Row plus k times a Row. (i.e. r += k * a)
    void rowMutiAndAdd(size_t r, double k, size_t a)
    {
        for (auto i = data[r].begin(), j = data[a].begin(); i != data[r].end(); i++, j++) *i += k * (*j);
    }

    // Let c Col plus k times a Col. (i.e. c += k * a)
    void colMutiAndAdd(size_t c, double k, size_t a)
    {
        for (auto& i : data) i[c] += k * i[a];
    }

    // Return true if this is a Upper Triangular Determinant.
    bool isUpperTriangular()
    {
        size_t n = getOrder();
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < i; j++)
                if (abs(data[i][j]) > 1e-8) return false;
        return true;
    }
};



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}