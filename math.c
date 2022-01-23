int _pow(int a, int b) {
    int i;
    int c = 1;

    for (i = 0; i < b; i++)
        c *= a;
    return c;
}

int _fact(int x) {
    int i;
    int ret = 1;
    for (i = 1; i <= x; i++)
        ret *= i;
    return ret;
}

int sin(int x) {
    return x - (x * x * x) / 6;
}

int cos(int x) {
    return 1 - (x*x) / 2;
}