/*
 *  find (c, d) which satisfy
 *  a * c + b * d = gcd(a, b)
 */

int gcd(int a,int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
