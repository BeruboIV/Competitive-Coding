// CLASS BASED Fenwick Tree
class Fenwick{
public:
    int N;
    vector<int64_t> tree;
    Fenwick()
    	: N(200005){
    		tree.resize(2000005);
    	}

    Fenwick(int n)
        : N(n){
            tree.resize(N + 1, 0);
        }

    void init(){
    	tree.resize(N + 1, 0);
    }

    int64_t query(int idx){
        int sum = 0;
        while(idx > 0){
            sum += tree[idx];
            idx -= (idx & (-idx));
        }
        return sum;
    }

    void update(int idx, int64_t val){
        while(idx <= N){
            tree[idx] += val;
            idx += (idx & (-idx));
        }
    }

    int64_t rangeQuery(int l, int r){
        if(l > r)
            return 0;
        int64_t leftSum = query(l - 1);
        int64_t rightSum = query(r);
        return (rightSum - leftSum);
    }

};

Fenwick BIT;

void solve(){
	int n;
	cin >> n;
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

