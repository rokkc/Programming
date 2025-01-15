unordered_map<int, int> compress;
unordered_map<int, int> decompress;
void compressArr(vector<int> &a) {
    int curr = 1;
    for (int i: a) {
        if (compress.count(i) == 0) {
            compress[i] = curr;
            decompress[curr] = i;
            curr++;
        }
    }
}
