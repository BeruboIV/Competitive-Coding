const int MAXN = 35005, INF = 9e8;
const int BOUNDS = 0;   // 0 -> SUM, INF -> MINIMUM, -INF -> MAXIMUM 
int tree[4*MAXN];
int lazy[4*MAXN];
int s[MAXN];

// Change this function for Sum/Max/Min
void merge(int &node_val, int &left_val, int &right_val){
    node = (left_val + right_val);    // Sum
    // node = min(left_val, right_val);  // Min
    // node = max(left_val, right_val);  // Max
}

// Change this when we perform lazy update
void lazyUpdate(int &node_val, int start, int end, int val){
    node_val = node_val + (end - start + 1)*val; // Sum
    // node_val = node_val + val; // Max/Min

}

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
        merge(tree[node], tree[2*node], tree[2*node + 1]);
    }
}

void updateRange(int node, int start, int end, int l, int r, int val){
    if(lazy[node] != 0){ 
        // This node needs to be updated
        lazyUpdate(tree[node], start, end, lazy[node]);    // Update it
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
        lazyUpdate(tree[node], start, end, val);
        // tree[node] += val;  // for maximum/minimum
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
    merge(tree[node], tree[2*node], tree[2*node + 1]); // Updating root with sum value 
}

int queryRange(int node, int start, int end, int l, int r){
    if(start > end || start > r || end < l)     // Out of range
        return BOUNDS; 
    if(lazy[node] != 0){
        // This node needs to be updated
        lazyUpdate(tree[node], start, end, lazy[node]);     // Update it
        if(start != end){
            lazy[2*node] += lazy[node];         // Mark child as lazy
            lazy[2*node + 1] += lazy[node];    // Mark child as lazy
        }
        lazy[node] = 0;                 // Reset it
    } 
    if(start >= l && end <= r)             // Current segment is totally within range [l, r]
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = queryRange(2*node, start, mid, l, r);         // Query left child
    int p2 = queryRange(2*node + 1, mid + 1, end, l, r);  // Query right child
    int curr;
    merge(curr, p1, p2);
    return curr;
}

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> s[i];
    build(1, 1, n);
}