template<typename T>
class SegmentTree {
private:
    vector<T> tree;
    int n;
    function<T(T, T)> op;  
    T identity;  

    void build(const vector<T>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];  
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);  
            build(arr, 2 * node + 1, mid + 1, end);  
            tree[node] = op(tree[2 * node], tree[2 * node + 1]);  
        }
    }

    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return identity;  
        }
        if (l <= start && end <= r) {
            return tree[node];  
        }
        int mid = (start + end) / 2;
        T leftQuery = query(2 * node, start, mid, l, r);  
        T rightQuery = query(2 * node + 1, mid + 1, end, l, r);  
        return op(leftQuery, rightQuery);  
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            tree[node] = val;  
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node, start, mid, idx, val);  
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);  
            }
            tree[node] = op(tree[2 * node], tree[2 * node + 1]);  
        }
    }

public:

    SegmentTree(const vector<T>& arr, function<T(T, T)> operation, T identityElement) {
        n = arr.size();
        tree.resize(4 * n);  
        op = operation;
        identity = identityElement;
        build(arr, 1, 0, n - 1);
    }

    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void update(int idx, T val) {
        update(1, 0, n - 1, idx, val);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);

    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree<int> segTreeSum(arr, [](int a, int b) { return a + b; }, 0);

    cout << "Sum of range [1, 3]: " << segTreeSum.query(1, 3) << endl;  
    segTreeSum.update(3, 6);  
    cout << "Sum of range [1, 3] after update: " << segTreeSum.query(1, 3) << endl;  

    SegmentTree<int> segTreeMin(arr, [](int a, int b) { return min(a, b); }, INT_MAX);

    cout << "Min of range [1, 4]: " << segTreeMin.query(1, 4) << endl;  
    segTreeMin.update(2, 2);  
    cout << "Min of range [1, 4] after update: " << segTreeMin.query(1, 4) << endl;  

    SegmentTree<int> segTreeMax(arr, [](int a, int b) { return max(a, b); }, INT_MIN);

    cout << "Max of range [2, 5]: " << segTreeMax.query(2, 5) << endl;  
    segTreeMax.update(4, 15);  
    cout << "Max of range [2, 5] after update: " << segTreeMax.query(2, 5) << endl;  
}
