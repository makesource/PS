#include <stdio.h>
#include <vector>
#include <memory.h>
#include <queue>
#define minf(a,b) ((a)<(b)?(a):(b))
#define INF 0x7fffffff/2
using namespace std;

struct Edge {
    Edge(int s, int t, int cap,int rev) {
        this->s = s; this->t = t;
        this->cap = cap; this->rev = rev;
    }
    int s,t,cap,rev;
};

struct Dinic {
    private:
    static const int SIZE = 2555;
    
    int source, sink;
    int level[SIZE], iter[SIZE];
    vector<int> graph[SIZE];
    vector<Edge> edges;
    
    void bfs(int s) {
        memset (level, -1, sizeof(level));
        queue<int> Q;
        level[s] = 0;
        Q.push(s);
        while (!Q.empty()) {
            int v = Q.front(); Q.pop();
            for (auto it : graph[v]) {
                Edge &e = edges[it];
                if (e.cap > 0 && level[e.t] < 0) {
                    level[e.t] = level[v] + 1;
                    Q.push(e.t);
                }
            }
        }
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < graph[v].size(); i++) {
            Edge &e = edges[graph[v][i]];
            if (e.cap > 0 && level[v] < level[e.t]) {
                int d = dfs(e.t, t, minf(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    edges[e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    
    public:
    Dinic(int source,int sink) {
        this->source = source;
        this->sink = sink;
    }
    void addEdge(int s,int t,int cap) {
        int z = (int) edges.size();
        edges.push_back(Edge(s,t,cap,z+1)); graph[s].push_back(z);
        edges.push_back(Edge(t,s,0,z)); graph[t].push_back(z+1);
    }
    int getFlow() {
        int flow = 0;
        while(1) {
            bfs(source);
            if (level[sink] < 0) return flow;
            memset(iter, 0 ,sizeof iter);
            int f;
            while ((f = dfs(source, sink, INF)) > 0) flow += f;
        }
    }
};
