struct SCC {
    private:
    int n, m, componentNum;
    std::vector< std::vector<int> > edge, rev_edge;
    std::vector<int> number, order;
    std::vector<bool> visit;
    
    void dfs(int x) {
        visit[x] = true;
        for (auto it : edge[x]) {
            if (visit[it]) continue;
            dfs(it);
        }
        order.push_back(x);
    }
    void rev_dfs(int x) {
        visit[x] = true;
        number[x] = componentNum;
        for (auto it : rev_edge[x]) {
            if (visit[it]) continue;
            rev_dfs(it);
        }
    }
    public:
    SCC() {};
    SCC(int _n) {
        n = _n;
        number.clear(); edge.clear(); rev_edge.clear();
        edge.resize(n + 1);
        rev_edge.resize(n + 1);
        number.resize(n + 1);
    }
    // usage
    void push_edge(int x, int y) {
        edge[x].push_back(y);
        rev_edge[y].push_back(x);
    }
    void scc() {
        visit.clear(); visit.resize(n + 1);
        order.clear();
        FOR(i, 1, n) {
            if (visit[i]) continue;
            dfs(i);
        }
        visit.clear(); visit.resize(n + 1);
        componentNum = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (visit[order[i]]) continue;
            componentNum++;
            rev_dfs(order[i]);
        }
    }
    int getComponentNumber() {
        return componentNum;
    }
    int getSpecificNumber(int x) {
        return number[x];
    }
    std::vector<int> getTotalNumber() {
        return number;
    }
};
