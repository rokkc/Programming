vector<vector<int>> primMST(vector<vector<pair<int, int>>> &graph, int V) {
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<vector<int>> mst;

    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto &[v, weight] : graph[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            mst.push_back({parent[i], i, key[i]});
        }
    }
    return mst;
}

void solve() {
    int V = 6;
    vector<vector<pair<int, int>>> adj(V);
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

    for (vector<int> edge: edges) {
        adj[edge[0] - 1].push_back(make_pair(edge[1] - 1, edge[2]));
        adj[edge[1] - 1].push_back(make_pair(edge[0] - 1, edge[2]));
    }

    vector<vector<int>> mst = primMST(adj, V);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const auto& edge: mst) {
        cout << edge[0] + 1 << " - " << edge[1] + 1 << " : " << edge[2] << endl;
    }
}
