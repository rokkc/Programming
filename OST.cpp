#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <typename Key, typename Compare = less<Key>>
class OrderStatisticTree {
private:
    using Tree = tree<
        Key,
        null_type,
        Compare,
        rb_tree_tag,
        tree_order_statistics_node_update>;

    Tree ost;

public:
    void insert(const Key& key) {
        ost.insert(key);
    }

    void erase(const Key& key) {
        ost.erase(key);
    }

    Key find_by_order(size_t k) const {
        auto it = ost.find_by_order(k);
        if (it == ost.end()) {
            throw out_of_range("Index out of range");
        }
        return *it;
    }

    size_t order_of_key(const Key& key) const {
        return ost.order_of_key(key);
    }

    size_t size() const {
        return ost.size();
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);

    OrderStatisticTree<int> ost;

    ost.insert(10);
    ost.insert(20);
    ost.insert(30);
    ost.insert(40);
    ost.insert(50);

    try {
        cout << "2nd smallest element: " << ost.find_by_order(4) << '\n';
    } catch (const out_of_range& e) {
        cerr << e.what() << '\n';
    }

    cout << "Number of elements smaller than 35: " << ost.order_of_key(35) << '\n';

    ost.erase(29);

    cout << "Number of elements smaller than 35 after removal: " << ost.order_of_key(35) << '\n';

    cout << "Tree size: " << ost.size() << '\n';
}
