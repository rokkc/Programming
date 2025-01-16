template <typename T>
class WaveletTree {
private:
    T lo, hi;
    WaveletTree *l, *r;
    std::vector<int> b;

public:
    WaveletTree(typename std::vector<T>::iterator from, typename std::vector<T>::iterator to, T x = std::numeric_limits<T>::min(), T y = std::numeric_limits<T>::max())
        : lo(*std::min_element(from, to)), hi(*std::max_element(from, to)), l(nullptr), r(nullptr) {
        if (from >= to) return;
        if (lo == hi) {
            b.reserve(to - from + 1);
            b.push_back(0);
            for (auto it = from; it != to; ++it) {
                b.push_back(b.back() + 1);
            }
            return;
        }
        T mid = lo + (hi - lo) / 2;
        auto f = [mid](T x) { return x <= mid; };
        b.reserve(to - from + 1);
        b.push_back(0);
        for (auto it = from; it != to; ++it) {
            b.push_back(b.back() + f(*it));
        }
        auto pivot = std::stable_partition(from, to, f);
        l = new WaveletTree(from, pivot, lo, mid);
        r = new WaveletTree(pivot, to, mid + 1, hi);
    }

    T kth(int l, int r, int k) {
        if (l > r) return -1;
        if (lo == hi) return lo;
        int inLeft = b[r + 1] - b[l];
        if (k < inLeft) {
            return this->l->kth(b[l], b[r + 1] - 1, k);
        } else {
            return this->r->kth(l - b[l], r - b[r + 1], k - inLeft);
        }
    }

    int LTE(int l, int r, T x) {
        if (l > r || x < lo) return 0;
        if (hi <= x) return r - l + 1;
        return this->l->LTE(b[l], b[r + 1] - 1, x) + this->r->LTE(l - b[l], r - b[r + 1], x);
    }
};
