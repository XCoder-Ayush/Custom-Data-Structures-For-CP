// Rabin Karp Algorithm
// T.C Worst Case : O(n*m)
// T.C Average Case : O(n+m)
// Stronger The Hash Function, Lesser The Collisions

#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MOD = 1e9+7;
const int P=17;
int modexp(int a, int b, int m) {a %= m;int res = 1LL;while (b > 0) {if (b & 1)res = (res%m *1LL* a%m) % m;a = (a%m *1LL* a%m) % m;b >>= 1;}return res%m;}
int modadd(int a,int b){return (a%MOD+b%MOD)%MOD;}
int modsub(int a,int b){return (a%MOD-b%MOD + MOD)%MOD;}
int modmul(int a,int b){return (a%MOD*1LL*b%MOD)%MOD;}
int modinv(int a){return modexp(a,MOD-2,MOD);}
int moddiv(int a,int b){return (a%MOD*1LL* modinv(b)%MOD)%MOD;}

int createHash(int m,string &pat,int P)
{
    int hash=0;
    for(int i=0;i<m;i++)
        hash=modadd(hash,modmul((pat[i]-96),modexp(P,i,MOD)%MOD));
    return hash%MOD;
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

int patHash=createHash(m,pat,P);
int subHash=0;

for(int i=0;i<m;i++)
    subHash=modadd(subHash,modmul((s[i]-96),modexp(P,i,MOD)));

if(subHash==patHash)
    cout<<0<<endl;

for(int i=m;i<n;i++)
{
    // Subtract Prev Index Hash Value
    subHash=modsub(subHash,(s[i-m]-96));
    // Divide By prime Number
    subHash=moddiv(subHash,P);
    // Add New Index* pow(P,len-1)
    subHash=modadd(subHash,modmul((s[i]-96),modexp(P,m-1,MOD)));
    // cout<<i<<" "<<subHash<<endl;
    if(subHash==patHash)
        cout<<i-m+1<<endl;
}
return 0;
}
