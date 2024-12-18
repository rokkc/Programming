vector<int> buildPrefixVector(vector<int>& v) {
    vector<int> prefs = {0};
    for (int i: v) {
        prefs.push_back(prefs.back() + i);
    }
    return prefs;
}

int prefQuery(vector<int> &prefs, int i, int j) {
    return prefs[j + 1] - prefs[i];
}

vector<vector<int>> build_2dprefix_sum(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> prefix_sum(rows + 1, vector<int>(cols + 1, 0));
    for (int i = 1; i <= rows; ++i) {
        for (int j = 1; j <= cols; ++j) {
            prefix_sum[i][j] = matrix[i-1][j-1] +
                               prefix_sum[i-1][j] +
                               prefix_sum[i][j-1] -
                               prefix_sum[i-1][j-1];
        }
    }
    return prefix_sum;
}

int query_submatrix(const vector<vector<int>>& prefix_sum, int row1, int col1, int row2, int col2) {
    return prefix_sum[row2+1][col2+1] -
           prefix_sum[row1][col2+1] -
           prefix_sum[row2+1][col1] +
           prefix_sum[row1][col1];
}
