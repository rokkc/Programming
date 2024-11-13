int mod(int x, int y) {
    int modInt = x % y;
    return modInt >= 0 ? modInt : modInt + y;
}
