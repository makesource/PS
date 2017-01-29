int R=0,p=0;
FOR(i, 1, n) {
    if (i <= R) dy[i] = min(dy[2 * p - i], R - i);
    else dy[i] = 0;
    while (i - dy[i] - 1 >= 1 && i + dy[i] + 1 <= 2 * n - 1 && a[i - dy[i] - 1] == a[i + dy[i] + 1]) dy[i]++;
    if (i + dy[i] > R) R = i + dy[i], p = i;
}
