template <typename T>
class WaveletTree {
private:
    int lo, hi;
    WaveletTree *l, *r;
    vector<int> b;
    vector<T>* values;
    bool isRoot;
public:
    WaveletTree(typename vector<T>::iterator from, typename vector<T>::iterator to) {
        isRoot = true;
        vector<T> temp(from, to);
        vector<T> sorted = temp;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        values = new vector<T>(sorted.begin(), sorted.end());
        lo = 0; hi = values->size() - 1;
        vector<int> comp; comp.resize(temp.size());
        for (size_t i = 0; i < temp.size(); ++i) comp[i] = lower_bound(values->begin(), values->end(), temp[i]) - values->begin();
        b.reserve(comp.size() + 1); b.push_back(0);
        if (lo == hi) { for (auto x : comp) b.push_back(b.back() + 1); l = r = nullptr; }
        else { int mid = lo + (hi - lo) / 2; auto f = [mid](int x){ return x <= mid; }; for (auto x : comp) b.push_back(b.back() + (f(x) ? 1 : 0)); auto pivot = stable_partition(comp.begin(), comp.end(), f); l = (comp.begin() != pivot) ? new WaveletTree(comp.begin(), pivot, lo, mid, values) : nullptr; r = (pivot != comp.end()) ? new WaveletTree(pivot, comp.end(), mid + 1, hi, values) : nullptr; }
    }
private:
    WaveletTree(typename vector<int>::iterator from, typename vector<int>::iterator to, int lo, int hi, vector<T>* values)
         : lo(lo), hi(hi), l(nullptr), r(nullptr), values(values), isRoot(false) {
        b.reserve((to - from) + 1); b.push_back(0);
        if (lo == hi) { for (auto it = from; it != to; ++it) b.push_back(b.back() + 1); return; }
        int mid = lo + (hi - lo) / 2; auto f = [mid](int x){ return x <= mid; };
        for (auto it = from; it != to; ++it) b.push_back(b.back() + (f(*it) ? 1 : 0));
        auto pivot = stable_partition(from, to, f);
        if (from != pivot) l = new WaveletTree(from, pivot, lo, mid, values);
        if (pivot != to) r = new WaveletTree(pivot, to, mid + 1, hi, values);
    }
public:
    T kth(int i, int j, int k) {
        if (i > j) return T();
        if (lo == hi) return (*values)[lo];
        int inLeft = b[j + 1] - b[i];
        if (k < inLeft) return l->kth(b[i], b[j + 1] - 1, k);
        else return r->kth(i - b[i], j - b[j + 1], k - inLeft);
    }
    int LTE(int i, int j, T x) {
        if (i > j || x < (*values)[lo]) return 0;
        if ((*values)[hi] <= x) return j - i + 1;
        int leftCount = (l ? l->LTE(b[i], b[j + 1] - 1, x) : 0);
        int rightCount = (r ? r->LTE(i - b[i], j - b[j + 1], x) : 0);
        return leftCount + rightCount;
    }
    ~WaveletTree() { delete l; delete r; if (isRoot) delete values; }
};
