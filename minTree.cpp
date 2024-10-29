vector<int> build(vector<int>& v) {
    int n = v.size();
    vector<int> tree(4 * n);
    function<void(int, int, int)> buildTree = [&](int node, int start, int end) {
        if (start == end) {
            tree[node] = v[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(2 * node, start, mid);
            buildTree(2 * node + 1, mid + 1, end);
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    };
    buildTree(1, 0, n - 1);
    return tree;
}

void update(vector<int>& tree, vector<int>& v, int idx, int val) {
    int n = v.size();
    int node = 1, start = 0, end = n - 1;
    while (start != end) {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            node = 2 * node;
            end = mid;
        } else {
            node = 2 * node + 1;
            start = mid + 1;
        }
    }
    v[idx] = val;
    tree[node] = val;
    while (node > 1) {
        node /= 2;
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
}

int query(vector<int>& tree, int L, int R) {
    int n = tree.size() / 4;
    function<int(int, int, int, int, int)> queryTreeHelper = [&](int node, int start, int end, int L, int R) {
        if (R < start || end < L) {
            return INT_MAX;
        }
        if (L <= start && end <= R) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left_query = queryTreeHelper(2 * node, start, mid, L, R);
        int right_query = queryTreeHelper(2 * node + 1, mid + 1, end, L, R);
        return min(left_query, right_query);
    };
    return queryTreeHelper(1, 0, n - 1, L, R);
}

void solve() {
    vector<int> v = {3242, 545, 1231, 345345, 45344, 54, 45452, 3423};
    vector<int> tree = build(v);

    cout << "Min in range [1, 4]: " << query(tree, 1, 4) << endl;

    update(tree, v, 3, 43);

    cout << "Min in range [1, 4] after update: " << query(tree, 1, 4) << endl;
}
