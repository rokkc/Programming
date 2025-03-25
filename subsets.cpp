vector<vector<int>> subsets(vector<int> &v) {
    vector<vector<int>> res;
    for (int i = 0; i < (1 << v.size()); i++) {
        vector<int> cur;
        for (int j = 0; j < v.size(); j++) {
            if (i & (1 << j)) {
                cur.push_back(v[j]);
            }
        }
        res.push_back(cur);
    }
    return res;
}
