#include <stdio.h>
#include <memory.h>
#include <vector>
#include <queue>
using namespace std;

/*
 시간복잡도 O(M sqrt N)
 
 Usage
 Hopcroft_Karp hk(n,m);
 // 간선 연결
 // V : 1~n,  U : 1~m
 // V의 a와 U의 b와 연결
 hk.graph[a].push_back(b);
 
 // 매칭수
 int matching = hk.solve();
 
 // 매칭결과
 hk.mx[x] // 정점 x와 매칭된 U의 정점번호
 hk.my[y] // 정점 y와 매칭된 V의 정점번호
 */

struct Hopcroft_Karp {
    static const int SIZE = 1010;
    
    int n,m;
    int mx[SIZE], my[SIZE];
    int total;
    
    int dist[SIZE];
    int inf_dist;
    
    vector<int> graph[SIZE];
    
    Hopcroft_Karp(int n,int m) {
        this->n = n; this->m = m;
        memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
        memset(dist, 0, sizeof(dist));
        total = 0;
    }
    
    void bfs() {
        queue<int> q;
        for(int i=1; i<=n; i++){
            if (mx[i] == -1) { dist[i] = 0; q.push(i); }
            else dist[i] = -1;
        }
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int i=0; i<graph[x].size(); i++) {
                int y = graph[x][i];
                if (my[y] != -1 && dist[my[y]] == -1) {
                    dist[my[y]] = dist[x] + 1;
                    q.push(my[y]);
                }
            }
        }
    }
    
    bool dfs(int x) {
        for (int i=0; i<graph[x].size(); i++) {
            int y = graph[x][i];
            if (my[y] == -1 || (dist[my[y]]==dist[x]+1 && dfs(my[y]))) {
                mx[x] = y;
                my[y] = x;
                return true;
            }
        }
        dist[x] = -1;
        return false;
    }
    
    int solve() {
        int flow;
        do {
            bfs();
            flow = 0;
            for (int i=1;i<=n;i++) if (mx[i] == -1 && dfs(i)) flow ++;
            total += flow;
        } while(flow);
        return total;
    }
};
