const int N = 2e5;
vector<int> adj[N + 1];

bool vis[N + 1];
int tin[N + 1], low[N + 1];
int TIMER;

set<pair<int,int>> bridges;

// Function for doing what to do with a bridge
void IS_BRIDGE(int u, int v){
	if(u > v)
		swap(u, v);
	bridges.insert({u, v});
}

void dfs(int src, int par = -1){
	vis[src] = true;
	tin[src] = low[src] = TIMER++;

	for(int child : adj[src]){
		if(child == par)
			continue;
		// A backedge cannot be a bridge
		if(vis[child])
			low[src] = min(low[src], tin[child]);
		else{
			dfs(child, src);
			low[src] = min(low[src], low[child]);
			// A forward edge "can" be a bridge
			if(low[child] > tin[src])
				IS_BRIDGE(src, child);
		}
	}
}

void solve(){
	int n, m;
	cin >> n >> m;

	for(int i = 0; i <= n; i++){
		vis[i] = false;
		tin[i] = -1;
		low[i] = -1;
		adj[i].clear();
	}

	for(int i = 0; i < m; i++){
		int x,y;
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	TIMER = 0;

	for(int i = 1; i <= n; i++){
		if(!vis[i]){
			dfs(i, -1);
		}
	}

	for(pair<int,int> x : bridges)
		cout << x.first << " " << x.second << "\n";
} 
