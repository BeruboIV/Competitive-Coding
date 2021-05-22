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
            update(2*node, start, mid, idx, val);
        }
        else{
            // if idx is in the right child, recurse on the right child
            update(2*node+1, mid+1, end, idx, val);
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
	int p1 = query(2*node, start, mid, l, r);
	int p2 = query(2*node + 1, mid + 1, end, l, r); 
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

