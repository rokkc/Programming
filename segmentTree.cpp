#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#define ll long long

template <class T>
class SegmentTree {
private:
    vector<T> segtree;
    int len;
    const T DEFAULT;
    function<T(T, T)> operation;

    void build(const vector<T>& data) {
        for (int i = 0; i < len; ++i) {
            segtree[len + i] = (i < data.size()) ? data[i] : DEFAULT;
        }
        for (int i = len - 1; i > 0; --i) {
            segtree[i] = operation(segtree[i * 2], segtree[i * 2 + 1]);
        }
    }

public:
    SegmentTree(const vector<T>& data, function<T(T, T)> op, T defaultValue) 
        : len(data.size()), operation(op), DEFAULT(defaultValue), segtree(data.size() * 2, defaultValue) {
        build(data);
    }

    void update(int ind, T val) {
        ind += len;
        segtree[ind] = val;
        for (; ind > 1; ind /= 2) {
            segtree[ind / 2] = operation(segtree[ind], segtree[ind ^ 1]);
        }
    }

    T query(int start, int end) {
        T result = DEFAULT;
        for (start += len, end += len + 1; start < end; start /= 2, end /= 2) {
            if (start % 2 == 1) { result = operation(result, segtree[start++]); }
            if (end % 2 == 1) { result = operation(result, segtree[--end]); }
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);

    vector<int> arr = {2, 54, 5, 21, 4, 1, 3, 5};
    SegmentTree<int> segtree(arr, [](int a, int b) { return min(a, b); }, INT_MAX);
    cout << segtree.query(0, 4) << "\n";
    segtree.update(2, 10);
    segtree.update(0, 5);
    cout << segtree.query(0, 4) << endl;
}
