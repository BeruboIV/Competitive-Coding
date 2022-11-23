const int N = 2e5;
vector<int> adj[N + 1];

bool vis[N + 1];
int tin[N + 1], low[N + 1];
int TIMER;

set<int> cutpoints;

// Function for doing what to do with a cut point
void IS_CUTPOINT(int node){
	cutpoints.insert(node);
}

void dfs(int src, int par = -1){
	vis[src] = true;
	tin[src] = low[src] = TIMER++;
	int children = 0;

	for(int child : adj[src]){
		if(child == par)
			continue;
		if(vis[child])
			low[src] = min(low[src], tin[child]);
		else{
			dfs(child, src);
			low[src] = min(low[src], low[child]);
			// If the current edge (src, child) is such that none of the vertices 
			// to or its descendants in the DFS traversal tree has a back-edge to 
			// any of ancestors of v, then v is an articulation point.
			// Otherwise, v is not an articulation point.
			if(low[child] >= tin[src] && par != -1)
				IS_CUTPOINT(src);
			children++;
		}
	}

	// Root vertex will be the point of articulation if and only if this vertex has more than one child in the DFS tree.
	if(par == -1 && children > 1)
		IS_CUTPOINT(src);
}

void solve(){
	int n, m;
	cin >> n >> m;

	cutpoints.clear();

	for(int i = 0; i <= n; i++){
		vis[i] = false;
		tin[i] = -1;
		low[i] = -1;
		adj[i].clear();
	}

	for(int i = 0; i < m; i++){
		int x,y;
		cin >> x >> y;
		// cout << x << " " << y << "\n";
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	TIMER = 0;

	for(int i = 1; i <= n; i++){
		if(!vis[i]){
			dfs(i, -1);
		}
	}

	for(int x : cutpoints)
		cout << x << "\n";
}

// Question: https://codeforces.com/contest/1761/problem/C
// Solution: https://codeforces.com/contest/1761/submission/181800977