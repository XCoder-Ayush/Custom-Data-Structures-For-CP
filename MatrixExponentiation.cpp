#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define INF 1e18
#define vi  vector<int>
#define vvi vector<vector<int>> 
#define vpi vector<pair<int,int>>
#define ff first
#define ss second
#define pb push_back
#define ppb pop_back
#define all(x) (x).begin(), (x).end()
#define pqb priority_queue<int>
#define pqs priority_queue<int,vi,greater<int> >
#define setbits(x) __builtin_popcountll(x)
#define MOD 1e9+7
#define upperToLower(x) char(x | ' ')
#define lowerToUpper(x) char(x & '_')

vvi matMul(vvi A,vvi B){
    // Research Why Reference Can't Be Used Here

    // Valid
    // [n * l]  [l * m]
    int l=A[0].size();
    int n=A.size();
    int m=B[0].size();
    vvi C(n,vi(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int sum=0;
            for(int k=0;k<l;k++)
                sum+=A[i][k]*B[k][j];
            C[i][j]=sum;
        }
    }
    return C;
}
vvi matExp(vvi &A,int pow){    
    int n=A.size();
    // Valid-> n*n Matrix
    if(pow==0){
        vvi B(n,vi(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                ((i==j)?B[i][j]=1:B[i][j]=0); 
            }
        }
        return B;
    }
    // vvi temp=matExp(A,pow/2);
    if(pow%2==0)return matMul(matExp(A,pow/2),matExp(A,pow/2));
    else return matMul(A,matMul(matExp(A,pow/2),matExp(A,pow/2)));
}


void inputMat(vvi &A)
{
    int n,m;
    cin>>n>>m;
    A.resize(n,vi(m,0));
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>A[i][j];
}
void printMat(vvi &A)
{
    int n=A.size();
    int m=A[0].size();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main()
{    
    vvi A;
    vvi B;
    inputMat(A);
    inputMat(B);
    // vvi C=matMul(A,B);
    // printMat(C);
    vvi D=matExp(A,10);
    printMat(D);

    // Fibonaaci Number Matrix :
    // 0 1
    // 1 1

    // 0 1 1 2 3 5 8 13 21
    // nth Fibonaaci Number= A^n[1][1]
    return 0;
}
