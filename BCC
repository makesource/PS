struct bcc_tree{
    int N;
    std::vector<vector<int>> v;
    std::vector<bool> chk;
    std::vector<int> bcc,d,low,parent;
    int ti;
    
    bcc_tree(){}
    bcc_tree(int size){
        N = size;
        bcc.clear(); v.clear();
        chk.resize(N+2); d.resize(N+2); low.resize(N+2); parent.resize(N+2);
        ti = 0;
        
        vector<int> temp;
        for (int i=0;i<=N;i++){
            v.push_back(temp);
            chk[i]=false; d[i]=low[i]=-1; parent[i] = i;
        }
    }
    void insert(int a,int b){
        v[a].push_back(b); v[b].push_back(a);
    }
    void tarjan(int a){
        bool isart = false;
        int child = 0;
        chk[a] = true;
        d[a]=low[a]=ti++;
        
        for (int i=0;i<v[a].size();i++){
            int b = v[a][i];
            if (!chk[b]){
                parent[b]=a;
                tarjan(b);
                child++;
                if (low[b] >= d[a] && parent[a]!=a) isart=true;
                low[a]=min(low[a],low[b]);
            }
            else if (parent[a]!=b) low[a]=min(low[a],d[b]);
        }
        if ((parent[a]!=a && isart) || (parent[a]==a && child > 1)){
            bcc.push_back(a);
        }
    }
    std::vector<int> get_bcc(){
        for (int i=1;i<=N;i++) if (!chk[i]) tarjan(i);
        return bcc;
    }
};
