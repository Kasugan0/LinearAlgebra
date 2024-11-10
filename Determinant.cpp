#include <iostream>
#include <algorithm>
#include <vector>



using namespace std;



struct Determinant
{
    static constexpr double PRECISION = 1e-8; // The precision of computing.

    vector<vector<double>> data;
    double coef;


    // Init first-order determinant with element 0 by default.
    Determinant() : data(1, std::vector<double>(1, 0)), coef(1) {}

    // Init n-order determinant with element 0 by default.
    Determinant(size_t n) : data(n, std::vector<double>(n, 0)), coef(1) {}

    // Init using existing data.
    Determinant(const std::vector<std::vector<double>>& other) : data(other), coef(1) {}

    // Init using existing ptr to another instance of Determinant.
    Determinant(const Determinant* ptr) : data(ptr -> data), coef(ptr -> coef) {}

    // Init using existing another instance of Determinant.
    Determinant(const Determinant& other) : data(other.data), coef(other.coef) {}

    // Use the default dtor.
    ~Determinant() = default;

    // Return to the x row. We count from 0, which is not common in math.
    vector<double>& operator[](unsigned int x)
    {
        return data[x];
    }

    // Using const reference to copy.
    void operator=(const Determinant& d)
    {
        data = d.data;
        coef = d.coef;
    }

    // Return the order of the determinant.
    size_t getOrd() const
    {
        return data.size();
    }

    // Modify the determinant with inputed ilen, jlen and the whole data block.
    void input()
    {
        coef = 1;
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
    void rowSwp(size_t a, size_t b)
    {
        coef = -coef;
        swap(data[a], data[b]);
    }

    // Swap two cols.
    void colSwp(size_t a, size_t b)
    {
        coef = -coef;
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
        for (size_t j = 0, n = getOrd(); j < n; j++) data[r][j] += k * data[a][j];
    }

    // Let c Col plus k times a Col. (i.e. c += k * a)
    void colMutiAndAdd(size_t c, double k, size_t a)
    {
        for (auto& i : data) i[c] += k * i[a];
    }

    // Return true if this is a Upper Triangular Determinant.
    bool isUpTri()
    {
        for (const auto& i : data)
            for (const auto& j : i)
                if (j > PRECISION) return false;
        return true;
    }

    // Transform the determinant to the Upper Triangular form.
    void toUpTri()
    {
        for (size_t i = 0, n = getOrd(); i < n; i++)
        {
            double base = data[i][i];
            if (abs(base) < PRECISION)
            {
                bool swp = false;
                for (size_t k = i + 1; k < n; k++) // Attemping to swap row in order to make sure data[i][i] != 0.
                    if (abs(data[k][i]) > PRECISION)
                    {
                        rowSwp(i, k);
                        base = data[i][i], swp = true; // Update base right now.
                        break;
                    }
                if (!swp)
                {
                    coef = 0; // Can not find none-zero element.
                    continue; // Skip, not terminate.
                }
            }
            coef *= base;
            if (abs(base - 1) > PRECISION) // Avoid Standardize when the first non-zero element in each row is 1.
                for (auto& j : data[i]) j /= base; // Standardize the i Row.
            for (size_t k = i + 1; k < n; k++) rowMutiAndAdd(k, -data[k][i], i);
        }
    }

    // Calc the value of the determinant.
    double calcVal()
    {
        Determinant t(this);
        for (size_t i = 0, n = t.getOrd(); i < n; i++)
        {
            double base = t[i][i];
            if (abs(base) < PRECISION)
            {
                bool swp = false;
                for (size_t k = i + 1; k < n; k++) // Attemping to swap row in order to make sure data[i][i] != 0.
                    if (abs(t[k][i]) > PRECISION)
                    {
                        t.rowSwp(i, k);
                        base = t[i][i], swp = true; // Update base right now.
                        break;
                    }
                if (!swp) return 0;
            }
            t.coef *= base;
            if (abs(base - 1) > PRECISION) // Avoid Standardize when the first non-zero element in each row is 1.
                for (auto& j : t[i]) j /= base; // Standardize the i Row.
            for (size_t k = i + 1; k < n; k++) t.rowMutiAndAdd(k, -t[k][i], i);
        }
        return t.coef;
    }

    // Return to the the (r, c) minor.
    Determinant getMnr(size_t r, size_t c)
    {
        Determinant ans(getOrd() - 1);
        auto newBg = ans.data.begin(), oriBg = data.begin(), oriEd = data.end();
        copy(oriBg, oriBg + r, newBg), copy(oriBg + r + 1, oriEd, newBg + r);
        for (auto& i : ans.data) i.erase(i.begin() + c);
        return ans;
    }

    // Return to the ptr of the (r, c) minor, which is more recommended than getMnr().
    Determinant* getMnrPtr(size_t r, size_t c)
    {
        Determinant* ans = new Determinant(getOrd() - 1);
        auto newBg = ans -> data.begin(), oriBg = data.begin(), oriEd = data.end();
        copy(oriBg, oriBg + r, newBg), copy(oriBg + r + 1, oriEd, newBg + r);
        for (auto& i : ans -> data) i.erase(i.begin() + c);
        return ans;
    }

    // Return to the (r, c) algebraic minor.
    double calcAlgMnr(size_t r, size_t c)
    {
        Determinant* mnr = getMnrPtr(c, r);
        mnr -> toUpTri();
        return mnr -> coef;
    }
};



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}