vector<int> buildPrefixVector(vector<int>& v) {
    vector<int> prefs = {0};
    for (int i: v) {
        prefs.push_back(prefs.back() + i);
    }
    return prefs;
}

int prefQuery(vector<int> prefs, int i, int j) {
    return prefs[j + 1] - prefs[i];
}

