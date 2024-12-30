#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <typename Key, typename Compare = less<pair<Key, size_t>>>
class MultiOST {
private:
    using ValueWithIndex = pair<Key, size_t>;
    using Tree = tree<
        ValueWithIndex,
        null_type,
        Compare,
        rb_tree_tag,
        tree_order_statistics_node_update>;

    Tree ost;
    size_t currentIndex = 0; 
public:

    void insert(const Key& key) {
        ost.insert({key, currentIndex++});
    }

    bool erase(const Key& key) {
        auto it = ost.lower_bound({key, 0});
        if (it != ost.end() && it->first == key) {
            ost.erase(it);
            return true;
        }
        return false;
    }

    Key find_by_order(size_t k) const {
        auto it = ost.find_by_order(k);
        if (it == ost.end()) {
            throw out_of_range("Index out of range");
        }
        return it->first;
    }

    size_t order_of_key(const Key& key) const {
        return ost.order_of_key({key, 0});
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

    MultiOST<int> multiOst;

    multiOst.insert(10);
    multiOst.insert(20);
    multiOst.insert(10);
    multiOst.insert(30);
    multiOst.insert(20);
    multiOst.insert(40);

    try {
        cout << "2nd smallest element: " << multiOst.find_by_order(3) << '\n';
    } catch (const out_of_range& e) {
        cerr << e.what() << '\n';
    }

    cout << "Number of elements smaller than 20: " << multiOst.order_of_key(20) << '\n';

    multiOst.erase(10);

    cout << "Number of elements smaller than 20 after removing one instance of 10: " << multiOst.order_of_key(20) << '\n';

    cout << "Tree size: " << multiOst.size() << '\n';
}
