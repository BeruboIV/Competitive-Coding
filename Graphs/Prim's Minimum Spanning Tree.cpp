const int N = 1e5;
vector<pair<long long, int>> adj[N + 1];
bool vis[N + 1];

long long prim(int src){
	priority_queue< pair<long long, int>, vector< pair<long long, int> >, greater< pair<long long, int> > > pq;

	long long mstCost = 0;

	pq.push({0LL, src});
	while(!pq.empty()){
		//	Select edge with minimum cost
		pair<long long, int> edge = pq.top();
		pq.pop();
		int v = edge.second;

		//	Check for cycle
		if(vis[v] == true)
			continue;
		mstCost += edge.first;
		vis[v] = true;

		for(pair<long long, int> temp : adj[v]){
			int u = temp.second;
			if(vis[u] == false){
				pq.push(temp);
			}
		}
	}

	return mstCost;
}

void solve(){
	int n, m;
	cin >> n >> m;

	for(int i = 1; i <= n; i++){
		vis[i] = false;
		adj[i].clear();
	}
	
	for(int i = 1; i <= m; i++){
		int x,y;
		long long cost;
		cin >> x >> y >> cost;
		adj[x].push_back({cost, y});
		adj[y].push_back({cost, x});
	}

	//	Selecting 1 as the starting node
	long long mstCost = prim(1);

	cout << mstCost << "\n";
}