template<typename T>
class WaveletMatrix {
    int n, maxLog;
    vector<vector<int>> mat;
    vector<int> zs;
    vector<T>* values;
public:
    WaveletMatrix(typename vector<T>::iterator from, typename vector<T>::iterator to) {
        vector<T> temp(from, to);
        vector<T> sorted = temp;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        values = new vector<T>(sorted.begin(), sorted.end());
        vector<int> A(temp.size());
        for (size_t i = 0; i < temp.size(); i++) {
            A[i] = lower_bound(values->begin(), values->end(), temp[i]) - values->begin();
        }
        n = A.size();
        int m = values->size();
        maxLog = m > 1 ? 32 - __builtin_clz(m - 1) : 1;
        mat.resize(maxLog);
        zs.resize(maxLog);
        for (int i = 0; i < maxLog; i++) {
            int bit = maxLog - 1 - i;
            mat[i].resize(n + 1);
            mat[i][0] = 0;
            for (int j = 0; j < n; j++) {
                mat[i][j + 1] = mat[i][j] + ((A[j] >> bit) & 1);
            }
            zs[i] = n - mat[i][n];
            vector<int> B(n);
            int z = 0, o = zs[i];
            for (int j = 0; j < n; j++) {
                if (((A[j] >> bit) & 1) == 0)
                    B[z++] = A[j];
                else
                    B[o++] = A[j];
            }
            A.swap(B);
        }
    }

    T kth(int l, int r, int k) {
        int res = 0, L = l, R = r;
        for (int i = 0; i < maxLog; i++) {
            int onesL = mat[i][L];
            int onesR = mat[i][R + 1];
            int zerosCount = (R - L + 1) - (onesR - onesL);
            if (k < zerosCount) {
                int newL = L - mat[i][L];
                L = newL;
                R = newL + zerosCount - 1;
            } else {
                k -= zerosCount;
                int newL = zs[i] + mat[i][L];
                int newR = zs[i] + onesR - 1;
                L = newL;
                R = newR;
                res |= 1 << (maxLog - 1 - i);
            }
        }
        return (*values)[res];
    }

    int LTE(int l, int r, T x) {
        int c = upper_bound(values->begin(), values->end(), x) - values->begin();
        int ans = 0, L = l, R = r;
        for (int i = 0; i < maxLog; i++) {
            int bit = (c >> (maxLog - 1 - i)) & 1;
            int onesL = mat[i][L];
            int onesR = mat[i][R + 1];
            int zerosCount = (R - L + 1) - (onesR - onesL);
            if (bit == 1) {
                ans += zerosCount;
                L = zs[i] + mat[i][L];
                R = zs[i] + onesR - 1;
            } else {
                int newL = L - mat[i][L];
                L = newL;
                R = newL + zerosCount - 1;
            }
        }
        return ans;
    }

    ~WaveletMatrix() {
        delete values;
    }
};
