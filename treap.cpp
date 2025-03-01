#include <bits/stdc++.h>
using namespace std;

class ImplicitTreap {
private:
    struct Node {
        int val;
        int priority;
        Node* left;
        Node* right;
        int size;
        long long sum;
        int mn;
        int mx;
        int lazyAdd;
        int lazySet;
        bool toSet;
        Node(int _val) : val(_val), priority(rand()), left(nullptr), right(nullptr), size(1), sum(_val), mn(_val), mx(_val), lazyAdd(0), lazySet(0), toSet(false) {}
    };
    Node* root;
    int getSize(Node* t) { return t ? t->size : 0; }
    long long getSum(Node* t) { return t ? t->sum : 0LL; }
    int getMin(Node* t) { return t ? t->mn : INT_MAX; }
    int getMax(Node* t) { return t ? t->mx : INT_MIN; }
    void update(Node* t) {
        if (!t) return;
        t->size = 1 + getSize(t->left) + getSize(t->right);
        t->sum = t->val + getSum(t->left) + getSum(t->right);
        t->mn = min(t->val, min(getMin(t->left), getMin(t->right)));
        t->mx = max(t->val, max(getMax(t->left), getMax(t->right)));
    }
    void applySet(Node* t, int value) {
        if (!t) return;
        t->val = value;
        t->sum = (long long)value * t->size;
        t->mn = value;
        t->mx = value;
        t->toSet = true;
        t->lazySet = value;
        t->lazyAdd = 0;
    }
    void applyAdd(Node* t, int addVal) {
        if (!t) return;
        if (t->toSet) {
            t->lazySet += addVal;
            t->val += addVal;
            t->sum = (long long)t->lazySet * t->size;
            t->mn += addVal;
            t->mx += addVal;
        } else {
            t->val += addVal;
            t->sum += (long long)addVal * t->size;
            t->mn += addVal;
            t->mx += addVal;
            t->lazyAdd += addVal;
        }
    }
    void push(Node* t) {
        if (!t) return;
        if (t->toSet) {
            if (t->left) applySet(t->left, t->lazySet);
            if (t->right) applySet(t->right, t->lazySet);
            t->toSet = false;
            t->lazySet = 0;
        }
        if (t->lazyAdd != 0) {
            if (t->left) applyAdd(t->left, t->lazyAdd);
            if (t->right) applyAdd(t->right, t->lazyAdd);
            t->lazyAdd = 0;
        }
    }
    void split(Node* t, int key, Node*& left, Node*& right) {
        if (!t) {
            left = nullptr;
            right = nullptr;
            return;
        }
        push(t);
        int curIndex = getSize(t->left);
        if (key <= curIndex) {
            split(t->left, key, left, t->left);
            right = t;
        } else {
            split(t->right, key - curIndex - 1, t->right, right);
            left = t;
        }
        update(t);
    }
    Node* merge(Node* left, Node* right) {
        if (!left || !right)
            return left ? left : right;
        push(left);
        push(right);
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            update(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            update(right);
            return right;
        }
    }
    void insert(Node*& t, int pos, int val) {
        Node* newNode = new Node(val);
        Node *left, *right;
        split(t, pos, left, right);
        t = merge(merge(left, newNode), right);
    }
    void erase(Node*& t, int pos) {
        Node *left, *mid, *right;
        split(t, pos, left, mid);
        split(mid, 1, mid, right);
        delete mid;
        t = merge(left, right);
    }
    void rangeAdd(Node*& t, int l, int r, int addVal) {
        Node *left, *mid, *right;
        split(t, l, left, mid);
        split(mid, r - l + 1, mid, right);
        if (mid) applyAdd(mid, addVal);
        t = merge(merge(left, mid), right);
    }
    void rangeSet(Node*& t, int l, int r, int setVal) {
        Node *left, *mid, *right;
        split(t, l, left, mid);
        split(mid, r - l + 1, mid, right);
        if (mid) applySet(mid, setVal);
        t = merge(merge(left, mid), right);
    }
    tuple<long long, int, int> rangeQuery(Node*& t, int l, int r) {
        Node *left, *mid, *right;
        split(t, l, left, mid);
        split(mid, r - l + 1, mid, right);
        long long resSum = getSum(mid);
        int resMin = getMin(mid);
        int resMax = getMax(mid);
        t = merge(merge(left, mid), right);
        return {resSum, resMin, resMax};
    }
    void pointUpdate(Node*& t, int pos, int newVal) {
        Node *left, *mid, *right;
        split(t, pos, left, mid);
        split(mid, 1, mid, right);
        if (mid) {
            mid->val = newVal;
            mid->sum = newVal;
            mid->mn = newVal;
            mid->mx = newVal;
            mid->lazyAdd = 0;
            mid->toSet = false;
        }
        t = merge(merge(left, mid), right);
    }
    void inorder(Node* t) {
        if (!t) return;
        push(t);
        inorder(t->left);
        cout << t->val << " ";
        inorder(t->right);
    }
public:
    ImplicitTreap() : root(nullptr) { srand(time(0)); }
    void print() { inorder(root); cout << endl; }
    int size() { return getSize(root); }
    void insert(int pos, int val) { insert(root, pos, val); }
    void erase(int pos) { erase(root, pos); }
    void updateValue(int pos, int newVal) { pointUpdate(root, pos, newVal); }
    void addRange(int l, int r, int addVal) { rangeAdd(root, l, r, addVal); }
    void setRange(int l, int r, int setVal) { rangeSet(root, l, r, setVal); }
    long long rangeSum(int l, int r) { return get<0>(rangeQuery(root, l, r)); }
    int rangeMin(int l, int r) { return get<1>(rangeQuery(root, l, r)); }
    int rangeMax(int l, int r) { return get<2>(rangeQuery(root, l, r)); }
};

int main() {
    ImplicitTreap treap;
    treap.insert(0, 5);
    treap.insert(1, 3);
    treap.insert(2, 7);
    treap.insert(3, 9);
    cout << "Initial treap: ";
    treap.print();
    cout << "Size: " << treap.size() << endl;
    treap.addRange(1, 2, 2);
    cout << "After adding 2 to range [1,2]: ";
    treap.print();
    treap.setRange(0, 1, 10);
    cout << "After setting range [0,1] to 10: ";
    treap.print();
    cout << "Range sum [0,2]: " << treap.rangeSum(0, 2) << endl;
    cout << "Range min [1,3]: " << treap.rangeMin(1, 3) << endl;
    cout << "Range max [1,3]: " << treap.rangeMax(1, 3) << endl;
    treap.updateValue(2, 4);
    cout << "After updating position 2 to 4: ";
    treap.print();
    treap.erase(1);
    cout << "After erasing position 1: ";
    treap.print();
    return 0;
}
