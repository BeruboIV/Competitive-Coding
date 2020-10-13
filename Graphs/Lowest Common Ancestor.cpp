const int N = 1e5;	//Number of nodes.
const int P = 25; //Highest set bit possible
int LCA[N+1][P+2];
vector<int> adj[N+1];
int LOG2[N+1];
int level[N+1];

void dfs(int node, int par){
	LCA[node][0] = par;
	level[node] = level[par] + 1;
	for(int child : adj[node]){
		if(child != par)
			dfs(child, node);
	}
}

void precompute_LCA(int n){
	for(int i = 2; i <= N; i++)
		LOG2[i] = LOG2[i/2] + 1;
	int p = LOG2[n];
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= p; j++)
			LCA[i][j] = -1;
	}
	dfs(1, -1);
	for(int j = 1; j <= P; j++){
		for(int i = 1; i <= N; i++){
			int par = LCA[i][j-1];
			if(par == -1)
				LCA[i][j] = -1;
			else
				LCA[i][j] = LCA[par][j-1];
		}
	}
	//Let's precalculate Log values also
	
}

int getLCA(int a, int b){
	if(level[b] < level[a])
		swap(a,b);
	int d = level[b] - level[a];
	while(d > 0){
		int i = LOG2[d];
		b = LCA[b][i];
		d -= (1 << i);
	}
	if(a == b)
		return a;
	// while(LCA[a][0] != LCA[b][0]){
	// 	a = LCA[a][0];
	// 	b = LCA[b][0];
	// } Takes O(N) time
	for(int i = P; i >= 0; i--){
		if(LCA[a][i] != -1 && (LCA[a][i] != LCA[b][i])){
			a = LCA[a][i];
			b = LCA[b][i];
		}
	}
	return LCA[a][0];
}

void solve(){
	int n;
	cin >> n;
	for(int i = 0; i < n - 1; i++){
		int x,y;
		cin >> x >> y;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	precompute_LCA(n);
	int q;
	cin >> q;
	while(q--){
		int a,b;
		cin >> a >> b;
		cout << getLCA(a,b) << "\n";
	}
}
