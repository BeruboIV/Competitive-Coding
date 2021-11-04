// CLASS BASED Fenwick Tree
class Fenwick{
	// 1 Based Indexing
public:
    int N;
    vector<int64_t> tree[2];
    Fenwick()
        : N(200005){
            tree[0].resize(N);
            tree[1].resize(N);
        }

    Fenwick(int n)
        : N(n){
            tree[0].resize(N + 1, 0);
            tree[1].resize(N + 1, 0);
        }

    void init(){
        tree[0].resize(N + 1, 0);
        tree[1].resize(N + 1, 0);
    }

    int64_t query(int idx, int flag = 0){
        int sum = 0;
        while(idx > 0){
            sum += tree[flag][idx];
            idx -= (idx & (-idx));
        }
        return sum;
    }

    void update(int idx, int64_t val, int flag = 0){
        while(idx <= N){
            tree[flag][idx] += val;
            idx += (idx & (-idx));
        }
    }

    int64_t rangeQuery(int l, int r, int flag = 0){
        if(l > r)
            return 0;
        int64_t leftSum = query(l - 1, flag);
        int64_t rightSum = query(r, flag);
        return (rightSum - leftSum);
    }

    // Use the below only in case of range update and range query
    // Call update_range() instead of update()
    // Point update -> update_range(i, i, val);
    // void update_range(int l, int r, int64_t val){
    //     update(l, val, 0);
    //     update(r + 1, -val, 0);
    //     update(l, val * (l - 1), 1);
    //     update(r + 1, -val * r, 1);
    // }

    // int64_t prefix_sum(int idx){
    //     return query(idx, 0) * idx - query(idx, 1);
    // }

    // int64_t range_sum(int l, int r){
    //     return prefix_sum(r) - prefix_sum(l - 1);
    // }

};


void solve(){
	int n;
	cin >> n;
	Fenwick BIT;
	BIT.N = n;
	BIT.init();
	// NOTE: 1 Based indexing is followed here
	for(int i = 1; i <= n; i++){
		int64_t val;
		cin >> val;
		BIT.update(i, val);
	}

	int q;
	cin >> q;
	while(q--){
		int x, y;
		cin >> x >> y;
		//Sum for the range [x, y]
		cout << BIT.rangeQuery(x, y) << "\n";
	}
}

// Normal BIT

// 1 Based indexing
const int N = 5e5;
int64_t arr[N + 1], BIT[N + 1];

//O(LogN)
void update(int i, int64_t val, int n){
	while(i <= n){
		BIT[i] += val;
		i += (i & (-i));
	}
}

//O(LogN)
int64_t query(int i){
	int64_t sum = 0;
	while(i > 0){
		sum += BIT[i];
		i -= (i & (-i));
	}
	return sum;
}

void solve(){
	int n;
	cin >> n;
	// NOTE: 1 Based indexing is followed here
	for(int i = 1; i <= n; i++){
		cin >> arr[i];
		update(i, arr[i], n);
	}
	int q;
	cin >> q;
	while(q--){
		int x, y;
		cin >> x >> y;
		//Sum for the range [x, y]
		cout << query(y) - query(x-1)<< "\n";
	}
}

