vector<int> build_tree(const vector<int>& data) {
    int n = data.size();
    vector<int> tree(2 * n);
    for (int i = 0; i < n; ++i) {
        tree[n + i] = data[i];
    }
    for (int i = n - 1; i > 0; --i) {
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }
    return tree;
}

void update_tree(vector<int>& tree, int index, int value) {
    int n = tree.size() / 2;
    index += n;
    tree[index] = value;
    while (index > 1) {
        index /= 2;
        tree[index] = min(tree[2 * index], tree[2 * index + 1]);
    }
}

int query_tree(const vector<int>& tree, int left, int right) {
    int n = tree.size() / 2;
    left += n;
    right += n + 1;
    int min_val = INT_MAX;
    while (left < right) {
        if (left % 2 == 1) {
            min_val = min(min_val, tree[left]);
            left++;
        }
        if (right % 2 == 1) {
            right--;
            min_val = min(min_val, tree[right]);
        }
        left /= 2;
        right /= 2;
    }
    return min_val;
}


void solve() {
    vector<int> data = {123, 4, 23, 1, 34, 2, 123, 0, 232, 313, 4, 12, 33};
    vector<int> tree = build_tree(data);

    cout << "Min value in range [1, 7]: " << query_tree(tree, 1, 7) << endl;

    update_tree(tree, 7, 2);
    cout << "Min value in range [1, 7] after update: " << query_tree(tree, 1, 7) << endl;
}
