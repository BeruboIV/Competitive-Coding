int highestPowerofTwo(int n){
	int highest_power = 0;
	while(n){
		highest_power++;
		n /= 2;
	}
	return highest_power;
}

void solve(){
	int n;
	cin >> n;
	int arr[n];
	for(int i = 0; i < n; i++)
		cin >> arr[i];
	int P = highestPowerofTwo(n);
	const int N = n;
	//const int N = 1e5; --> In most cases
	//const int P = 25; --> Suited for values <= 1e7
	int LOG2[N+1] = {0};
	int dp[P][N+1];
	//Quick Look-up table for floor(log2(i)) , 1<=i<=N
	for(int i = 2; i <= n; i++)
		LOG2[i] = LOG2[i/2] + 1;
	//Filling first row dp[0][i];
	for(int i = 0; i < n; i++)
		dp[0][i] = arr[i];
	for(int p = 1; p <= P; p++){
		for(int i = 0; i + (1 << p) <= n; i++){
			int left = dp[p - 1][i];
			int right = dp[p - 1][i + (1 << (p - 1))];
			dp[p][i] = min(left, right);
		}
	}

	//Query
	int q;
	cin >> q;

	auto MinQuery = [&](int l, int r){
		int len = r - l + 1;
		int p = LOG2[len];
		int left = dp[p][l];
		int right = dp[p][r - (1 << p) + 1];
		cout << min(left, right) << "\n";
	};

	auto CascadingMinQuery = [&](int l, int r){
		int min_val = INT_MAX;
		for(int p = LOG2[r - l + 1]; p <= r; p = LOG2[r - l + 1]){
			min_val = min(min_val, dp[p][l]);
			l += (1 << p);
		}
		cout << min_val << "\n";
	}

	while(q--){
		int l,r;
		cin >> l >> r;
		l--;
		r--;
		MinQuery(l,r);
		//CascadingMinQuery(l,r);
	}
}