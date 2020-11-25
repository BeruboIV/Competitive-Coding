//0 Based indexing is followed here.
const int N = 2e5;
int log2[N + 1];	//Quick lookup table for floor(log2(i)), 1 <= i <= N
int dp[261][N + 1];	//dp[i][j] = [j, j + (1 << i) ) --> Notice the open interval
int arr[N + 1];

//Call this function once before all test cases
void init(){
	for(int i = 2; i <= N; i++)
		log2[i] = 1 + log2[i/2];
}

//Query the smallest element in the range [l, r], O(1)
int MinQuery(int l, int r){
	int len = r - l + 1;
	int p = log2[len];
	int left = dp[p][l];
	int right = dp[p][r - (1 << p) + 1];
	return min(left, right);
}

//Query the smallest element in the range [l, r] by doing
//a cascading min query, O(log2(n));
//This function can be used to return sum of ranges also
int CascadingMinQuery(int l, int r){
	int min_val = INT_MAX;
	for(int p = log2[r - l + 1]; l <= r; p = log2[r - l + 1]){
		min_val = min(min_val, dp[p][l]);
		l += (1 << p);
	}
	return min_val
}

void solve(){
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> arr[i];
	//Filling first row
	for(int i = 0; i < n; i++){
		dp[0][i] = arr[i];
		//it[0][i] = i;
	}
	int P = log2[n];
	for(int p = 1; p <= P; p++){
		for(int i = 0; i + (1 << p) <= n; i++){
			int left = dp[p - 1][i];
			int right = dp[p - 1][i + (1 << (p - 1))];
			dp[p][i] = min(left, right);

			// //Save the index of smallest element
			// if(left <= right)
			// 	it[p][i] = it[p - 1][i];
			// else
			// 	it[p][i] = it[p - 1][i + (1 << (p - 1))];
		}
	}
	int q;
	cin >> q;
	while(q--){
		int l,r;
		cin >> l >> r;
		l--, r--;
		cout << MinQuery(l, r) << "\n";
	}
}