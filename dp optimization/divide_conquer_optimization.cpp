/*
 조건 1) DP 점화식 꼴
 D[t][i]=mink<i(D[t−1][k]+C[k][i])
 조건 2) A[t][i]는 D[t][i]를 만족시키는 최소 k라 할 때 아래 부등식을 만족
 A[t][i]≤A[t][i+1]
 
 조건 1의 점화식 꼴이고, 비용 C가 사각부등식 C[a][c]+C[b][d]≤C[a][d]+C[b][c]를 만족하는 경우 조건 2도 만족한다.
 */

#include <stdio.h>
#define maxf(a,b) ((a)>(b)?(a):(b))
#define minf(a,b) ((a)<(b)?(a):(b))
typedef long long ll;
ll dp[100010];
ll T[100010], V[100010];
int D, N;

ll cost(ll a,ll b) {
    return (b-a) * T[b] + V[a];
}

void divide (int l,int r,int p,int q) {
    if (l > r) return;
    int m = (l + r) >> 1;
    
    int pos = -1;
    for (int i=maxf(p, m-D);i<=minf(q, m);i++) {
        if (dp[m] < cost(i,m)) {
            dp[m] = cost(i,m);
            pos = i;
        }
    }
    divide(l,m-1,p,pos);
    divide(m+1,r,pos,q);
}

int main() {
    scanf ("%d%d",&N,&D);
    for (int i=1;i<=N;i++) scanf ("%lld",&T[i]);
    for (int i=1;i<=N;i++) scanf ("%lld",&V[i]);
    divide(1, N, 1, N);
    ll ans = 0;
    for (int i=1;i<=N;i++) ans = maxf(ans, dp[i]);
    printf ("%lld",ans);
    return 0;
}

