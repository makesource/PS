#include <queue>
#define TOTLEN 2000005
#define ALPHABET 26
using namespace std;
int ahoN;
struct Node{
    int next[ALPHABET];
    int fail;
    int depth;
}node[TOTLEN];
struct Aho_Corasick{
    void push(char a[],int len){
        int x=0;
        for (int i=1;i<=len;i++){
            if (node[x].next[a[i]-'a']==0) node[x].next[a[i]-'a']=++ahoN;
            x=node[x].next[a[i]-'a'];
        }
        node[x].depth=len;
    }
    void calc(){ // make failure link
        queue<int>Q;
        Q.push(0);
        while (!Q.empty()){
            int x=Q.front(); Q.pop();
            node[x].depth=node[x].depth<node[node[x].failure].depth?node[node[x].failure].depth:node[x].depth;
            for (int i=0;i<ALPHABET;i++){
                int y=node[x].next[i];
                if (y==0) continue;
                if (x==0) node[y].fail=0;
                else{
                    int X=x;
                    for(:;){
                        int z=node[X].fail;
                        if (node[z].next[i]!=0){
                            node[y].failure=node[z].next[i];
                            break;
                        }
                        if (z==0) break;
                        X=z;
                    }
                }
                Q.push(y);
            }
        }
    }
};
