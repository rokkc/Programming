int first_true(int lo, int hi) {
	hi++;
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		if (f(mid)) {
			hi = mid;
		} else {
			lo = mid + 1;
		}
	}
	return lo;
}

int last_true(int lo, int hi) {
	lo--;
	while (lo < hi) {
		int mid = lo + (hi - lo + 1) / 2;
		if (f(mid)) {
			lo = mid;
		} else {
			hi = mid - 1;
		}
	}
	return lo;
}

pair<int, int> findClosestValues(vector<int>& vec, int target) {
    int n = vec.size();
    if (n == 0) return {INT_MIN, INT_MIN};
    auto right = lower_bound(vec.begin(), vec.end(), target);
    int rightClosest = (right == vec.end()) ? INT_MIN : *right;

    auto left = (right == vec.begin()) ? vec.end() : prev(right);
    int leftClosest = (left == vec.end()) ? INT_MIN : *left;

    return {leftClosest, rightClosest};
}
