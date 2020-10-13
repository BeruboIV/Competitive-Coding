const int N = 5e5;
int arr[N + 1], BIT[N + 1];

//O(LogN)
void update(int i, int val, int n){
	while(i <= n){
		BIT[i] += val;
		i += (i & (-i));
	}
}

//O(LogN)
int query(int i){
	int sum = 0;
	while(i > 0){
		sum += BIT[i];
		i -= (i & (-i));
	}
	return sum;
}

void solve(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> arr[i];
		update(i, arr[i], n);
	}
	int q;
	cin >> q;
	while(q--){
		int x, y;
		cin >> x >> y;
		//Sum for the range [y, x]
		cout << query(y) - query(x-1)<< "\n";
	}
}