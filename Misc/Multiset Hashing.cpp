const int N = 2e5;
const long long INF=1e18;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
auto dist=uniform_int_distribution<long long>(0,INF);
vector<long long> rnd;
vector<long long> arr;	// Contains distinct elements only
long long hashed[N + 1]; // Contains the hashed values of arr[i] after sorting

void init(){
	for(int i = 0; i <= 2*N; i++)
		rnd.pb(dist(rng));
}

void solve(){
	int n;
	cin >> n;
 	for(int i = 0; i < n; i++){
		long long x;
		cin >> x;
		arr.push_back(x);
	}
	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	for(int i = 0; i < arr.size(); i++){
		hashed[i] = arr[i];
	}
	for(int i = 0; i < arr.size(); i++){
		hashed[i] = rnd[lower_bound(arr.begin(), arr.end(), hashed[i]) - arr.begin()];
		// cout << arr[i] << ": " << hashed[i] << "\n";
	}

}