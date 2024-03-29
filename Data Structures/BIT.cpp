// CLASS BASED Fenwick Tree
// NOTE: 0 Based indexing is followed here --> [0, r] range is supported
template<typename T = long long>
class Fenwick{
public:
    int N;
    vector<T> tree[2];
    Fenwick(){}

    Fenwick(int n)
        : N(n){
            tree[0].resize(N + 1, 0);
            tree[1].resize(N + 1, 0);
        }

    void init(int n){
        N = n;
        tree[0].resize(N + 1, 0);
        tree[1].resize(N + 1, 0);
    }

    T query(int idx, int flag = 0){
        assert(idx <= N);
        T sum = 0;
        while(idx >= 0){
            sum += tree[flag][idx];
            idx = (idx & (idx + 1)) - 1;
        }
        return sum;
    }

    void update(int idx, T val, int flag = 0){
        while(idx <= N){
            tree[flag][idx] += val;
            idx = (idx | (idx + 1));
        }
    }

    // [l, r]
    T rangeQuery(int l, int r, int flag = 0){
        assert(r <= N && "R Out of bound");
        assert(l >= 0 && "L Must be positive");
        if(l > r)
            return 0;
        if(l == 0)
            return query(r, flag);
        T leftSum = query(l - 1, flag);
        T rightSum = query(r, flag);
        return (rightSum - leftSum);
    }

    int getKth(T k){
        int ans = 0;
        T cnt = 0;

        for(int i = 20; i >= 0; i--){
            if((ans | (1 << i)) <= N && cnt + tree[0][(ans | (1 << i))] < k){
                ans |= (1 << i);
                cnt += tree[0][ans];
            }
        }

        if(ans == N)
            return -1;
        return ans + 1; // +1 because 'ans' will have position of largest value less than k
    }

    // Insert x into BIT. We basically increment
    // rank of all elements greater than x.
    void insert(int x){
        update(x, 1);
    }

    // Delete x from BIT. We basically decreases
    // rank of all elements greater than x.
    void erase(int x){
        update(x, -1);
    }

    T findRank(int x){
        return query(x);
    }

    // Use the below only in case of range update and range query
    // Call update_range() instead of update()
    // Point update -> update_range(i, i, val);
    // void update_range(int l, int r, T val){
    //     if(l > r)
    //         return;
    //     update(l, val, 0);
    //     update(r + 1, -val, 0);
    //     update(l, val * (l - 1), 1);
    //     update(r + 1, -val * r, 1);
    // }

    // T prefix_sum(int idx){
    //     return query(idx, 0) * idx - query(idx, 1);
    // }

    // T range_sum(int l, int r){
    //     if(l > r)
    //         return 0;
    //     return prefix_sum(r) - prefix_sum(l - 1);
    // }

};


void solve(){
    int n;
    cin >> n;
    Fenwick<long long> BIT(n);
    // vector<Fenwick<long long>> BIT(no_of_fenwick_tree, n);   // Array of fenwick tree which calls the constructor BIT(n);


    // NOTE: 1 Based indexing is followed here
    for(int i = 1; i <= n; i++){
        int64_t val;
        cin >> val;
        BIT.update(i, val);
    }

    // NOTE: to use getKth, use this:
    // Here 1 <= x <= n, else use coordinate compression
    // for(int i = 1; i <= n; i++){
    //     int x;
    //     cin >> x;
    //     BIT.insert(x);
    //     // To get the k-th element:
    //     BIT.getKth(x);
    // }

    int q;
    cin >> q;
    while(q--){
        int x, y;
        cin >> x >> y;
        //Sum for the range [x, y]
        cout << BIT.rangeQuery(x, y) << "\n";
        // To ADD value 'y' to value at index 'x'
        // BIT.update(x, y);

        // In case of range updates
        // BIT.update_range(l, r, val);
        // In case of range query:
        // BIT.range_sum(l, r);
    }
}

// Problem: https://codeforces.com/contest/1660/problem/F2
// Solution: https://codeforces.com/contest/1660/submission/152552222


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

