/*
 *  find (c, d) which satisfy
 *  a * c + b * d = gcd(a, b)
 */

#define make_pair mp
typedef long long ll;
pair<ll, ll> extended_gcd(ll a,ll b) {
    if (b == 0) return mp(1,0);
    pair<ll, ll> t = extended_gcd(b, a%b);
    return mp(t.second, t.first - t.second * (a/b));
}
