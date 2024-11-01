int find(vector<int>& parent, int u) {
    if (parent[u] != u) {
        parent[u] = find(parent, parent[u]);
    }
    return parent[u];
}

void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
    int root_u = find(parent, u);
    int root_v = find(parent, v);
    if (root_u != root_v) {
        if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
    }
}

vector<vector<int>> kruskal(int n, vector<vector<int>>& edges) {
    vector<vector<int>> mst;
    vector<int> parent(n);
    vector<int> rank(n, 0);

    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2];
    });

    for (const auto& edge : edges) {
        if (find(parent, edge[0]) != find(parent, edge[1])) {
            unionSets(parent, rank, edge[0], edge[1]);
            mst.push_back(edge);
        }
    }

    return mst;
}

void solve() {
    int n = 6;
    vector<vector<int>> edges = {
        {1, 2, 9},
        {1, 3, 4},
        {2, 3, 1},
        {2, 4, 5},
        {2, 5, 3},
        {3, 5, 2},
        {4, 6, 8},
        {5, 6, 7}
    };

    vector<vector<int>> mst = kruskal(n, edges);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const auto& edge: mst) {
        cout << edge[0] << " - " << edge[1] << " : " << edge[2] << endl;
    }
}
