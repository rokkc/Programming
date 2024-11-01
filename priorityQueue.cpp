void solve() {
    priority_queue<int> maxHeap;

    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);
    maxHeap.push(5);

    cout << "Max-Heap Priority Queue: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;

    priority_queue<int, vector<int>, greater<int>> minHeap;

    minHeap.push(10);
    minHeap.push(30);
    minHeap.push(20);
    minHeap.push(5);

    cout << "Min-Heap Priority Queue: ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;
}
