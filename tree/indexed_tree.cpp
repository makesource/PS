typedef long long int ll;
struct indexed_tree {
private:
  int N;
  std::vector<ll> tree;
  void update_tree(int x, ll cnt, ll f(ll, ll)) {
    if (x == 0) return;
    tree[x] = f(tree[x], cnt);
    update_tree(x >> 1, cnt, f);
  }
  ll find_tree(int left, int right, ll f(ll, ll)) {
    int L = left, R = right;
    ll res = DEFAULT;
    while (L <= R) {
      if (L & 1) res = f(res, tree[L++]);
      if (!(R & 1)) res = f(res, tree[R--]);
      L >>= 1, R >>= 1;
    }
    return res;
  }

public:
  ll DEFAULT;
  indexed_tree() {};
  indexed_tree(ll size, ll _DEFAULT) {
    N = size;
    DEFAULT = _DEFAULT;
    tree.resize(size * 2 + 2);
    FOR(i, 1, size*2 + 1) tree[i] = DEFAULT;
  }

  void update(int x, ll cnt, ll f(ll, ll)) { update_tree(x + N, cnt, f); }
  ll find(int left, int right, ll f(ll, ll)) { return find_tree(left + N, right + N, f); }
};

