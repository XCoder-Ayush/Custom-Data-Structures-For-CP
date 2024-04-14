/**
 * @parent[node] -> represents the parent of the connected component containing node.
 * @size[node] -> represents the size of the connected component containing node.
 * 
 * DSU Build -> O(N)
 * DSU findParent -> O(logN) Due To Path Compression & Size Compression
 * DSU Union -> O(logN)
*/

#include <bits/stdc++.h> 
using namespace std;
class DSU
{
private:
    int n;
    vector<int> parent;
    vector<int> size;
public:
    DSU(int n){
        parent.resize(n);
        size.resize(n,1);
        this->n=n;
        for(int i=0;i<n;i++)parent[i]=i;
    }

    int findParent(int node)
    {
        if(parent[node]==node)return node;
        return parent[node]=findParent(parent[node]);
    }
    void Union(int u,int v)
    {
        int pu=findParent(u);
        int pv=findParent(v);
        if(pu==pv)return;
        if(size[pu]<=size[pv])
        {
            parent[pu]=pv;
            size[pv]+=size[pu];
        }
        else
        {
            parent[pv]=pu;
            size[pu]+=size[pv];
        }
    }
    int getComponentSize(int node){
        return size[findParent(node)];
    }
    bool isConnected(int u,int v)
    {
        return findParent(u)==findParent(v);
    }
    void printParent(){
        for(int i=0;i<this->n;i++)cout<<findParent(i)<<" ";
        cout<<endl;
    }
    void printSize(){
        for(int i=0;i<this->n;i++)cout<<size[i]<<" ";
        cout<<endl;
    }
};