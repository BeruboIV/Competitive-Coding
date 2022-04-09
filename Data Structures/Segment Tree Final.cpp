// Copied from demoralizer's video: https://unacademy.com/class/all-purpose-generic-segment-tree/3UUZEGVH
// Note: 0 based indexing is followed here
template<typename Node, typename Update>
class SegmentTree{
public:
    int len;
    vector<Node> t;
    vector<Update> u;
    vector<bool> lazy;
    Node identity_element;
    Update identity_transformation;

    SegmentTree(int n){
        this->len = n;
        t.resize(4 * len + 4);
        u.resize(4 * len + 4);
        lazy.resize(4 * len + 4);
        identity_element = Node();
        identity_transformation = Update();
    }

    void push_down(const int32_t &tree_idx, const int32_t &tl, const int32_t &tr){
        if(!lazy[tree_idx])
            return;
        int32_t tm = (tl + tr) >> 1;
        apply(tree_idx << 1, tl, tm, u[tree_idx]);
        apply((tree_idx << 1) | 1, tm + 1, tr, u[tree_idx]);
        u[tree_idx] = identity_transformation;
        lazy[tree_idx] = 0;
    }

    void apply(const int32_t &tree_idx, const int32_t &tl, const int32_t &tr, Update upd){
        if(tl != tr){
            lazy[tree_idx] = 1;
            u[tree_idx].combine(upd, tl, tr);
        }
        upd.apply(t[tree_idx], tl, tr);
    }

    template<typename T>
    void build(const T &arr, const int32_t &tree_idx, const int32_t &tl, const int32_t &tr){
        if(tl == tr){
            // Leaves have the same values as values of the array
            t[tree_idx] = arr[tl];
            return;
        }
        int32_t tm = (tl + tr) >> 1;
        build(arr, tree_idx << 1, tl, tm);
        build(arr, (tree_idx << 1) | 1, tm + 1, tr);
        t[tree_idx].merge(t[tree_idx << 1], t[(tree_idx << 1) | 1]);
    }

    Node query(const int32_t &tree_idx, const int32_t &tl, const int32_t &tr, const int32_t &l, const int32_t &r){
        if(l > tr || r < tl){
            // No overlap
            return identity_element;
        }
        if(tl >= l && tr <= r){
            // Complete overlap
            return t[tree_idx];
        }
        push_down(tree_idx, tl, tr);
        int32_t tm = (tl + tr) >> 1;
        Node a = query(tree_idx << 1, tl, tm, l, r);
        Node b = query((tree_idx << 1) | 1, tm + 1, tr, l, r);
        Node ans;
        ans.merge(a, b);
        return ans;
    }

    void rupd(const int32_t &v, const int32_t &tl, const int32_t &tr, const int32_t &l, const int32_t &r, const Update &upd){
        if(l > tr || r < tl){
            // No overlap
            return;
        }
        if(tl >= l && tr <= r){
            // Complete overlap
            apply(v, tl, tr, upd);
            return;
        }
        push_down(v, tl, tr);
        int32_t tm = (tl + tr) >> 1;
        rupd(v << 1, tl, tm, l, r, upd);
        rupd((v << 1) | 1, tm + 1, tr, l, r, upd);
        t[v].merge(t[v << 1], t[(v << 1) | 1]);
    }

    template<typename T>
    void build(const T &arr){
        build(arr, 1, 0, len - 1);
    }

    Node query(const int32_t &l, const int32_t &r){
        return query(1, 0, len - 1, l, r);
    }

    void rupd(const int32_t &l, const int32_t &r, const Update &upd){
        rupd(1, 0, len - 1, l, r, upd);
    }
};

class Node{
public:
    int v = 0;  // Change
    // Use more variables if you want more information
    // these default values should be identity_element
    Node(){}
    Node(int val){
        v = val;    // Change
    }
    void merge(const Node &l, const Node &r){
        // Change
        v = l.v + r.v;  // For sum
        // v = max(l.v, r.v);  // For max;
        // v = __gcd(l.v, r.v);    // For gcd;
    }
};

class Update{
public:
    int v = 0;  // Change
    // Use more variables if you want more information
    // these default values should be identity_element
    Update(){}
    Update(int val){
        v = val;    // Change
    }
    // combine the current update with the other update
    void combine(Update &other, const int32_t &tl, const int32_t &tr){
        // Change
        v += other.v;   // updates the node by +other.v

        // We can be sure that the "other" is newer than current
        // other = new updated value
    }
    // Store the correct information in the Node x
    // tr - tl + 1 --> Width of the range
    void apply(Node &x, const int32_t &tl, const int32_t &tr){
        // Change
        x.v += (tr - tl + 1) * v;   // For range update: Add 'v' to the whole range
    }
};

void solve(){
    int n = 1000;
    // cin >> n;
    SegmentTree<Node, Update> seg(n);   // Create a segment tree of len = n
    vector<int> arr(n);
    seg.build(arr);

    seg.rupd(2, 6, 3);     // [l, r] --> Add value val: [2, 6] -> +3
    seg.rupd(3, 10, 5);
    for(int i = 0; i < 15; i++){
        cout << seg.query(i, i).v << " ";   // For printing the values: Point query
    }

    cout << "\n\n";

    cout << seg.query(2, 3).v;  // Range query
}

// Question: https://www.codechef.com/problems/SORTDIS
// Solution: https://www.codechef.com/viewsolution/62499174