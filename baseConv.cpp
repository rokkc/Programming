vector<int> convertToBaseN(int n, int base) {
    vector<int> res;
    while (n) {
        res.push_back(n % base);
        n /= base;
    }
    reverse(res.begin(), res.end());
    return res;
}

