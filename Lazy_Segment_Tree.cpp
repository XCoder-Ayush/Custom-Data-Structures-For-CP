class SegmentTree{
    public:
    vector<int> seg,lazy;
    SegmentTree(int n)
    {
        seg.resize(4*n+1,0);
        lazy.resize(4*n+1,0);
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
    void updateRange(int ind, int low, int high, int l, int r, int val)
    {
        if(lazy[ind] != 0){ 
            // This ind Needs To Be Updated
            seg[ind] += (high - low + 1) * lazy[ind];    
            if(low != high)
            {
                // Propagate The Update Down
                lazy[ind*2+1] += lazy[ind];                  
                lazy[ind*2+2] += lazy[ind];                
            }
            //Update Of This ind Done
            lazy[ind] = 0;                                 
        }
        
        // No Overlap
        if(low > high or low > r or high < l)              
            return;

        // Complete Overlap
        if(low >= l && high <= r)
        {
            seg[ind] += (high - low + 1) * val;
            if(low != high)
            {
                // Propagate Down
                lazy[ind*2 + 1] += val;
                lazy[ind*2 + 2] += val;
            }
            return;
        }
        // Partial Overlap
        int mid = (low + high) / 2;
        updateRange(ind*2 + 1, low, mid, l, r, val);        
        updateRange(ind*2 + 2, mid + 1, high, l, r, val);   
        seg[ind] = seg[ind*2 + 1] + seg[ind*2 + 2];       
    }
 
    int queryRange(int ind, int low, int high, int l, int r)
    {
        if(low > high or low > r or high < l)
            return 0;        
        if(lazy[ind] != 0)
        {
            seg[ind] += (high - low + 1) * lazy[ind];            
            if(low != high)
            {
                lazy[ind*2+1] += lazy[ind];         
                lazy[ind*2+2] += lazy[ind];    
            }
            lazy[ind] = 0;                 
        }
        if(low >= l and high <= r)             
            return seg[ind];
        int mid = (low + high) / 2;
        int p1 = queryRange(ind*2 + 1, low, mid, l, r);         
        int p2 = queryRange(ind*2 + 2, mid + 1, high, l, r); 
        return (p1 + p2);
    }
};
