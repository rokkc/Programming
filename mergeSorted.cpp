vector<int> merge(vector<int> &a, vector<int> &b) {
    vector<int> c;
    int i = 0, j = 0;
    while (i + j < a.size() + b.size()) {
        if (i == a.size()) {
            c.push_back(b[j]);
            j++;
        } else if (j == b.size()) {
            c.push_back(a[i]);
            i++;
        } else {
            if (a[i] < b[j]) {
                c.push_back(a[i]);
                i++;
            } else {
                c.push_back(b[j]);
                j++;
            }
        }
    }
    return c;
}
