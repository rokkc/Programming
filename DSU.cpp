vector<int> parent;
vector<int> rankVec;

void createDSU(int n) {
    parent.resize(n);
    rankVec.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void unite(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    if (rootU != rootV) {
        if (rankVec[rootU] > rankVec[rootV]) {
            parent[rootV] = rootU;
        } else if (rankVec[rootU] < rankVec[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rankVec[rootU]++;
        }
    }
}

int main() {
    createDSU(5);

    unite(0, 2);
    unite(4, 2);
    unite(3, 1);

    if (find(1) == find(0)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}
