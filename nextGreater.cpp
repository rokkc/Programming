vector<int> nextGreater(vector<int> &a) {
    vector<int> b(a.size(), -1);
    stack<int> s;
    for (int i = 0; i < a.size(); i++) {
        while (!s.empty() && a[s.top()] < a[i]) {
            b[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    return b;
}
