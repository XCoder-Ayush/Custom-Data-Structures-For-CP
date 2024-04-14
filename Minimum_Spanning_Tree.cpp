// Create MST
#include <bits/stdc++.h> 
using namespace std;
class DSU
{
    public:
    int findParent(int node,vector<int>& par)
    {
        if(par[node]==node)return node;
        return par[node]=findParent(par[node],par);
    }
    void Union(int u,int v,vector<int> &size,vector<int> &par)
    {
        int pu=findParent(u,par);
        int pv=findParent(v,par);
        if(pu==pv)return;
        if(size[pu]<=size[pv])
        {
            par[pu]=pv;
            size[pv]++;
        }
        else
        {
            par[pv]=pu;
            size[pu]++;
        }
    }
};

bool cmp(vector<int> &v1,vector<int> &v2){
    return v1[2]<v2[2];
}
int formMST(int n, int m, vector<vector<int>> &edges)
{
    sort(edges.begin(),edges.end(),cmp);
    DSU dsu;
    vector<int> par(n+1),size(n+1,1);
    for(int i=1;i<=n;i++)par[i]=i;

    int ans=0;
    int comp=n;
    vector<vector<int>> mst;
    for(auto &it : edges){
        int u=it[0];
        int v=it[1];
        int w=it[2];

        if(dsu.findParent(u,par)!=dsu.findParent(v,par)){
            dsu.Union(u,v,size,par);
            mst.push_back({u,v});
            ans+=w;
            comp-=1;
        }
    }
    if(comp>1)return -1;
    // for(auto &it : mst)
    //     cout<<it[0]<<" "<<it[1]<<endl;
    return ans;
}

int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> edges;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({u,v,w});
    }
    cout<<formMST(n,m,edges)<<endl;
}
