#include <iostream>
#include <algorithm>
#include <vector>



using namespace std;



struct Determinant
{
    vector<vector<double>> data;
    bool minus;

    // Init first-order determinant with element 0 by default.
    Determinant()
    {
        data.resize(1), data[0].resize(1);
        minus = false;
    }

    // Init n-order determinant with element 0 by default.
    Determinant(size_t n)
    {
        data.resize(n);
        for (auto& i : data) i.resize(n);
        minus = false;
    }

    // Init using existing data.
    Determinant(const vector<vector<double>>& d)
    {
        data = d;
        minus = false;
    }

    // Return to the x row. We count from 0, which is not common in math.
    vector<double> operator[](unsigned int x)
    {
        return data[x];
    }

    // Using const reference to copy.
    void operator=(Determinant& d)
    {
        data = d.data;
        minus = d.minus;
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
        minus = !minus;
        swap(data[a], data[b]);
    }

    // Swap two cols.
    void colSwap(size_t a, size_t b)
    {
        minus = !minus;
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
};



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}