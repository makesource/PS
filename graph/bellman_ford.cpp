// https://www.acmicpc.net/problem/11657
// source by rhs0266

#include <stdio.h>
#include <vector>
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
#define si(n) fscanf(in,"%d",&n)
//FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
FILE *in = stdin, *out = stdout;
using namespace std;

typedef int ll;
struct EDGE {
    int v; ll cnt;
    EDGE() {};
    EDGE(int _v, ll _cnt) :v(_v), cnt(_cnt) {};
};
struct BellmanFord {
    private:
    int n, m;
    std::vector< std::vector<EDGE> > edge; // TODO : Change size as maximum N
    std::vector<ll> dist;
    bool bellmanford(int start) {
        FOR(i, 1, n) dist[i] = 0x7fffffff;
        dist[start] = 0;
        FOR(k, 1, n - 1) {
            FOR(i, 1, n) {
                if (dist[i] == 0x7fffffff) continue;
                for (int j = 0; j < edge[i].size(); j++) {
                    ll y = edge[i][j].v;
                    ll cnt = edge[i][j].cnt;
                    dist[y] = dist[y] < dist[i] + cnt ? dist[y] : dist[i] + cnt;
                }
            }
        }
        
        bool neg_cycle = false;
        FOR(i, 1, n) {
            if (dist[i] == 0x7fffffff) continue;
            for (int j = 0; j < edge[i].size(); j++) {
                ll y = edge[i][j].v;
                ll cnt = edge[i][j].cnt;
                if (dist[y] > dist[i] + cnt) neg_cycle = true;
            }
        }
        return neg_cycle;
    }
    
    public:
    BellmanFord() {};
    BellmanFord(int _n) {
        n = _n;
        dist.clear(); edge.clear();
        dist.resize(n + 1);
        edge.resize(n + 1);
    }
    void push_edge(int x, int y, ll cnt) {
        edge[x].push_back(EDGE(y, cnt));
        //edge[y].push_back(EDGE(x, cnt)); // bi-directed case
    }
    bool calc(int start) {
        return bellmanford(start);
    }
    std::vector<ll> getDist() {
        return dist;
    }
};
int n, m;
int main() {
    BellmanFord bf;
    
    si(n), si(m);
    bf = BellmanFord(n);
    FOR(i, 1, m) {
        int x, y, cnt;
        si(x), si(y), si(cnt); // x->y, dist : cnt
        bf.push_edge(x, y, cnt); // push edge to graph
    }
    
    if (bf.calc(1)) {
        fprintf(out, "-1"); // negative cycle
        return 0;
    }
    std::vector<ll> ans = bf.getDist(); // get shortest distance
    FOR(i, 2, n) {
        fprintf(out, "%d\n", ans[i] == 0x7fffffff ? -1 : ans[i]);
    }
    return 0;
}
