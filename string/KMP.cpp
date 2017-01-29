#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstdio>
#define M 2000009
using namespace std;

char S[M],T[M];
int fail[M];
vector<int> ans;
int main(){
    int i;
    
    cin.getline(T,M);
    cin.getline(S,M);
    int now=-1;
    fail[0]=now;
    for (i=1;S[i];i++){
        while(now>=0 && S[now+1]!=S[i]) now=fail[now];
        if (S[now+1]==S[i]) now++;
        fail[i]=now;
    }
    int len = i;
    now = -1;
    for (i=0;T[i];i++){
        while(now>=0 && S[now+1]!=T[i]) now=fail[now];
        if (S[now+1]==T[i]) now++;
        if (!S[now+1]){
            ans.push_back(i-len+2);
            now=fail[now];
        }
    }
    printf("%d\n",(int)ans.size());
    for (i=0;i<ans.size();i++) printf("%d ",ans[i]);
    return 0;
}
