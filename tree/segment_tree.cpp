#include <vector>
typedef long long ll;
using namespace std;

struct segment_tree { // Lazy Propagation
private:
    int N;
    std::vector<ll> tree;
    void update(int x, int L, int R, int range_L, int range_R, ll val, ll f(ll, ll)) {
        // x : node's index
        // L, R : current node's range
        // range_L, range_R : target range
        if (range_R < L || R < range_L) return ;
        if (L > R || range_L > range_R) return ;
        
        if (range_L <= L && R <= range_R) {
            tree[x] = f(tree[x], val);
            return ;
        }
        int M = (L + R) / 2;
        update(x*2, L, M, range_L, range_R, val, f);
        update(x*2+1, M+1, R, range_L, range_R, val, f);
    }
    ll find_range(int x, int L, int R, int range_L, int range_R, ll f(ll, ll)) {
        // x : node's index
        // L, R : current node's range
        // range_L, range_R : target range

        if (range_R < L || R < range_L) return DEFAULT;
        if (L > R || range_L > range_R) return DEFAULT;
        if (range_L <= L && R <= range_R) {
            return tree[x];
        }
        int M = (L + R) / 2;
        ll left_v = find_range(x*2, L, M, range_L, range_R, f);
        ll right_v = find_range(x*2+1, M+1,R, range_L, range_R, f);
        return f(left_v, right_v);
    }
    
public:
    ll DEFAULT;
    segment_tree(int size, ll DEF) {
        N = size;
        DEFAULT = DEF;
        tree.resize(N + 1);
        for (int i=1;i<=N;i++) tree[i] = lazy[i] = DEFAULT;
    }
    void update(int L, int R, ll val, ll f(ll, ll)) { update(1, 1, N, L, R, val, f); }
    ll find_single(int X, ll f(ll, ll)) { return find_range(1, 1, N, X, X, f); }
    ll find_range(int L, int R, ll f(ll, ll)) { return find_range(1, 1, N, L, R, f); }
};
