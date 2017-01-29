#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#define INF 0x7fffffff/2
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
using namespace std;

struct MCMF{
    int SIZE;
    int source, sink;
    vector<vector<int>> flow,cost,v;
    vector<int> dist;
    vector<int> in_que,parent;
    
    MCMF(int source,int sink,int SIZE) { // 노드의 마지막이 sink가 아닌 경우
        this->source = source; this->sink = sink; this->SIZE = SIZE;
        v.resize(SIZE+2);
        dist.resize(SIZE+2); in_que.resize(SIZE+2); parent.resize(SIZE+2);
        FOR(i,0,SIZE+2){
            flow.push_back(dist);
            cost.push_back(dist);
        }
    }
    void add_edge(int a,int b,int c){
        if (!flow[a][b] && !flow[b][a]) v[a].push_back(b), v[b].push_back(a);
        flow[a][b]=1; cost[a][b]=c; cost[b][a]=-c;
    }
    void add_edge(int a,int b,int c,int f){
        if (!flow[a][b] && !flow[b][a]) v[a].push_back(b), v[b].push_back(a);
        flow[a][b]=f; cost[a][b]=c; cost[b][a]=-c;
    }
    bool SPFA(){
        FOR(i,0,SIZE) dist[i]=INF, in_que[i]=parent[i]=0;
        queue<int> q;
        dist[source]=0; q.push(source); in_que[source]=1;
        while(!q.empty()){
            int a = q.front(); q.pop();
            in_que[a] = 0;
            for (auto b : v[a]){
                if (!flow[a][b]) continue;
                if (dist[b] > dist[a]+cost[a][b]){
                    dist[b] = dist[a]+cost[a][b];
                    parent[b]=a;
                    if (!in_que[b]) in_que[b]=1,q.push(b);
                }
            }
        }
        return dist[sink] != INF;
    }
    pair<int,int> get_MCMF(){
        int ans=0,cnt=0;
        while (SPFA()){
            cnt++;
            ans += dist[sink];
            for (int i=sink;i!=source;i=parent[i]) flow[parent[i]][i]--, flow[i][parent[i]]++;
        }
        return make_pair(ans, cnt);
    }
};
