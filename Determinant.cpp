#include <iostream>
#include <algorithm>
#include <vector>



using namespace std;



struct Determinant
{
    vector<vector<double>> data;
    bool minus;

    Determinant()
    {
        data.resize(1), data[0].resize(1);
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

    // Return the size of each row.
    size_t getRowLen() const
    {
        return data.size();
    }

    // Return the size of each column.
    size_t getColLen() const
    {
        return data[0].size();
    }

    // Modify the determinant with inputed ilen, jlen and the whole data block.
    void input()
    {
        size_t ilen, jlen;
        cin >> ilen >> jlen;
        data.resize(ilen);
        for (auto& i : data)
        {
            i.resize(ilen); // Allocate enough memory only once for each row, avoiding allocating at insert each element, to get the best performance.
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
};



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}