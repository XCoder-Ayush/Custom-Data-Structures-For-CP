// Tree Cutting Codeforces(Euler Tour + BFS)

#include <bits/stdc++.h>

using namespace std;

// T.C : O(N)
// The Path Array Will Have A Space Complexity Of O(2*N).
int timer=0;
void eulerTour(int node,int par,vector<vector<int>> &tree,vector<int> &path)
{
    // Entering The Node
    path[timer]=node;
    timer++;
    for(auto &it : tree[node])
    {
        if(it==par)continue;
        eulerTour(it,node,tree,path);
    }
    path[timer]=node;
    timer++;
    // Exiting The Node
}


void bfs(vector<vector<int>> &tree,unordered_map<int,int> &level){
    int lvl=0;
    queue<pair<int,int>> q;
    // {node,parent}
    // Let The Root Be 1
    q.push({1,0});
    while(!q.empty())
    {
        int size=q.size();
        while(size--)
        {
            pair<int,int> x=q.front();
            q.pop();
            int node=x.first;
            int par=x.second;
            level[node]=lvl;

            for(auto &it : tree[node])
            {
                if(it!=par)
                {
                    q.push({it,node});
                }
            }
        }
        lvl++;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

int n;
cin>>n;
vector<int> arr(n+1);
for(int i=1;i<=n;i++)
    cin>>arr[i];

vector<vector<int>> tree(n+1);
vector<int> path(2*n);
vector<vector<int>> edges;
for(int i=0;i<n-1;i++)
{
    int u,v;
    cin>>u>>v;
    tree[u].push_back(v);
    tree[v].push_back(u);
    edges.push_back({u,v});
}
eulerTour(1,0,tree,path);
// for(auto &it : path)
//     cout<<it<<" ";
// cout<<endl;

unordered_map<int,int> fo,lo;
for(int i=0;i<2*n;i++)
{
    if(fo.find(path[i])==fo.end()){
        fo[path[i]]=i;
    }
    lo[path[i]]=i;
}

// Now Starts The Problem
int ans=0;
int blue=0,red=0,no=0;
for(int i=1;i<=n;i++)
{
    if(arr[i]==0)no++;
    if(arr[i]==1)red++;
    if(arr[i]==2)blue++;
}
unordered_map<int,int> level;
bfs(tree,level);
vector<int> preR(2*n);
vector<int> preB(2*n);
vector<int> preN(2*n);
for(int i=0;i<2*n;i++)
{
    if(arr[path[i]]==0)preN[i]=1;
    if(arr[path[i]]==1)preR[i]=1;
    if(arr[path[i]]==2)preB[i]=1;
}
// Prefix Sum
for(int i=1;i<2*n;i++)
{
    preR[i]+=preR[i-1];
    preB[i]+=preB[i-1];
    preN[i]+=preN[i-1];
}

for(auto &it : edges)
{
    // Check If It Is A Nice Edge Or Not
    int x=it[0];
    if(level[it[0]]<level[it[1]])x=it[1];

    int left=fo[x];
    int right=lo[x];
    int r1,b1,n1,r2,b2,n2;
    r1=preR[right]-preR[left-1];
    r1/=2;
    b1=preB[right]-preB[left-1];
    b1/=2;
    n1=preN[right]-preN[left-1];
    n1/=2;
    r2=red-r1,b2=blue-b1,n2=no-n1;
    if((r1>0 && b1>0) || (r2>0 && b2>0)){
        continue;
    }
    ans+=1;
}
cout<<ans<<endl;
return 0;
}
