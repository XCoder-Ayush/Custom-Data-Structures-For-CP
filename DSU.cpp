// DSU
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
    bool isConnected(int u,int v,vector<int> &par){
        return findParent(u,par)==findParent(v,par);
    }
};
