#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define MAXN 30010
#define logN 19
vector<int> v[MAXN];
int ac[MAXN][logN],tin[MAXN],tout[MAXN],dis[MAXN],n,t;
//ac[r][i]求r的第i層祖先 , tin、tout時間戳記 , dis是求深度 , t是dfs計時器 
void dfs(int r,int fa){
    ac[r][0]=fa;
    tin[r]=t++;
    for(int i=1;(1<<i)<=n;i++)
        ac[r][i]=ac[ac[r][i-1]][i-1];
    for(auto i:v[r]){
        dis[i]=dis[r]+1;
        dfs(i,r);
    }
    tout[r]=t++;
}
bool is_ac(int a,int b){
    if(a<=0) return 1;
    return tin[a]<=tin[b]&&tout[a]>=tout[b];  //  拿/不拿掉等號評測WA的答案是相同的
} 
int lca(int a,int b){
    if(a==b||is_ac(a,b)) return a;
    if(is_ac(b,a)) return b;
    for(int i=logN;i>=0;i--){
        if(!is_ac(ac[a][i],b))
            a=ac[a][i];
    }
    return ac[a][0];
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        while(cin>>x&&x){
            v[i].push_back(x);
        }
    }
    dfs(1,-1);
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        int qq=lca(x,y);
        //cout<<"(x,y)="<<'('<<x<<","<<y<<")\n";
        cout<<qq<<' '<<dis[x]+dis[y]-2*dis[qq]<<'\n';
    }
}