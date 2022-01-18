// NOTE: 1 based indexing is followed here
class Node{
public:
    // Use required attributes
    long long val;

    // Default Values:
    Node(){
        val = 0;
    }

};

template <typename T = long long>
class SegmentTree{
public:
    int N;
    vector<Node> tree;
    vector<T> arr;

    SegmentTree(){
        N = 2e5 + 5;
        tree.resize(4 * N + 5);
        arr.resize(N);
    }

    SegmentTree(int n){
        N = n + 1;
        tree.resize(4 * N + 5);
        arr.resize(N);
    }

    void init(int n){
        // For 1 based requirement
        N = n + 1;
        tree.resize(4 * N + 5);
        arr.resize(N);
    }

    void merge(Node &node, const Node &left_node, const Node &right_node){
        // Change as per requirements
        node.val = left_node.val + right_node.val;  // Sum
        // node.val = max(left_node.val, right_node.val);  // Max
        // node.val = __gcd(left_node.val, right_node.val);  // GCD
    }

    void build(int node_idx, int start, int end){
        if(start == end){
        	// Change as per requirements
            // Leaf node will have a single element
            tree[node_idx].val = arr[start];
        }
        else{
            int mid = (start + end) / 2;
            // Recurse on the left child
            build(2 * node_idx, start, mid);
            // Recurse on the right child
            build(2 * node_idx + 1, mid + 1, end);
            // Internal node will have the sum of both of its children
            merge(tree[node_idx], tree[2 * node_idx], tree[2 * node_idx + 1]);
        }
    }

    // start, end -> node range
    // idx -> index of the element to be updated
    void updatePoint(int node_idx, int start, int end, int arr_idx, T val){
        if(start == end){
        	// Change as per requirements
            // Leaf node
            arr[arr_idx] += val;
            // Change the node values
            tree[node_idx].val += val;
        }
        else{
            int mid = (start + end) / 2;
            if(arr_idx <= mid){
                // If arr_idx is in the left child, recurse on the left child
                updatePoint(2 * node_idx, start, mid, arr_idx, val);
            }
            else{
                // if arr_idx is in the right child, recurse on the right child
                updatePoint(2 * node_idx + 1, mid + 1, end, arr_idx, val);
            }
            // Internal node will have the sum of both of its children
            merge(tree[node_idx], tree[2 * node_idx], tree[2 * node_idx + 1]);
        }
    }

    // l, r -> query range
    // start, end -> tree range
    Node queryRange(int node_idx, int start, int end, int l, int r){
        // no overlap
        if(start > r || end < l){
        	// Change as per requirements
            Node empty_node;
            return empty_node;
        }
        // full overlap
        if(l <= start && end <= r){ // l ... start ... end ... r
            return tree[node_idx];
        }
        // partial overlap
        int mid = (start + end) / 2;
        Node p1 = queryRange(2 * node_idx, start, mid, l, r);
        Node p2 = queryRange(2 * node_idx + 1, mid + 1, end, l, r); 
        Node curr;
        merge(curr, p1, p2);
        return curr;
    }
};

void solve(){
    int n;
    cin >> n;
    SegmentTree<long long> seg(n);
    vector<long long> arr(n + 1);

    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        arr[i] = x;
        seg.arr[i] = x;
    }

    seg.build(1, 1, n);

    // Update: idx --> Point update and 1 <= idx <= n --> 1 based indexing
    // seg.updatePoint(1, 1, n, idx, val)

    // Query: [l, r] --> Returns a node
    // seg.queryRange(1, 1, n, l, r)
}


// -------------------------------------------------------------------------------

// Non class based

const int N = 1e5 + 5;
int tree[4 * N], s[N];
// node v - > 2 * v and (2 * v + 1)

// Change this function as per requirement
void merge(int &node_val, int &left_val, int &right_val){
	node_val = left_val + right_val;	// Sum
}

void build(int node, int start, int end){
    if(start == end){
        // Leaf node will have a single element
        tree[node] = s[start];
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

// start, end -> node range
// idx -> index of the element to be updated
void updatePoint(int node, int start, int end, int idx, int val){
    if(start == end){
        // Leaf node
        s[idx] += val;
        tree[node] += val;
    }
    else{
        int mid = (start + end) / 2;
        if(idx <= mid){
            // If idx is in the left child, recurse on the left child
            updatePoint(2*node, start, mid, idx, val);
        }
        else{
            // if idx is in the right child, recurse on the right child
            updatePoint(2*node+1, mid+1, end, idx, val);
        }
        // Internal node will have the sum of both of its children
        merge(tree[node], tree[2*node], tree[2*node + 1]);
    }
}

// l, r -> query range
// start, end -> tree range
int queryRange(int node, int start, int end, int l, int r){
	// no overlap
	if(start > r || end < l){
		return 0;
	}
	// full overlap
	if(l <= start && end <= r){	// l ... start ... end ... r
		return tree[node];
	}
	// partial overlap
	int mid = (start + end)/2;
	int p1 = queryRange(2*node, start, mid, l, r);
	int p2 = queryRange(2*node + 1, mid + 1, end, l, r); 
	int curr;
	merge(curr, p1, p2);
	return curr;
}

void solve(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> s[i];
	build(1, 1, n);
	int q;
	cin >> q;
	while(q--){
		int type;
		cin >> type;
		if(type == 1){
			// update
			int idx, val;
			cin >> idx >> val;
			updatePoint(1, 1, n, idx, val);
		}
		else{
			int l, r;
			cin >> l >> r;
			cout << queryRange(1, 1, n, l, r) << "\n";
		}
	}
}

