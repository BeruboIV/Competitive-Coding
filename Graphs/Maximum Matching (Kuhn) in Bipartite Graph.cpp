const int N = 500;	
vector<int> adj[N + 1];
vector<int> mt;
vector<bool> used;

int kuhn(int u) {
    if(used[u])
        return 0;
    used[u] = true;
    for(int v : adj[u]) {
        if (mt[v] == -1 || kuhn(mt[v])) {
            mt[v] = u;
            return 1;
        }
    }
    return 0;
}

void solve(){
	int n,m;
	cin >> n >> m;
	mt.clear();
	for(int i = 0; i <= n; i++){
		adj[i].clear();
		mt.push_back(-1);
	}
	for(int i = 1; i <= m; i++){
		int x,y;
		cin >> x >> y;
		adj[x].push_back(y);
	}
	int cnt = 0;	// Maximum matching
	for (int u = 1; u <= n; u++) {
        used.assign(n + 1, false);
        cnt += kuhn(u);
    }
    cout << cnt << "\n";
    // for(int i = 1; i <= n; i++){
    // 	if(mt[i] != -1)
    // 		cout << mt[i] << " " << i << "\n";
    // }
}