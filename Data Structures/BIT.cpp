// CLASS BASED Fenwick Tree
class Fenwick{
    vector<long long> tree;
    const int N;
public:
    Fenwick(int n)
        : N(n){
            tree.resize(n + 1, 0);
        }

    long long query(int idx){
        int sum = 0;
        while(idx > 0){
            sum += tree[idx];
            idx -= (idx & (-idx));
        }
        return sum;
    }

    void update(int idx, long long val){
        while(idx <= N){
            tree[idx] += val;
            idx += (idx & (-idx));
        }
    }

    long long rangeQuery(int l, int r){
        if(l > r)
            return 0;
        long long leftSum = query(l - 1);
        long long rightSum = query(r);
        return (rightSum - leftSum);
    }
};

void solve(){
	int n;
	cin >> n;
	Fenwick BIT(n);
	// NOTE: 1 Based indexing is followed here
	for(int i = 1; i <= n; i++){
		long long val;
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
long long arr[N + 1], BIT[N + 1];

//O(LogN)
void update(int i, long long val, int n){
	while(i <= n){
		BIT[i] += val;
		i += (i & (-i));
	}
}

//O(LogN)
long long query(int i){
	long long sum = 0;
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

