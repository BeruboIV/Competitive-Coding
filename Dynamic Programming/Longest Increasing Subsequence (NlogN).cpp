void solve(){
	int n;
	cin >> n;
	int arr[n];
	for(int i = 0; i < n; i++)
		cin >> arr[i];
	const int INF = (int)1e9;
	vector<int> d(n+1, INF);
	d[0] = -INF;
	for(int i = 0; i < n; i++){
		int j = upper_bound(d.begin(), d.end(), arr[i]) - d.begin();
		if(d[j-1] < arr[i] && arr[i] < d[j])
			d[j] = arr[i];
	}
	int ans = 0;
	for(int i = 0; i < n; i++)
		if(d[i] < INF)
			ans = i;
	cout << ans;
}