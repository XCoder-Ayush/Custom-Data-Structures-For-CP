class SegmentTree
{
public:
    vector<int> seg;
    SegmentTree(int n)
    {
        seg.resize(2 * n + 1);
    }
    void build(vector<int> &arr, int n)
    {
        for (int i = 0; i < n; i++)
            seg[n + i] = arr[i];

        for (int i = n - 1; i >= 1; i--)
            seg[i] = min(seg[2 * i],
                         seg[2 * i + 1]);
    }
    int query(int left, int right, int n)
    {
        left += n;
        right += n + 1;
        int mi = 1e9;
        while (left < right)
        {
            if (left & 1)
            {
                mi = min(mi, seg[left]);
                left++;
            }
            if (right & 1)
            {
                right--;

                mi = min(mi, seg[right]);
            }
            left /= 2;
            right /= 2;
        }
        return mi;
    }
    void pointUpdate(int pos, int value, int n)
    {
        pos += n;
        seg[pos] = value;

        while (pos > 1)
        {
            pos >>= 1;
            seg[pos] = min(seg[2 * pos],
                           seg[2 * pos + 1]);
        }
    }
};
