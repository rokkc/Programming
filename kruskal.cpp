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

vector<vector<int>> kruskal(int n, vector<vector<pair<int, int>>>& adj) {
    vector<vector<int>> mst;
    vector<int> parent(n);
    vector<int> rank(n, 0);
    vector<tuple<int, int, int>> edges;

    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        for (auto& [v, weight] : adj[i]) {
            edges.push_back({weight, i, v});
        }
    }

    sort(edges.begin(), edges.end());

    for (const auto& [weight, u, v] : edges) {
        if (find(parent, u) != find(parent, v)) {
            unionSets(parent, rank, u, v);
            mst.push_back({u, v, weight});
        }
    }

    return mst;
}

void solve() {
    int n = 6;
    vector<vector<pair<int, int>>> adj(n);

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

    for (vector<int> &edge: edges) {
        adj[edge[0] - 1].push_back(make_pair(edge[1] - 1, edge[2]));
        adj[edge[1] - 1].push_back(make_pair(edge[0] - 1, edge[2]));
    }

    vector<vector<int>> mst = kruskal(n, adj);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const auto& edge: mst) {
        cout << edge[0] << " - " << edge[1] << " : " << edge[2] << endl;
    }
}
