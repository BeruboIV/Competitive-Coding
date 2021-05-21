const int MAXN = 35005, INF = 9e8;
int tree[4*MAXN];
int lazy[4*MAXN];
int s[MAXN];

void build(int node, int start, int end){
    lazy[node] = 0;
    if(start == end){
        // Leaf node will have a single element
        tree[node] = s[start];
        //cout << tree[node] << " ";
    }
    else{
        int mid = (start + end) / 2;
        // Recurse on the left child
        build(2*node, start, mid);
        // Recurse on the right child
        build(2*node+1, mid+1, end);
        // Internal node will have the sum of both of its children
        tree[node] = (tree[2*node] + tree[2*node+1]);
    }
}

void updateRange(int node, int start, int end, int l, int r, int val){
    if(lazy[node] != 0){ 
        // This node needs to be updated
        tree[node] += (end - start + 1)*lazy[node];    // Update it
        // tree[node] += lazy[node] for maximum/minimum
        if(start != end){
            lazy[2*node] += lazy[node];     // Mark left child as lazy
            lazy[2*node + 1] += lazy[node]; // Mark right child as lazy
        }
        lazy[node] = 0;     // Reset it
    }
    if(start > end || start > r || end < l)     // Current segment is not within range [l, r]
        return;
    if(start >= l && end <= r){
        // Segment is fully within range
        tree[node] += (end - start + 1)*val;
        // tree[node] += lazy[node] for maximum/minimum
        if(start != end){
            // Not leaf node
            lazy[2*node] += val;
            lazy[2*node + 1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(2*node, start, mid, l, r, val);         // Updating left child
    updateRange(2*node + 1, mid + 1, end, l, r, val);   // Updating right child
    tree[node] = (tree[2*node] + tree[2*node + 1]); // Updating root with sum value 
}

int queryRange(int node, int start, int end, int l, int r){
    if(start > end || start > r || end < l)     // Out of range
        return 0; 
    if(lazy[node] != 0){
        // This node needs to be updated
        tree[node] += (end - start + 1)*lazy[node];     // Update it
        // tree[node] += lazy[node] for maximum/minimum
        if(start != end){
            lazy[node*2] += lazy[node];         // Mark child as lazy
            lazy[node*2+1] += lazy[node];    // Mark child as lazy
        }
        lazy[node] = 0;                 // Reset it
    } 
    if(start >= l && end <= r)             // Current segment is totally within range [l, r]
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = queryRange(2*node, start, mid, l, r);         // Query left child
    int p2 = queryRange(2*node + 1, mid + 1, end, l, r);  // Query right child
    return (p1 + p2);
}

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> s[i];
    build(1, 1, n);
}