// Rabin Karp Algorithm
// T.C Worst Case : O(n*m)
// T.C Average Case : O(n+m)
// Stronger The Hash Function, Lesser The Collisions

#include <bits/stdc++.h>

using namespace std;
#define int long long
#define P 17
#define M 1e9+7

int modexp(int a, int b, int m) {a %= m;int res = 1LL;while (b > 0) {if (b & 1)res = (res%m *1LL* a%m) % m;a = (a%m *1LL* a%m) % m;b >>= 1;}return res%m;}

int createHash(int m,string &pat)
{
    int hash=0;
    for(int i=0;i<m;i++)
        hash+=(pat[i]-96)*1LL*modexp(P,i,M);
    return hash;
}
int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

int n;
cin>>n;
string s;
cin>>s;

int m;
cin>>m;
string pat;
cin>>pat;

int patHash=createHash(m,pat);
int subHash=0;

for(int i=0;i<m;i++)
    subHash+=(s[i]-96)*1LL*modexp(P,i,M);

if(subHash==patHash)
    cout<<0<<endl;

for(int i=m;i<n;i++)
{
    // Subtract Prev Index Hash Value
    subHash-=(s[i-m]-96);
    // Divide By prime Number
    subHash/=P;
    // Add New Index* pow(P,len-1)
    subHash+=(s[i]-96)*1LL*modexp(P,m-1,M);
    // cout<<i<<" "<<subHash<<endl;
    if(subHash==patHash)
        cout<<i-m+1<<endl;
}
return 0;
}
