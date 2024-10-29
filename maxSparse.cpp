void precomputeLog(int n, vector<int>& logValues) {
    logValues.resize(n + 1);
    logValues[1] = 0;
    for (int i = 2; i <= n; i++) {
        logValues[i] = logValues[i / 2] + 1;
    }
}

void buildSparseTable(const vector<int>& arr, vector<vector<int>>& table, const vector<int>& logValues) {
    int n = arr.size();
    int maxLog = log2(n) + 1;
    table.resize(n, vector<int>(maxLog));
    for (int i = 0; i < n; i++) {
        table[i][0] = arr[i];
    }
    for (int j = 1; j < maxLog; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            table[i][j] = max(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int L, int R, const vector<vector<int>>& table, const vector<int>& logValues) {
    int j = logValues[R - L + 1];
    return max(table[L][j], table[R - (1 << j) + 1][j]);
}


void solve() {
    vector<int> arr = {1, 3, 2, 7, 9, 11, 3, 5, 6, 8};
    vector<int> logValues;
    vector<vector<int>> table;

    precomputeLog(arr.size(), logValues);
    buildSparseTable(arr, table, logValues);

    cout << "Maximum value in range [0, 5]: " << query(0, 5, table, logValues) << endl;
    cout << "Maximum value in range [3, 8]: " << query(3, 8, table, logValues) << endl;
    cout << "Maximum value in range [1, 6]: " << query(1, 6, table, logValues) << endl;
}
