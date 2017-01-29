#include <stdio.h>
#define maxf(a,b) ((a)>(b)?(a):(b))
#define minf(a,b) ((a)<(b)?(a):(b))
typedef long long ll;

struct CHT {
    static const int SIZE = 200020;
    ll aa[SIZE], bb[SIZE];
    int sz = 0;
    
    double getX(int a,int b) {
        return (1.0) * (bb[b] - bb[a]) / (aa[a] - aa[b]);
    }
    void add(ll a,ll b) {
        aa[sz] = a; bb[sz] = b;

        if (sz > 0 && aa[sz-1] == aa[sz]) {
            aa[sz-1] = aa[sz];
            bb[sz-1] = minf(bb[sz-1],bb[sz]);
            sz--;        
        }
        
        while (sz>=2 && (getX(sz-2, sz-1) > getX(sz-1, sz))) { // get(sz-2,sz-1) < getX(sz-1, sz) 유지
            aa[sz - 1] = aa[sz];
            bb[sz - 1] = bb[sz];
            sz --;
        }
        sz ++;
    }
    ll query(ll pos) {
        int l = 0, r = sz - 2;
        ll ans = -9e18;
        while (l <= r) {
            int m = (l + r) / 2;
            if (getX(m, m+1) <= pos) {
                ans = maxf(ans, aa[m+1] * pos + bb[m+1]);
                l = m + 1;
            } else {
                ans = maxf(ans, aa[m] * pos + bb[m]);
                r = m - 1;
            }
        }
        return ans;
    }
};

/*
            int p = 0;
            for (int i=sub.sz-1;i>=0;i--) {
                if (sub.aa[i] > a) {
                    sub.aa[i+1] = sub.aa[i];
                    sub.bb[i+1] = sub.bb[i];
                } else {
                    p = i + 1;
                    break;
                }
            }
            sub.aa[p] = a; sub.bb[p] = b;
            sub.sz ++;
            
            if (sub.sz >= 500) {
                tmp.sz = 0;
                int s1 = 0, s2 = 0;
                while (s1 < cht.sz && s2 < sub.sz) {
                    if (cht.aa[s1] < sub.aa[s2]) tmp.add(cht.aa[s1], cht.bb[s1]), s1 ++;
                    else tmp.add(sub.aa[s2], sub.bb[s2]), s2 ++;
                }
                while (s1 < cht.sz) tmp.add(cht.aa[s1], cht.bb[s1]), s1 ++;
                while (s2 < sub.sz) tmp.add(sub.aa[s2], sub.bb[s2]), s2 ++;
                cht.sz = tmp.sz;
                for (int i=0;i<cht.sz;i++) cht.aa[i] = tmp.aa[i], cht.bb[i] = tmp.bb[i];
                sub.sz = 0;
*/
