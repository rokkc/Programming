class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);

    DSU dsu(10);

    dsu.unionSets(0, 1);
    dsu.unionSets(1, 2);
    dsu.unionSets(3, 4);

    cout << "Is 0 and 2 connected? " << (dsu.connected(0, 2) ? "Yes" : "No") << endl;
    cout << "Is 0 and 4 connected? " << (dsu.connected(0, 4) ? "Yes" : "No") << endl;
}
