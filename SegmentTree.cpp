// Example Of A Template Of Segment Tree With Range Sum Query
// Point Update Included
// T.C For Build : O(N)
// T.C For Query : O(logN)
// T.C For Update : O(logN)
//
#include <bits/stdc++.h>

using namespace std;
class SegmentTree{
    public:
    vector<int> seg;
    SegmentTree(int n)
    {
        seg.resize(4*n+1);
    }
    void build(int ind,int low,int high,vector<int> &arr)
    {
        if(low>=high){
            seg[ind]=arr[low];
            return;
        }
        int mid=low+(high-low)/2;
        build(2*ind+1,low,mid,arr);
        build(2*ind+2,mid+1,high,arr);
        // Whatever Is The Range Query
        // Here It Is RSQ
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    int query(int ind,int low,int high,int l,int r)
    {
        // No Overlap
        // [low..high] [l..r] OR  [l..r] [low..high] 
        if(high<l || r<low)return 0;
        // Complete Overlap
        if(low>=l && high<=r)return seg[ind];

        int mid=low+(high-low)/2;
        int left=query(2*ind+1,low,mid,l,r);
        int right=query(2*ind+2,mid+1,high,l,r);
        return left+right;
    }
    void pointUpdate(int ind,int low,int high,int idx,int val)
    {
        if(low==high){
            seg[ind]=val;
            return;
        }
        // Update arr[idx] with val
        int mid=low+(high-low)/2;
        if(idx<=mid)pointUpdate(2*ind+1,low,mid,idx,val);
        else pointUpdate(2*ind+2,mid+1,high,idx,val);

        seg[ind]=seg[2*ind+1]+seg[2*ind +2];
    }
};
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &it : arr)
        cin>>it;
    SegmentTree st(n);
    st.build(0,0,n-1,arr);
    int q;
    cin>>q;
    while(q--)
    {
        int type;
        cin>>type;
        if(type==1)
        {
            int l,r;
            cin>>l>>r;
            cout<<st.query(0,0,n-1,l,r)<<endl;
        }
        else
        {
            int idx,val;
            cin>>idx>>val;
            arr[idx]=val;
            st.pointUpdate(0,0,n-1,idx,val);
        }
    }
return 0;
}
