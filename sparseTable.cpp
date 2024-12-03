template<typename T>
class SparseTable {
private:
    vector<vector<T>> table;
    int n;
    int logN;
    function<T(T, T)> op;  
    T identity;  

public:

    SparseTable(const vector<T>& arr, function<T(T, T)> operation, T identityElement) {
        n = arr.size();
        op = operation;
        identity = identityElement;

        logN = log2(n) + 1;

        table.resize(n, vector<T>(logN));

        for (int i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }

        for (int j = 1; j < logN; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                table[i][j] = op(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r) {
        if (l > r) {
            return identity;  
        }

        int length = r - l + 1;
        int k = log2(length);  

        return op(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);

    vector<int> arr = {1, 3, 2, 7, 9, 11, 5, 4};
    SparseTable<int> sparseTableMin(arr, [](int a, int b) { return min(a, b); }, INT_MAX);

    cout << "Min of range [1, 4]: " << sparseTableMin.query(1, 4) << endl;  
    cout << "Min of range [3, 7]: " << sparseTableMin.query(3, 7) << endl;  

    SparseTable<int> sparseTableMax(arr, [](int a, int b) { return max(a, b); }, INT_MIN);

    cout << "Max of range [1, 4]: " << sparseTableMax.query(1, 4) << endl;  
    cout << "Max of range [3, 7]: " << sparseTableMax.query(3, 7) << endl;  

    vector<int> arrGCD = {12, 15, 18, 30, 24, 36, 48};
    SparseTable<int> sparseTableGCD(arrGCD, [](int a, int b) { return gcd(a, b); }, 0);

    cout << "GCD of range [1, 4]: " << sparseTableGCD.query(1, 4) << endl;  
    cout << "GCD of range [3, 6]: " << sparseTableGCD.query(3, 6) << endl;  

}
